/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Common.h"
#include "Log.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "World.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "GossipDef.h"
#include "QuestDef.h"
#include "ObjectAccessor.h"
#include "Group.h"
#include "Battleground.h"
#include "BattlegroundAlteracValley.h"
#include "ScriptMgr.h"
#include "GameObjectAI.h"
#include "QuestPackets.h"
#include "GarrisonPackets.h"
#include "QuestData.h"
#include "GameEventMgr.h"

void WorldSession::HandleQuestGiverStatusQuery(WorldPackets::Quest::QuestGiverStatusQuery& packet)
{
    QuestGiverStatus questStatus = QuestGiverStatus::None;

    Object* questGiver = ObjectAccessor::GetObjectByTypeMask(*_player, packet.QuestGiverGUID, TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT);
    if (!questGiver)
    {
        TC_LOG_INFO("network", "Error in CMSG_QUESTGIVER_STATUS_QUERY, called for non-existing questgiver (%s)", packet.QuestGiverGUID.ToString().c_str());
        return;
    }

    switch (questGiver->GetTypeId())
    {
        case TYPEID_UNIT:
        {
            TC_LOG_DEBUG("network", "WORLD: Received CMSG_QUESTGIVER_STATUS_QUERY for npc, %s", questGiver->GetGUID().ToString().c_str());
            if (!questGiver->ToCreature()->IsHostileTo(_player))       // do not show quest status to enemies
                questStatus = _player->GetQuestDialogStatus(questGiver);
            break;
        }
        case TYPEID_GAMEOBJECT:
        {
            TC_LOG_DEBUG("network", "WORLD: Received CMSG_QUESTGIVER_STATUS_QUERY for GameObject %s", questGiver->GetGUID().ToString().c_str());
            questStatus = _player->GetQuestDialogStatus(questGiver);
            break;
        }
        default:
            TC_LOG_ERROR("network", "QuestGiver called for unexpected type %u", questGiver->GetTypeId());
            break;
    }

    //inform client about status of quest
    _player->PlayerTalkClass->SendQuestGiverStatus(questStatus, packet.QuestGiverGUID);
}

void WorldSession::HandleQuestGiverHello(WorldPackets::Quest::QuestGiverHello& packet)
{
    Creature* creature = GetPlayer()->GetNPCIfCanInteractWith(packet.QuestGiverGUID,UNIT_NPC_FLAG_QUESTGIVER, UNIT_NPC_FLAG2_NONE);
    if (!creature)
        return;

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    // Stop the npc if moving
    creature->StopMoving();

    _player->PlayerTalkClass->ClearMenus();
    if (sScriptMgr->OnGossipHello(_player, creature))
        return;

    _player->PrepareGossipMenu(creature, creature->GetCreatureTemplate()->GossipMenuId, true);
    _player->SendPreparedGossip(creature);

    creature->AI()->sGossipHello(_player);
}

void WorldSession::HandleQuestGiverAcceptQuest(WorldPackets::Quest::QuestGiverAcceptQuest& packet)
{
    Object* object;
    if (!packet.QuestGiverGUID.IsPlayer())
        object = ObjectAccessor::GetObjectByTypeMask(*_player, packet.QuestGiverGUID, TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT | TYPEMASK_ITEM);
    else
        object = ObjectAccessor::FindPlayer(packet.QuestGiverGUID);

#define CLOSE_GOSSIP_CLEAR_DIVIDER() \
    do { \
        _player->PlayerTalkClass->SendCloseGossip(); \
        _player->SetDivider(ObjectGuid::Empty); \
    } while (0)

    // no or incorrect quest giver
    if (!object)
    {
        CLOSE_GOSSIP_CLEAR_DIVIDER();
        return;
    }

    if (Player* playerQuestObject = object->ToPlayer())
    {
        if ((_player->GetDivider().IsEmpty() && _player->GetDivider() != packet.QuestGiverGUID) ||  !playerQuestObject->CanShareQuest(packet.QuestID))
        {
            CLOSE_GOSSIP_CLEAR_DIVIDER();
            return;
        }
        if (!_player->IsInSameRaidWith(playerQuestObject))
        {
            CLOSE_GOSSIP_CLEAR_DIVIDER();
            return;
        }
    }
    else
    {
        if (!object->hasQuest(packet.QuestID))
        {
            CLOSE_GOSSIP_CLEAR_DIVIDER();
            return;
        }
    }

    // some kind of WPE protection
    if (!_player->CanInteractWithQuestGiver(object))
    {
        CLOSE_GOSSIP_CLEAR_DIVIDER();
        return;
    }

    if (Quest const* quest = sQuestDataStore->GetQuestTemplate(packet.QuestID))
    {
        // prevent cheating
        if (!GetPlayer()->CanTakeQuest(quest, true))
        {
            CLOSE_GOSSIP_CLEAR_DIVIDER();
            return;
        }

        if (!_player->GetDivider().IsEmpty())
        {
            Player* player = ObjectAccessor::FindPlayer(_player->GetDivider());
            if (player)
            {
                player->SendPushToPartyResponse(_player, QUEST_PARTY_MSG_ACCEPT_QUEST);
                _player->SetDivider(ObjectGuid::Empty);
            }
        }

        if (_player->CanAddQuest(quest, true))
        {
            _player->AddQuestAndCheckCompletion(quest, object);

            if (quest->HasFlag(QUEST_FLAGS_PARTY_ACCEPT))
            {
                if (Group* group = _player->GetGroup())
                {
                    for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
                    {
                        Player* player = itr->getSource();

                        if (!player || player == _player || !player->CanContact())     // not self
                            continue;

                        if (player->CanTakeQuest(quest, true))
                        {
                            player->SetDivider(_player->GetGUID());

                            //need confirmation that any gossip window will close
                            player->PlayerTalkClass->SendCloseGossip();

                            _player->SendQuestConfirmAccept(quest, player);
                        }
                    }
                }
            }

            _player->PlayerTalkClass->SendCloseGossip();

            if (quest->SourceSpellID)
                _player->CastSpell(_player, quest->SourceSpellID, true);

            return;
        }
    }

    CLOSE_GOSSIP_CLEAR_DIVIDER();

#undef CLOSE_GOSSIP_CLEAR_DIVIDER
}

