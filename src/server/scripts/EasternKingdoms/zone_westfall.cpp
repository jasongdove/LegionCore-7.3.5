/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Westfall
SD%Complete: 90
SDComment: Quest support: 155, 1651
SDCategory: Westfall
EndScriptData */

/* ContentData
npc_daphne_stilwell
npc_defias_traitor
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"

enum WestfallCreature
{
    NPC_MERCENARY                     = 42656,
    NPC_AGENT_KEARNEN                 = 7024
};

enum WestfallSpell
{
    SPELL_KILL_SHOT_TRIGGERED        = 79525
};

/*######
## npc_daphne_stilwell
######*/

enum eEnums
{
    SAY_DS_START        = -1000293,
    SAY_DS_DOWN_1       = -1000294,
    SAY_DS_DOWN_2       = -1000295,
    SAY_DS_DOWN_3       = -1000296,
    SAY_DS_PROLOGUE     = -1000297,

    SPELL_SHOOT         = 6660,
    QUEST_TOME_VALOR    = 1651,
    NPC_DEFIAS_RAIDER   = 6180,
    EQUIP_ID_RIFLE      = 2511
};

class npc_daphne_stilwell : public CreatureScript
{
public:
    npc_daphne_stilwell() : CreatureScript("npc_daphne_stilwell") { }

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_TOME_VALOR)
        {
            DoScriptText(SAY_DS_START, creature);

            if (npc_escortAI* pEscortAI = CAST_AI(npc_daphne_stilwell::npc_daphne_stilwellAI, creature->AI()))
                pEscortAI->Start(true, true, player->GetGUID());
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_daphne_stilwellAI(creature);
    }

    struct npc_daphne_stilwellAI : public npc_escortAI
    {
        npc_daphne_stilwellAI(Creature* creature) : npc_escortAI(creature) {}

        uint32 uiWPHolder;
        uint32 uiShootTimer;

        void Reset()
        {
            if (HasEscortState(STATE_ESCORT_ESCORTING))
            {
                switch (uiWPHolder)
                {
                    case 7:
                        DoScriptText(SAY_DS_DOWN_1, me);
                        break;
                    case 8:
                        DoScriptText(SAY_DS_DOWN_2, me);
                        break;
                    case 9:
                        DoScriptText(SAY_DS_DOWN_3, me);
                        break;
                }
            }
            else
                uiWPHolder = 0;

            uiShootTimer = 0;
        }

        void WaypointReached(uint32 waypointId)
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            uiWPHolder = waypointId;

            switch (waypointId)
            {
                case 4:
                    SetEquipmentSlots(false, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE, EQUIP_ID_RIFLE);
                    me->SetSheath(SHEATH_STATE_RANGED);
                    me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING_NO_SHEATHE);
                    break;
                case 7:
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11450.836f, 1569.755f, 54.267f, 4.230f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11449.697f, 1569.124f, 54.421f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.237f, 1568.307f, 54.620f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    break;
                case 8:
                    me->SetSheath(SHEATH_STATE_RANGED);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11450.836f, 1569.755f, 54.267f, 4.230f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11449.697f, 1569.124f, 54.421f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.237f, 1568.307f, 54.620f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.037f, 1570.213f, 54.961f, 4.283f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    break;
                case 9:
                    me->SetSheath(SHEATH_STATE_RANGED);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11450.836f, 1569.755f, 54.267f, 4.230f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11449.697f, 1569.124f, 54.421f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.237f, 1568.307f, 54.620f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.037f, 1570.213f, 54.961f, 4.283f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    me->SummonCreature(NPC_DEFIAS_RAIDER, -11449.018f, 1570.738f, 54.828f, 4.220f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    break;
                case 10:
                    SetRun(false);
                    break;
                case 11:
                    DoScriptText(SAY_DS_PROLOGUE, me);
                    break;
                case 13:
                    SetEquipmentSlots(true);
                    me->SetSheath(SHEATH_STATE_UNARMED);
                    me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING_NO_SHEATHE);
                    break;
                case 17:
                    player->GroupEventHappens(QUEST_TOME_VALOR, me);
                    break;
            }
        }

        void AttackStart(Unit* who)
        {
            if (!who)
                return;

            if (me->Attack(who, false))
            {
                me->AddThreat(who, 0.0f);
                me->SetInCombatWith(who);
                who->SetInCombatWith(me);

                me->GetMotionMaster()->MoveChase(who, 30.0f);
            }
        }

        void JustSummoned(Creature* summoned)
        {
            summoned->AI()->AttackStart(me);
        }

        void Update(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1500;

                if (!me->IsWithinDist(me->getVictim(), ATTACK_DISTANCE))
                    DoCast(me->getVictim(), SPELL_SHOOT);
            } else uiShootTimer -= diff;
        }
    };
};

