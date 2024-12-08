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

#ifndef GOSSIP_H
#define GOSSIP_H

#include "Common.h"
#include "QuestDef.h"
#include "NPCHandler.h"

class WorldSession;

#define GOSSIP_MAX_MENU_ITEMS 64                            // client supported items unknown, but provided number must be enough
#define DEFAULT_GOSSIP_MESSAGE              0xffffff

enum class GossipOptionNpc : uint8
{
    None                            = 0,                    // white chat bubble
    Vendor                          = 1,                    // brown bag
    TaxiNode                        = 2,                    // flightmarker (paperplane)
    Trainer                         = 3,                    // brown book (trainer)
    SpiritHealer                    = 4,                    // golden interaction wheel
    Binder                          = 5,                    // golden interaction wheel
    Banker                          = 6,                    // brown bag (with gold coin in lower corner)
    PetitionVendor                  = 7,                    // white chat bubble (with "..." inside)
    TabardVendor                    = 8,                    // white tabard
    BattleMaster                    = 9,                    // two crossed swords
    Auctioneer                      = 10,                   // yellow dot/point
    TalentMaster                    = 11,                   // white chat bubble
    StableMaster                    = 12,                   // white chat bubble
    PetSpecializationMaster         = 13,                   /*DEPRECATED*/ // White chat bubble
    GuildBanker                     = 14,                   /*NYI*/ // White chat bubble
    SpellClick                      = 15,                   /*NYI*/ // White chat bubble
    DisableXPGain                   = 16,                   // White chat bubble
    EnableXPGain                    = 17,                   // White chat bubble
    Mailbox                         = 18,                   // white chat bubble
    WorldPVPQueue                   = 19,                   // white chat bubble
    GOSSIP_ICON_CHAT_20             = 20,                   // white chat bubble
    ArtifactRespec                  = 21,
    SpecializationMaster            = 23,                   /*DEPRECATED*/ // White chat bubble
    GlyphMaster                     = 24,                   /*DEPRECATED*/ // White chat bubble
    GarrisonArchitect               = 26,
    GarrisonMission                 = 27,
    ShipmentCrafter                 = 28,                   // auto-click?
    GarrisonTradeskill              = 29,
    GarrisonRecruitment             = 30,
    AdventureMap                    = 31,
    GarrisonTalent                  = 32,                   //UNIT_NPC_FLAG2_CLASS_HALL_UPGRADE
    Transmogrify                    = 34,                   // transmogrifier

    Count
};

//POI icons. Many more exist, list not complete.
enum Poi_Icon
{
    ICON_POI_BLANK              =   0,                      // Blank (not visible)
    ICON_POI_GREY_AV_MINE       =   1,                      // Grey mine lorry
    ICON_POI_RED_AV_MINE        =   2,                      // Red mine lorry
    ICON_POI_BLUE_AV_MINE       =   3,                      // Blue mine lorry
    ICON_POI_BWTOMB             =   4,                      // Blue and White Tomb Stone
    ICON_POI_SMALL_HOUSE        =   5,                      // Small house
    ICON_POI_GREYTOWER          =   6,                      // Grey Tower
    ICON_POI_REDFLAG            =   7,                      // Red Flag w/Yellow !
    ICON_POI_TOMBSTONE          =   8,                      // Normal tomb stone (brown)
    ICON_POI_BWTOWER            =   9,                      // Blue and White Tower
    ICON_POI_REDTOWER           =   10,                     // Red Tower
    ICON_POI_BLUETOWER          =   11,                     // Blue Tower
    ICON_POI_RWTOWER            =   12,                     // Red and White Tower
    ICON_POI_REDTOMB            =   13,                     // Red Tomb Stone
    ICON_POI_RWTOMB             =   14,                     // Red and White Tomb Stone
    ICON_POI_BLUETOMB           =   15,                     // Blue Tomb Stone
    ICON_POI_16                 =   16,                     // Grey ?
    ICON_POI_17                 =   17,                     // Blue/White ?
    ICON_POI_18                 =   18,                     // Blue ?
    ICON_POI_19                 =   19,                     // Red and White ?
    ICON_POI_20                 =   20,                     // Red ?
    ICON_POI_GREYLOGS           =   21,                     // Grey Wood Logs
    ICON_POI_BWLOGS             =   22,                     // Blue and White Wood Logs
    ICON_POI_BLUELOGS           =   23,                     // Blue Wood Logs
    ICON_POI_RWLOGS             =   24,                     // Red and White Wood Logs
    ICON_POI_REDLOGS            =   25,                     // Red Wood Logs
    ICON_POI_26                 =   26,                     // Grey ?
    ICON_POI_27                 =   27,                     // Blue and White ?
    ICON_POI_28                 =   28,                     // Blue ?
    ICON_POI_29                 =   29,                     // Red and White ?
    ICON_POI_30                 =   30,                     // Red ?
    ICON_POI_GREYHOUSE          =   31,                     // Grey House
    ICON_POI_BWHOUSE            =   32,                     // Blue and White House
    ICON_POI_BLUEHOUSE          =   33,                     // Blue House
    ICON_POI_RWHOUSE            =   34,                     // Red and White House
    ICON_POI_REDHOUSE           =   35,                     // Red House
    ICON_POI_GREYHORSE          =   36,                     // Grey Horse
    ICON_POI_BWHORSE            =   37,                     // Blue and White Horse
    ICON_POI_BLUEHORSE          =   38,                     // Blue Horse
    ICON_POI_RWHORSE            =   39,                     // Red and White Horse
    ICON_POI_REDHORSE           =   40                      // Red Horse
};