void WorldSession::HandleQuestGiverQueryQuest(WorldPackets::Quest::QuestGiverQueryQuest& packet)
{
    // Verify that the guid is valid and is a questgiver or involved in the requested quest
    Object* object = ObjectAccessor::GetObjectByTypeMask(*_player, packet.QuestGiverGUID, TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT | TYPEMASK_ITEM);
    if (!object || (!object->hasQuest(packet.QuestID) && !object->hasInvolvedQuest(packet.QuestID)))
    {
        _player->PlayerTalkClass->SendCloseGossip();
        return;
    }

    if (Quest const* quest = sQuestDataStore->GetQuestTemplate(packet.QuestID))
    {
        // not sure here what should happen to quests with QUEST_FLAGS_AUTOCOMPLETE
        // if this breaks them, add && object->IsItem() to this check
        // item-started quests never have that flag
        if (!_player->CanTakeQuest(quest, true))
            return;

        if (quest->IsAutoAccept() && _player->CanAddQuest(quest, true))
            _player->AddQuestAndCheckCompletion(quest, object);

        if (quest->IsAutoComplete())
            _player->PlayerTalkClass->SendQuestGiverRequestItems(quest, object->GetGUID(), _player->CanCompleteQuest(quest->GetQuestId()), true);
        else
            _player->PlayerTalkClass->SendQuestGiverQuestDetails(quest, object->GetGUID(), true, false);
    }
}

void WorldSession::HandleQueryQuestInfo(WorldPackets::Quest::QueryQuestInfo& packet)
{
    if (!_player)
        return;

    if (Quest const* quest = sQuestDataStore->GetQuestTemplate(packet.QuestID))
        _player->PlayerTalkClass->SendQuestQueryResponse(quest->GetQuestId());
    else
    {
        WorldPackets::Quest::QueryQuestInfoResponse response;
        response.QuestID = packet.QuestID;
        SendPacket(response.Write());
    }
}

void WorldSession::HandleQueryTreasurePicker(WorldPackets::Quest::QueryTreasurePicker& packet)
{
    auto quest = sQuestDataStore->GetQuestTemplate(packet.QuestID);
    if (!quest || !sWorld->getBoolConfig(CONFIG_WORLD_QUEST))
        return;

    WorldPackets::Quest::QueryQuestRewardResponse response;
    response.QuestID = packet.QuestID;
    response.QuestRewardID = packet.QuestRewardID;

    if (quest->QuestInfoID)
    {
        auto wq = sQuestDataStore->GetWorldQuest(quest);
        if (!wq)
            return;

        response.Money = wq->Gold;
        uint32 ItemID = GetPlayer()->GetTeamId() == TEAM_HORDE ? wq->ItemList[CLASS_NONE].ItemIDH : wq->ItemList[CLASS_NONE].ItemIDA;
        uint32 ItemCount = wq->ItemList[CLASS_NONE].ItemCount;
        if (!ItemID)
        {
            ItemID = GetPlayer()->GetTeamId() == TEAM_HORDE ? wq->ItemList[GetPlayer()->getClass()].ItemIDH : wq->ItemList[GetPlayer()->getClass()].ItemIDA;
            ItemCount = wq->ItemList[GetPlayer()->getClass()].ItemCount;
        }
        if (ItemID)
        {
            WorldPackets::Quest::QueryQuestRewardResponse::ItemReward itemRew;
            itemRew.Item.ItemID = ItemID;
            itemRew.ItemCount = ItemCount;

            uint32 modTreeID = 0;
            auto bonusTree = GetPlayer()->GetWorldQuestBonusTreeMod(wq);
            modTreeID = std::get<0>(bonusTree);
            uint32 needLevel = std::get<1>(bonusTree);
            if (wq->worldQuest->MinItemLevel)
                needLevel = wq->worldQuest->MinItemLevel;

            itemRew.Item.ItemBonus = boost::in_place();
            itemRew.Item.ItemBonus->Context = modTreeID;
            itemRew.Item.ItemBonus->BonusListIDs = sObjectMgr->GetItemBonusForLevel(ItemID, modTreeID, GetPlayer()->getLevel(), needLevel);

            response.Items.emplace_back(itemRew);
        }

        if (wq->CurrencyID)
            response.Currencys.emplace_back(WorldPackets::Quest::QuestCurrency(wq->CurrencyID, wq->CurrencyCount));
        if (wq->worldQuest->Currency)
            response.Currencys.emplace_back(WorldPackets::Quest::QuestCurrency(wq->worldQuest->Currency, wq->worldQuest->CurrencyCount));
    }
    else
    {
        auto bracket = 0;
        switch (packet.QuestID)
        {
            case 45536: // 2v2 Weekly Quest UI
                bracket = MS::Battlegrounds::BracketType::Arena2v2;
                break;
            case 45537: // 3v3 Weekly Quest UI
                bracket = MS::Battlegrounds::BracketType::Arena3v3;
                break;
            case 45538: // 10v10 Weekly Quest UI
                bracket = MS::Battlegrounds::BracketType::RatedBattleground;
                break;
            default:
                return;
        }

        auto data = GetPlayer()->GetItemDataForRatedQuest(bracket);
        uint32 modTreeID = std::get<0>(data);
        uint32 needLevel = std::get<1>(data);
        std::vector<uint32> BonusListIDs = sObjectMgr->GetItemBonusForLevel(147421, modTreeID, GetPlayer()->getLevel(), needLevel);

        WorldPackets::Quest::QueryQuestRewardResponse::ItemReward itemRew;
        itemRew.ItemCount = 1;
        itemRew.Item.ItemID = 150369;
        itemRew.Item.ItemBonus = boost::in_place();
        itemRew.Item.ItemBonus->Context = modTreeID;
        itemRew.Item.ItemBonus->BonusListIDs = sObjectMgr->GetItemBonusForLevel(147421, modTreeID, GetPlayer()->getLevel(), needLevel);
        response.Items.emplace_back(itemRew);
    }

    GetPlayer()->SendDirectMessage(response.Write());
}