/*######
## npc_defias_traitor
######*/

#define SAY_START                   -1000101
#define SAY_PROGRESS                -1000102
#define SAY_END                     -1000103
#define SAY_AGGRO_1                 -1000104
#define SAY_AGGRO_2                 -1000105

#define QUEST_DEFIAS_BROTHERHOOD    155

class npc_defias_traitor : public CreatureScript
{
public:
    npc_defias_traitor() : CreatureScript("npc_defias_traitor") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_DEFIAS_BROTHERHOOD)
        {
            if (npc_escortAI* pEscortAI = CAST_AI(npc_defias_traitor::npc_defias_traitorAI, creature->AI()))
                pEscortAI->Start(true, true, player->GetGUID());

            DoScriptText(SAY_START, creature, player);
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_defias_traitorAI(creature);
    }

    struct npc_defias_traitorAI : public npc_escortAI
    {
        npc_defias_traitorAI(Creature* creature) : npc_escortAI(creature) { Reset(); }

        void WaypointReached(uint32 waypointId)
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
                case 35:
                    SetRun(false);
                    break;
                case 36:
                    DoScriptText(SAY_PROGRESS, me, player);
                    break;
                case 44:
                    DoScriptText(SAY_END, me, player);
                    player->GroupEventHappens(QUEST_DEFIAS_BROTHERHOOD, me);
                    break;
            }
        }

        void EnterCombat(Unit* who)
        {
            DoScriptText(RAND(SAY_AGGRO_1, SAY_AGGRO_2), me, who);
        }

        void Reset() {}
    };
};

enum clodoEnum { 

    NPC_HOMELESS_STORMWIND_CITIZEN      = 42384,
    NPC_HOMELESS_STORMWIND_CITIZEN2     = 42386,
    NPC_WEST_PLAINS_DRIFTER             = 42391,
    KILL_CREDIT_WESTFALL_STEW           = 42617

};

class npc_westfall_stew : public CreatureScript
{
public:
    npc_westfall_stew() : CreatureScript("npc_westfall_stew") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_westfall_stewAI (creature);
    }
    
    struct npc_westfall_stewAI : public ScriptedAI
    {
        npc_westfall_stewAI(Creature* creature) : ScriptedAI(creature) {}
        uint32 time;
        bool booltest;
        std::list<Creature*> clodoList;
            
        void Reset()
        {
            time = 30000;
            booltest = true;
            if(me->ToTempSummon() && me->ToTempSummon()->GetSummoner())
            if(Player* invocer = me->ToTempSummon()->GetSummoner()->ToPlayer()) 
            {               
                GetCreatureListWithEntryInGrid(clodoList, me, NPC_HOMELESS_STORMWIND_CITIZEN, 15.0f);
                for (std::list<Creature*>::iterator itr = clodoList.begin(); itr != clodoList.end(); ++itr)
                {
                    if((*itr)->getStandState() != UNIT_STAND_STATE_SIT)
                    {
                        (*itr)->GetMotionMaster()->MoveFollow(me, 1, me->GetAngle((*itr)));
                        (*itr)->SetStandState(UNIT_STAND_STATE_SIT);
                        invocer->KilledMonsterCredit(KILL_CREDIT_WESTFALL_STEW, ObjectGuid::Empty);
                    }
                }               
            }
        }
        void UpdateAI(uint32 diff)
        {
            if(booltest)
            {
                if (time < diff)
                {
                    for (std::list<Creature*>::iterator itr = clodoList.begin(); itr != clodoList.end(); ++itr)
                    
                    {
                        (*itr)->SetStandState(UNIT_STAND_STATE_STAND);
                        (*itr)->SetDefaultMovementType(RANDOM_MOTION_TYPE);                   
                    } 
                    me->DespawnOrUnsummon();
                    booltest = false;
                }
                else 
                    time -= diff;
            }
        }
    };

};

class spell_westfall_unbound_energy : public SpellScript
{
    PrepareSpellScript(spell_westfall_unbound_energy);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Unit* caster = GetCaster();
        targets.remove_if([caster](WorldObject const* target)->bool
        {
            return caster == target;
        });

        if (targets.size() > 1)
            Trinity::Containers::RandomResizeList(targets, 1);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_westfall_unbound_energy::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
    }
};

enum ItsAlive
{
    // Events
    EVENT_CHECK_AREA                = 1,
    EVENT_DESPAWN_HARVESTER         = 2,