struct GossipMenuItem
{
    GossipOptionNpc OptionNpc;
    uint32 Sender;
    uint32 Action;
    uint32 BoxMoney;
    std::string Message;
    std::string BoxMessage;
    bool IsCoded;
};

// need an ordered container
typedef std::map<uint32, GossipMenuItem> GossipMenuItemContainer;

struct GossipMenuItemData
{
    uint32 GossipActionMenuId;  // MenuID of the gossip triggered by this action
    uint32 GossipActionPoi;
};

// need an ordered container
typedef std::map<uint32, GossipMenuItemData> GossipMenuItemDataContainer;

struct QuestMenuItem
{
    uint32 QuestId;
    uint8 QuestIcon;
};

typedef std::vector<QuestMenuItem> QuestMenuItemList;

class TC_GAME_API GossipMenu
{
    GossipMenuItemContainer _menuItems;
    GossipMenuItemDataContainer _menuItemData;
    LocaleConstant _locale;
    uint32 _menuId;
public:
    GossipMenu();
    ~GossipMenu();

    void AddMenuItem(int32 menuItemId, GossipOptionNpc icon, std::string const& message, uint32 sender, uint32 action, std::string const& boxMessage, uint32 boxMoney, bool coded = false);
    void AddMenuItem(uint32 menuId, uint32 menuItemId, uint32 sender, uint32 action);

    void SetMenuId(uint32 menu_id);
    uint32 GetMenuId() const;
    void SetLocale(LocaleConstant locale);
    LocaleConstant GetLocale() const;

    void AddGossipMenuItemData(uint32 menuItemId, uint32 gossipActionMenuId, uint32 gossipActionPoi);

    uint32 GetMenuItemCount() const;
    bool Empty() const;
    GossipMenuItem const* GetItem(uint32 id) const;
    GossipMenuItemData const* GetItemData(uint32 indexId) const;

    uint32 GetMenuItemSender(uint32 menuItemId) const;
    uint32 GetMenuItemAction(uint32 menuItemId) const;
    bool IsMenuItemCoded(uint32 menuItemId) const;

    void ClearMenu();
    GossipMenuItemContainer const& GetMenuItems() const;

    static uint64 GetRequiredNpcFlagForOption(GossipOptionNpc optionNpc);
};

class TC_GAME_API QuestMenu
{
    QuestMenuItemList _questMenuItems;
public:
    QuestMenu();
    ~QuestMenu();

    void AddMenuItem(uint32 QuestId, uint8 Icon);
    void ClearMenu();

    uint8 GetMenuItemCount() const;
    bool Empty() const;
    bool HasItem(uint32 questId) const;
    QuestMenuItem const& GetItem(uint16 index) const;
};

class TC_GAME_API PlayerMenu
{
    GossipMenu _gossipMenu;
    QuestMenu  _questMenu;
    WorldSession* _session;
public:
    explicit PlayerMenu(WorldSession* session);
    ~PlayerMenu();

    GossipMenu& GetGossipMenu();
    QuestMenu& GetQuestMenu();

    bool Empty() const;

    void ClearMenus();
    uint32 GetGossipOptionSender(uint32 selection) const;
    uint32 GetGossipOptionAction(uint32 selection) const;
    bool IsGossipOptionCoded(uint32 selection) const;

    void SendGossipMenu(uint32 titleTextId, ObjectGuid objectGUID) const;
    void SendCloseGossip() const;
    void SendPointOfInterest(uint32 poiId) const;
    void SendQuestGiverStatus(QuestGiverStatus questStatus, ObjectGuid npcGUID) const;
    void SendQuestGiverQuestList(uint32 BroadcastTextID, ObjectGuid npcGUID);
    void SendQuestQueryResponse(uint32 questId) const;
    void SendQuestGiverQuestDetails(Quest const* quest, ObjectGuid npcGUID, bool autoLaunched, bool displayPopup, bool isArea = false, uint32 questStartItemId = 0) const;
    void SendQuestGiverOfferReward(Quest const* quest, ObjectGuid npcGUID, bool autoLaunched) const;
    void SendQuestGiverRequestItems(Quest const* quest, ObjectGuid npcGUID, bool canComplete, bool autoLaunched) const;
};
#endif