void WorldSession::HandleQuestGiverChooseReward(WorldPackets::Quest::QuestGiverChooseReward& packet)
{
    Quest const* quest = sQuestDataStore->GetQuestTemplate(packet.QuestID);
    if (!quest)
        return;

    // This is Real Item Entry, not slot id as pre 5.x
    if (packet.ItemChoiceID)
    {
        ItemTemplate const* rewardProto = sObjectMgr->GetItemTemplate(packet.ItemChoiceID);
        if (!rewardProto)
        {
            TC_LOG_ERROR("entities.player.cheat", "Error in CMSG_QUESTGIVER_CHOOSE_REWARD: player %s (%s) tried to get invalid reward item (Item Entry: %u) for quest %u (possible packet-hacking detected)", _player->GetName(), _player->GetGUID().ToString().c_str(), packet.ItemChoiceID, packet.QuestID);
            return;
        }

        bool itemValid = false;
        for (uint32 i = 0; i < quest->m_rewChoiceItemsCount; ++i)
        {
            if (quest->RewardChoiceItemId[i] && quest->RewardChoiceItemId[i] == uint32(packet.ItemChoiceID))
            {
                itemValid = true;
                break;
            }
        }

        if (!itemValid && quest->PackageID)
        {
            if (std::vector<QuestPackageItemEntry const*> const* questPackageItems = sDB2Manager.GetQuestPackageItems(quest->PackageID))
            {
                for (QuestPackageItemEntry const* questPackageItem : *questPackageItems)
                {
                    if (questPackageItem->ItemID != packet.ItemChoiceID)
                        continue;

                    if (_player->CanSelectQuestPackageItem(questPackageItem))
                    {
                        itemValid = true;
                        break;
                    }
                }
            }

            if (!itemValid)
            {
                if (std::vector<QuestPackageItemEntry const*> const* questPackageItems = sDB2Manager.GetQuestPackageItemsFallback(quest->PackageID))
                {
                    for (QuestPackageItemEntry const* questPackageItem : *questPackageItems)
                    {
                        if (questPackageItem->ItemID != packet.ItemChoiceID)
                            continue;

                        itemValid = true;
                        break;
                    }
                }
            }
        }

        if (!itemValid)
        {
            TC_LOG_ERROR("entities.player.cheat", "Error in CMSG_QUESTGIVER_CHOOSE_REWARD: player %s (%s) tried to get reward item (Item Entry: %u) wich is not a reward for quest %u (possible packet-hacking detected)", _player->GetName(), _player->GetGUID().ToString().c_str(), packet.ItemChoiceID, packet.QuestID);
            return;
        }
    }

    Object* object = _player;

    if (!quest->HasFlag(QUEST_FLAGS_AUTOCOMPLETE))
    {
        object = ObjectAccessor::GetObjectByTypeMask(*_player, packet.QuestGiverGUID, TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT);
        if (!object || !object->hasInvolvedQuest(packet.QuestID))
            return;

        // some kind of WPE protection
        if (!_player->CanInteractWithQuestGiver(object))
            return;

    }
    if ((!_player->CanSeeStartQuest(quest) && _player->GetQuestStatus(packet.QuestID) == QUEST_STATUS_NONE && !quest->IsAutoComplete()) ||
        (_player->GetQuestStatus(packet.QuestID) != QUEST_STATUS_COMPLETE && !quest->IsAutoComplete()))
        return;

    if (_player->CanRewardQuest(quest, packet.ItemChoiceID, true))
    {
        _player->RewardQuest(quest, packet.ItemChoiceID, object, true);

        switch (object->GetTypeId())
        { 
        case TYPEID_UNIT:
        case TYPEID_PLAYER:
            {
                //For AutoSubmition was added plr case there as it almost same exclude AI script cases.
                Creature *creatureQGiver = object->ToCreature();
                if (!creatureQGiver || !(sScriptMgr->OnQuestReward(_player, creatureQGiver, quest, packet.ItemChoiceID)))
                {
                    // Send next quest
                    if (Quest const* nextQuest = _player->GetNextQuest(packet.QuestGiverGUID, quest))
                    {
                        if (_player->CanTakeQuest(nextQuest, false))
                        {

                        }
                        if (nextQuest->IsAutoAccept() && _player->CanAddQuest(nextQuest, true))
                        {
                            if (creatureQGiver)
                            {
                                sScriptMgr->OnQuestAccept(_player, creatureQGiver, nextQuest);
                                creatureQGiver->AI()->sQuestAccept(_player, nextQuest);
                            }

                            _player->AddQuestAndCheckCompletion(nextQuest, object);
                        }

                        _player->PlayerTalkClass->SendQuestGiverQuestDetails(nextQuest, packet.QuestGiverGUID, true);
                    }

                    if (creatureQGiver)
                        creatureQGiver->AI()->sQuestReward(_player, quest, packet.ItemChoiceID);
                }
                break;
            }
        case TYPEID_GAMEOBJECT:
            if (!sScriptMgr->OnQuestReward(_player, dynamic_cast<GameObject*>(object), quest, packet.ItemChoiceID))
            {
                // Send next quest
                if (Quest const* nextQuest = _player->GetNextQuest(packet.QuestGiverGUID, quest))
                {
                    if (_player->CanTakeQuest(nextQuest, false))
                    {
                        if (nextQuest->IsAutoAccept() && _player->CanAddQuest(nextQuest, true))
                            _player->AddQuestAndCheckCompletion(nextQuest, object);

                        _player->PlayerTalkClass->SendQuestGiverQuestDetails(nextQuest, packet.QuestGiverGUID, true);
                    }
                }

                object->ToGameObject()->AI()->QuestReward(_player, quest, packet.ItemChoiceID);
            }
            break;
        default:
            break;
        }

        // TODO: is this needed?
        // As quest complete send available quests. Need when questgiver from next quest chain staying near questtaker
        //SendQuestgiverStatusMultipleQuery();

        // AutoTake system
         _player->PrepareAreaQuest( _player->GetCurrentAreaID());
    }
    else 
        _player->PlayerTalkClass->SendQuestGiverOfferReward(quest, packet.QuestGiverGUID, true);
}