    // Texts
    SAY_ANNOUNCE_OUT_OF_AREA        = 0,

    // Area Ids
    AREA_ID_THE_MOEST_FARM          = 918,

    // Creatures
    NPC_ENERGIZED_HARVEST_REAPER    = 42342,
    NPC_OVERLOADED_HARVEST_GOLEM    = 42601
};

struct npc_westfall_overloaded_harvest_golem : public VehicleAI
{
    npc_westfall_overloaded_harvest_golem(Creature* creature) : VehicleAI(creature) { }

    void Reset() override
    {
        _events.ScheduleEvent(EVENT_CHECK_AREA, 1s);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);
        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_CHECK_AREA:
                    if (me->GetAreaId() != AREA_ID_THE_MOEST_FARM)
                    {
                        if (Unit* owner = me->GetCharmerOrOwner())
                            Talk(SAY_ANNOUNCE_OUT_OF_AREA, owner->GetGUID());
                        _events.ScheduleEvent(EVENT_DESPAWN_HARVESTER, 8s);
                    }
                    else
                        _events.Repeat(1s);
                    break;
                case EVENT_DESPAWN_HARVESTER:
                    if (me->GetAreaId() != AREA_ID_THE_MOEST_FARM)
                        me->DespawnOrUnsummon();
                    else
                        _events.ScheduleEvent(EVENT_CHECK_AREA, 1s);
                    break;
                default:
                    break;
            }
        }
    }

private:
    EventMap _events;
};

class spell_westfall_reaping_blows : public AuraScript
{
    PrepareAuraScript(spell_westfall_reaping_blows);

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();
        if (Creature* reaper = GetTarget()->FindNearestCreature(NPC_ENERGIZED_HARVEST_REAPER, 5.f, true))
            GetTarget()->CastSpell(reaper, GetSpellInfo()->Effects[EFFECT_1]->TriggerSpell, true);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_westfall_reaping_blows::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_westfall_wake_harvest_golem : public SpellScript
{
    PrepareSpellScript(spell_westfall_wake_harvest_golem);

    SpellCastResult CheckTarget()
    {
        Unit* target = GetExplTargetUnit();
        if (!target || !target->IsCreature())
            return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->IsPlayer())
            return;

        if (Creature* target = GetHitCreature())
        {
            caster->ToPlayer()->KilledMonsterCredit(NPC_OVERLOADED_HARVEST_GOLEM);
            target->DespawnOrUnsummon(100ms);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_westfall_wake_harvest_golem::CheckTarget);
        OnEffectHitTarget += SpellEffectFn(spell_westfall_wake_harvest_golem::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_westfall_sniper_fire_proc : public AuraScript
{
    PrepareAuraScript(spell_westfall_sniper_fire_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        _target = (eventInfo.GetProcTarget() == GetTarget() ? eventInfo.GetActor() : eventInfo.GetProcTarget());
        return _target && _target->IsCreature() && _target->GetEntry() == NPC_MERCENARY;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(_target, GetSpellInfo()->Effects[aurEff->GetEffIndex()]->TriggerSpell);

    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_westfall_sniper_fire_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_westfall_sniper_fire_proc::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }

private:
    Unit* _target = nullptr;
};

enum AgentKearnenText
{
    SAY_0 = 0
};

class spell_westfall_sniper_fire : public SpellScript
{
    PrepareSpellScript(spell_westfall_sniper_fire);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_KILL_SHOT_TRIGGERED });
    }

    void HandleDummyEffect(SpellEffIndex /*effIndex*/)
    {
        Unit* target = GetHitUnit();
        Unit* caster = GetCaster();
        if (caster && target)
            if (Creature* agent = caster->FindNearestCreature(NPC_AGENT_KEARNEN, 100.f))
            {
                agent->CastSpell(target, SPELL_KILL_SHOT_TRIGGERED); // 79525
                if (agent->IsAIEnabled)
                    agent->AI()->Talk(SAY_0, caster->GetGUID());
            }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_westfall_sniper_fire::HandleDummyEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_westfall()
{
    new npc_daphne_stilwell();
    new npc_defias_traitor();
    new npc_westfall_stew();
    RegisterSpellScript(spell_westfall_unbound_energy);
    RegisterCreatureAI(npc_westfall_overloaded_harvest_golem);
    RegisterAuraScript(spell_westfall_reaping_blows);
    RegisterSpellScript(spell_westfall_wake_harvest_golem);
    RegisterAuraScript(spell_westfall_sniper_fire_proc);
    RegisterSpellScript(spell_westfall_sniper_fire);
}