void WorldSession::HandleQuestGiverRequestReward(WorldPackets::Quest::QuestGiverRequestReward& packet)
{
    Quest const* quest = sQuestDataStore->GetQuestTemplate(packet.QuestID);
    if (!quest)
        return;

    if (!quest->HasFlag(QUEST_FLAGS_AUTOCOMPLETE))
    {
        Object* object = ObjectAccessor::GetObjectByTypeMask(*_player, packet.QuestGiverGUID, TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT);
        if (!object || !object->hasInvolvedQuest(packet.QuestID))
            return;

        // some kind of WPE protection
        if (!_player->CanInteractWithQuestGiver(object))
            return;
    }

    if (_player->CanCompleteQuest(packet.QuestID))
        _player->CompleteQuest(packet.QuestID);

    if (_player->GetQuestStatus(packet.QuestID) != QUEST_STATUS_COMPLETE)
        return;

    _player->PlayerTalkClass->SendQuestGiverOfferReward(quest, packet.QuestGiverGUID, true);
}

void WorldSession::HandleQuestLogRemoveQuest(WorldPackets::Quest::QuestLogRemoveQuest& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    if (packet.Entry > MAX_QUEST_LOG_SIZE)
        return;

    if (uint32 questId = player->GetQuestSlotQuestId(packet.Entry))
    {
        if (!player->TakeQuestSourceItem(questId, true))
            return;                                     // can't un-equip some items, reject quest cancel

        if (Quest const* quest = sQuestDataStore->GetQuestTemplate(questId))
        {
            if (quest->HasSpecialFlag(QUEST_SPECIAL_FLAGS_TIMED))
                player->RemoveTimedQuest(questId);

            for (QuestObjective const& obj : quest->Objectives)
            {
                if (obj.Type == QUEST_OBJECTIVE_COMPLETE_CRITERIA_TREE)
                    if (CriteriaTree const* tree = sAchievementMgr->GetCriteriaTree(obj.ObjectID))
                        for (CriteriaTree const* node : tree->Children)
                            player->GetAchievementMgr()->RemoveCriteriaProgress(node);
            }
        }

        player->TakeQuestSourceItem(questId, true); // remove quest src item from player
        player->RemoveActiveQuest(questId);
        player->GetAchievementMgr()->RemoveTimedAchievement(CRITERIA_TIMED_TYPE_ITEM, questId);

        TC_LOG_INFO("network", "Player %u abandoned quest %u", player->GetGUIDLow(), questId);
    }

    _player->SetQuestSlot(packet.Entry, 0);

    _player->UpdateAchievementCriteria(CRITERIA_TYPE_QUEST_ABANDONED, 1);
}

void WorldSession::HandleQuestConfirmAccept(WorldPackets::Quest::QuestConfirmAccept& packet)
{
    if (Quest const* quest = sQuestDataStore->GetQuestTemplate(packet.QuestID))
    {
        if (!quest->HasFlag(QUEST_FLAGS_PARTY_ACCEPT))
            return;

        Player* originalPlayer = ObjectAccessor::FindPlayer(_player->GetDivider());
        if (!originalPlayer)
            return;

        if (!_player->IsInSameRaidWith(originalPlayer))
            return;

//        if (!originalPlayer->IsActiveQuest(packet.QuestID))
//            return;

        if (!_player->CanTakeQuest(quest, true))
            return;

        if (_player->CanAddQuest(quest, true))
        {
            _player->AddQuestAndCheckCompletion(quest, NULL); // NULL, this prevent DB script from duplicate running

            if (quest->SourceSpellID)
                _player->CastSpell(_player, quest->SourceSpellID, true);
        }

        _player->SetDivider(ObjectGuid::Empty);
    }
}

void WorldSession::HandleQuestgiverCompleteQuest(WorldPackets::Quest::QuestGiverCompleteQuest& packet)
{
    if (!packet.FromScript)
    {
        Object* object = ObjectAccessor::GetObjectByTypeMask(*_player, packet.QuestGiverGUID, TYPEMASK_UNIT | TYPEMASK_GAMEOBJECT);
        if (!object || !object->hasInvolvedQuest(packet.QuestID))
            return;

        // some kind of WPE protection
        if (!_player->CanInteractWithQuestGiver(object))
            return;
    }

    if (Quest const* quest = sQuestDataStore->GetQuestTemplate(packet.QuestID))
    {
        if (packet.FromScript && !quest->HasFlag(QUEST_FLAGS_AUTOCOMPLETE))
        {
            TC_LOG_ERROR("network", "Possible hacking attempt: Player %s [playerGuid: %s] tried to complete questId [entry: %u] by auto-submit flag for quest witch not suport it.",
                _player->GetName(), _player->GetGUID().ToString().c_str(), packet.QuestID);
            return;
        }
        if (!_player->CanSeeStartQuest(quest) && _player->GetQuestStatus(packet.QuestID) == QUEST_STATUS_NONE)
        {
            TC_LOG_ERROR("network", "Possible hacking attempt: Player %s [playerGuid: %s] tried to complete questId [entry: %u] without being in possession of the questId!",
                          _player->GetName(), _player->GetGUID().ToString().c_str(), packet.QuestID);
            return;
        }
        // TODO: need a virtual function
        if (_player->InBattleground())
            if (Battleground* bg = _player->GetBattleground())
                if (bg->GetTypeID() == MS::Battlegrounds::BattlegroundTypeId::BattlegroundAlteracValley)
                    ((BattlegroundAlteracValley*)bg)->HandleQuestComplete(packet.QuestID, _player);

        if (_player->GetQuestStatus(packet.QuestID) != QUEST_STATUS_COMPLETE)
        {
            if (quest->IsRepeatable())
                _player->PlayerTalkClass->SendQuestGiverRequestItems(quest, packet.QuestGiverGUID, _player->CanCompleteRepeatableQuest(quest), false);
            else
                _player->PlayerTalkClass->SendQuestGiverRequestItems(quest, packet.QuestGiverGUID, _player->CanRewardQuest(quest, false), false);
        }
        else
        {
            bool reqItem = false;
            if (quest->HasSpecialFlag(QUEST_SPECIAL_FLAGS_DELIVER))                  // some items required
            {
                reqItem = true;
                for (QuestObjective const& obj : quest->GetObjectives())
                {
                    if (obj.Type != QUEST_OBJECTIVE_ITEM)
                        continue;
                    if (obj.Flags & QUEST_OBJECTIVE_FLAG_OPTIONAL)
                        reqItem = false;
                }
            }
            if (reqItem)                  // some items required
                _player->PlayerTalkClass->SendQuestGiverRequestItems(quest, packet.QuestGiverGUID, _player->CanRewardQuest(quest, false), false);
            else                                                                    // no items required
                _player->PlayerTalkClass->SendQuestGiverOfferReward(quest, packet.QuestGiverGUID, !packet.FromScript);
        }
    }
}

void WorldSession::HandlePushQuestToParty(WorldPackets::Quest::PushQuestToParty& packet)
{
    if (_player->GetQuestStatus(packet.QuestID) == QUEST_STATUS_NONE || _player->GetQuestStatus(packet.QuestID) == QUEST_STATUS_REWARDED)
        return;

    Quest const* quest = sQuestDataStore->GetQuestTemplate(packet.QuestID);
    if (!quest)
        return;

    Group* group = _player->GetGroup();
    if (!group)
        return;

    for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* player = itr->getSource();
        if (!player || player == _player || !player->CanContact())
            continue;

        if (!player->SatisfyQuestStatus(quest, false))
        {
            _player->SendPushToPartyResponse(player, QUEST_PARTY_MSG_HAVE_QUEST);
            continue;
        }

        if (player->GetQuestStatus(packet.QuestID) == QUEST_STATUS_COMPLETE)
        {
            _player->SendPushToPartyResponse(player, QUEST_PARTY_MSG_FINISH_QUEST);
            continue;
        }

        if (!player->CanTakeQuest(quest, false))
        {
            _player->SendPushToPartyResponse(player, QUEST_PARTY_MSG_CANT_TAKE_QUEST);
            continue;
        }

        if (!player->SatisfyQuestLog(false))
        {
            _player->SendPushToPartyResponse(player, QUEST_PARTY_MSG_LOG_FULL);
            continue;
        }

        if (!player->GetDivider().IsEmpty())
        {
            _player->SendPushToPartyResponse(player, QUEST_PARTY_MSG_BUSY);
            continue;
        }

        _player->SendPushToPartyResponse(player, QUEST_PARTY_MSG_SHARING_QUEST);

        if (quest->IsAutoAccept() && player->CanAddQuest(quest, true) && player->CanTakeQuest(quest, true))
            player->AddQuestAndCheckCompletion(quest, _player);

        if (quest->IsAutoComplete() && quest->IsRepeatable() && !quest->IsDailyOrWeekly())
            player->PlayerTalkClass->SendQuestGiverRequestItems(quest, _player->GetGUID(), player->CanCompleteRepeatableQuest(quest), true);
        else
        {
            player->SetDivider(_player->GetGUID());
            player->PlayerTalkClass->SendQuestGiverQuestDetails(quest, player->GetGUID(), true, false);
        }
    }
}

void WorldSession::HandleQuestPushResult(WorldPackets::Quest::QuestPushResult& packet)
{
    if (!_player->GetDivider().IsEmpty())
    {
        if (_player->GetDivider() == packet.SenderGUID)
            if (Player* player = ObjectAccessor::FindPlayer(_player->GetDivider()))
                player->SendPushToPartyResponse(_player, static_cast<QuestShareMessages>(packet.Result));

        _player->SetDivider(ObjectGuid::Empty);
    }
}

void WorldSession::HandleQuestgiverStatusMultipleQuery(WorldPackets::Quest::QuestGiverStatusMultipleQuery& /*packet*/)
{
    _player->SendQuestGiverStatusMultiple();
}

void WorldSession::HandleAdventureJournalOpenQuest(WorldPackets::Quest::AdventureJournalOpenQuest& packet)
{
    auto const entry = sAdventureJournalStore.LookupEntry(packet.AdventureJournalID);
    if (!entry)
        return;

    if (entry->Type != 3/*typeQuest*/)
        return;

    auto quest = sQuestDataStore->GetQuestTemplate(entry->QuestID);
    if (!quest)
        return;

    if (_player->hasQuest(entry->QuestID) || !_player->CanTakeQuest(quest, true))
        return;

    _player->SetDivider(_player->GetGUID());
    PlayerMenu menu(this);
    menu.SendQuestGiverQuestDetails(quest, _player->GetGUID(), true, false);
}

void WorldSession::HandleAdventureJournalStartQuest(WorldPackets::Quest::AdventureJournalStartQuest& packet)
{
    auto questID = packet.QuestID;

    if (std::find_if(sAdventureMapPOIStore.begin(), sAdventureMapPOIStore.end(), [questID](AdventureMapPOIEntry const* adventureMapPOIEntry) -> bool { return adventureMapPOIEntry->Type == 1 && adventureMapPOIEntry->QuestID == questID; }) == sAdventureMapPOIStore.end())
        return;

    auto player = GetPlayer();
    auto quest = sQuestDataStore->GetQuestTemplate(questID);
    if (!quest)
        return;

    if (!player->getAdventureQuestID() && player->CanTakeQuest(quest, true) && player->CanAddQuest(quest, true))
    {
        player->setAdventureQuestID(quest->Id);
        player->AddQuest(quest, player);
        if (player->CanCompleteQuest(quest->Id))
            player->CompleteQuest(quest->Id);
    }
}

bool WorldSession::AdventureMapPOIAvailable(uint32 adventureMapPOIID)
{
    auto adventureMapPOIEntry = sAdventureMapPOIStore[adventureMapPOIID];
    if (!adventureMapPOIEntry)
        return false;

    auto available = false;

    if (sConditionMgr->IsPlayerMeetingCondition(GetPlayer(), adventureMapPOIEntry->PlayerConditionID))
    {
        switch (adventureMapPOIEntry->Type)
        {
        case 1:
            if (auto quest = sQuestDataStore->GetQuestTemplate(adventureMapPOIEntry->QuestID))
                available = !_player->getAdventureQuestID() && _player->CanTakeQuest(quest, false);
            break;
        default:
            break;
        }
    }

    return available;
}

void WorldSession::HandleQueryAdventureMapPOI(WorldPackets::Quest::QueryAdventureMapPOI& packet)
{
    SendPacket(WorldPackets::Quest::QueryAdventureMapPOIResponse(packet.AdventureMapPOIID, AdventureMapPOIAvailable(packet.AdventureMapPOIID)).Write());
}

void WorldSession::HandleGarrisonRequestScoutingMap(WorldPackets::Garrison::GarrisonRequestScoutingMap& scoutingMap)
{
    WorldPackets::Garrison::GarrisonScoutingMapResult result;
    result.ID = scoutingMap.ID;
    result.Active = AdventureMapPOIAvailable(scoutingMap.ID);
    SendPacket(result.Write());
}

void WorldSession::HandleRequestWorldQuestUpdate(WorldPackets::Quest::RequestWorldQuestUpdate& /*packet*/)
{
    TC_LOG_DEBUG("worldquest", "HandleRequestWorldQuestUpdate");

    WorldPackets::Quest::WorldQuestUpdate response;
    if (_player->getLevel() >= MAX_LEVEL && sWorld->getBoolConfig(CONFIG_WORLD_QUEST))
    {
        if (WorldQuestMap const* worldQuestInfo = sQuestDataStore->GetWorldQuestMap())
        {
            for (auto const& itr : *worldQuestInfo)
            {
                for (auto const& iter : itr.second)
                {
                    WorldQuest const* worldQuest = &iter.second;
                    if (!worldQuest || _player->WorldQuestCompleted(worldQuest->QuestID))
                        continue;

                    if (sQuestDataStore->WorldLegionInvasionZoneID && sQuestDataStore->WorldLegionInvasionZoneID == worldQuest->quest->QuestSortID && !worldQuest->worldQuest->PrimaryID && !worldQuest->quest->IsLegionInvasion())
                        continue;

                    if (QuestV2CliTaskEntry const* questTask = sQuestV2CliTaskStore.LookupEntry(worldQuest->QuestID))
                    {
                        if (!sConditionMgr->IsPlayerMeetingCondition(_player, questTask->ConditionID))
                            continue;

                        // if (questTask->WorldStateExpressionID)
                        // {
                            // auto expressionEntry = sWorldStateExpressionStore.LookupEntry(questTask->WorldStateExpressionID);
                            // if (!expressionEntry || !expressionEntry->Eval(_player))
                                // continue;
                        // }

                        if (questTask->FiltMinSkillID && _player->GetSkillValue(questTask->FiltMinSkillID) < questTask->FiltMinSkillValue)
                            continue;

                        if (questTask->FiltMinLevel != -1 && _player->getLevel() < questTask->FiltMinLevel)
                            continue;

                        if (questTask->FiltMaxLevel != -1 && _player->getLevel() > questTask->FiltMaxLevel)
                            continue;

                        if (questTask->FiltRaces && (questTask->FiltRaces & _player->getRaceMask()) == 0)
                            continue;

                        if (questTask->FiltClasses && (questTask->FiltClasses & _player->getClassMask()) == 0)
                            continue;

                        bool needQuest = false;
                        bool canStart = true;
                        for (auto quest : questTask->FiltCompletedQuest)
                            if (quest)
                                needQuest = true;

                        if (needQuest)
                            for (auto slot : questTask->FiltCompletedQuest)
                                if (slot && _player->GetQuestStatus(slot) != QUEST_STATUS_REWARDED)
                                    canStart = false;

                        //if (questTask->StartItem && !_player->HasAura(questTask->StartItem))
                        //    continue;

                        if (needQuest && !canStart)
                            continue;
                    }

                    response.WorldQuestUpdates.emplace_back(worldQuest->StartTime, worldQuest->QuestID, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);
                }
            }
        }
    }

    SendPacket(response.Write());
}

void WorldSession::HandleRequestAreaPoiUpdate(WorldPackets::Quest::RequestAreaPoiUpdate& /*packet*/)
{
    WorldPackets::Quest::AreaPoiUpdate response;
    bool needSend = false;
    // For activate screen need cast 233539
    if (sQuestDataStore->WorldLegionInvasionZoneID)
    {
        // Temporary hack
        Quest const* quest = sQuestDataStore->GetQuestTemplate(45812);
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(quest))
        {
            response.Pois.emplace_back(worldQuest->StartTime, 5210, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);
            response.Pois.emplace_back(worldQuest->StartTime, 5272, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);
            needSend = true;
        }
        quest = sQuestDataStore->GetQuestTemplate(45838);
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(quest))
        {
            response.Pois.emplace_back(worldQuest->StartTime, 5175, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);
            response.Pois.emplace_back(worldQuest->StartTime, 5273, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);
            needSend = true;
        }
        quest = sQuestDataStore->GetQuestTemplate(45839);
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(quest))
        {
            response.Pois.emplace_back(worldQuest->StartTime, 5178, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);
            response.Pois.emplace_back(worldQuest->StartTime, 5270, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);
            needSend = true;
        }
        quest = sQuestDataStore->GetQuestTemplate(45840);
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(quest))
        {
            response.Pois.emplace_back(worldQuest->StartTime, 5177, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);
            response.Pois.emplace_back(worldQuest->StartTime, 5271, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);
            needSend = true;
        }
    }
    if (sGameEventMgr->IsActiveEvent(117))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[117];
        response.Pois.emplace_back(ged->start, 5252, ged->start * 60, 13321, 1);
        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(118))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[118];
        response.Pois.emplace_back(ged->start, 5261, ged->start * 60, 13321, 9);
        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(119))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[119];
        response.Pois.emplace_back(ged->start, 5257, ged->start * 60, 13321, 5);
        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(120))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[120];
        response.Pois.emplace_back(ged->start, 5260, ged->start * 60, 13321, 8);
        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(121))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[121];
        response.Pois.emplace_back(ged->start, 5254, ged->start * 60, 13321, 2);
        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(122))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[122];
        response.Pois.emplace_back(ged->start, 5259, ged->start * 60, 13321, 7);
        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(123))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[123];
        response.Pois.emplace_back(ged->start, 5258, ged->start * 60, 13321, 6);
        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(124))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[124];
        response.Pois.emplace_back(ged->start, 5256, ged->start * 60, 13321, 4);
        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(125))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[125];
        response.Pois.emplace_back(ged->start, 5255, ged->start * 60, 13321, 3);
        needSend = true;
    }
    // Spring Balloon Festival
    if (sGameEventMgr->IsActiveEvent(87))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[87];
        response.Pois.emplace_back(ged->start, 5191, 0, 13062, 1);
        response.Pois.emplace_back(ged->start, 5192, 0, 13062, 1);
        response.Pois.emplace_back(ged->start, 5193, 0, 13062, 1);
        response.Pois.emplace_back(ged->start, 5195, 0, 13062, 1);
        response.Pois.emplace_back(ged->start, 5196, 0, 13062, 1);
        response.Pois.emplace_back(ged->start, 5197, 0, 13062, 1);
        response.Pois.emplace_back(ged->start, 5198, 0, 13062, 1);
        needSend = true;
    }
    // Glowcap Festival
    if (sGameEventMgr->IsActiveEvent(301))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[301];
        response.Pois.emplace_back(ged->start, 5055, 0, 13107, 1);
        needSend = true;
    }
    // darkmoon
    if (sGameEventMgr->IsActiveEvent(75))
    {
        GameEventData const* ged = &sGameEventMgr->GetEventMap()[75];
        response.Pois.emplace_back(ged->start, 2704, 0, 6078, 1);
        response.Pois.emplace_back(ged->start, 2705, 0, 6078, 1);
        needSend = true;
    }
    // World Bosses Argus
    if (sGameEventMgr->IsActiveEvent(227))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49171)))
            response.Pois.emplace_back(worldQuest->StartTime, 5380, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(226))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49169)))
            response.Pois.emplace_back(worldQuest->StartTime, 5381, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(229))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49166)))
            response.Pois.emplace_back(worldQuest->StartTime, 5379, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(231))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49167)))
            response.Pois.emplace_back(worldQuest->StartTime, 5377, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(228))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49168)))
            response.Pois.emplace_back(worldQuest->StartTime, 5375, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(230))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49170)))
            response.Pois.emplace_back(worldQuest->StartTime, 5376, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    // Invasion Point Argus
    if (sGameEventMgr->IsActiveEvent(180))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49098)))
            response.Pois.emplace_back(worldQuest->StartTime, 5359, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(181))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49091)))
            response.Pois.emplace_back(worldQuest->StartTime, 5372, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(182))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49099)))
            response.Pois.emplace_back(worldQuest->StartTime, 5366, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(183))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(48982)))
            response.Pois.emplace_back(worldQuest->StartTime, 5373, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(184))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49096)))
            response.Pois.emplace_back(worldQuest->StartTime, 5368, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(185))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49091)))
            response.Pois.emplace_back(worldQuest->StartTime, 5360, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(186))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49098)))
            response.Pois.emplace_back(worldQuest->StartTime, 5370, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(187))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49097)))
            response.Pois.emplace_back(worldQuest->StartTime, 5350, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(188))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(48982)))
            response.Pois.emplace_back(worldQuest->StartTime, 5367, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(189))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49099)))
            response.Pois.emplace_back(worldQuest->StartTime, 5371, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(190))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49096)))
            response.Pois.emplace_back(worldQuest->StartTime, 5374, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }
    if (sGameEventMgr->IsActiveEvent(191))
    {
        if (WorldQuest const* worldQuest = sQuestDataStore->GetWorldQuest(sQuestDataStore->GetQuestTemplate(49097)))
            response.Pois.emplace_back(worldQuest->StartTime, 5369, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value);

        needSend = true;
    }

    if (needSend)
        SendPacket(response.Write());

    // if (uint8 eventID = sWorldStateMgr.GetWorldStateValue(13321))
    // {
        // WorldPackets::Quest::AreaPoiUpdate response;
        // switch (eventID)
        // {
            // case 1:
                // response.Pois.push_back(WorldPackets::Quest::WorldQuestUpdateInfo(worldQuest->StartTime, 5271, worldQuest->Timer, worldQuest->VariableID, worldQuest->Value));
        // }
    // }
}
