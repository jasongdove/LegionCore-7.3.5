#include "GossipData.h"
#include "DatabaseEnv.h"
#include "ObjectMgr.h"
#include "GossipDef.h"
#include "QuestData.h"

GossipDataStoreMgr::GossipDataStoreMgr() = default;

GossipDataStoreMgr::~GossipDataStoreMgr() = default;

GossipDataStoreMgr* GossipDataStoreMgr::instance()
{
    static GossipDataStoreMgr instance;
    return &instance;
}

void GossipDataStoreMgr::LoadGossipMenuItemsLocales()
{
    auto oldMSTime = getMSTime();

    _gossipMenuItemsLocaleStore.clear();

    //                                                    0       1         2       3           4
    auto result = WorldDatabase.Query("SELECT MenuID, OptionID, Locale, OptionText, BoxText FROM gossip_menu_option_locale");
    if (!result)
        return;

    do
    {
        auto fields = result->Fetch();
        auto locale = GetLocaleByName(fields[2].GetString());
        if (locale == LOCALE_none)
            continue;


        auto& data = _gossipMenuItemsLocaleStore[MAKE_PAIR32(fields[0].GetUInt16(), fields[1].GetUInt16())];
        ObjectMgr::AddLocaleString(fields[3].GetString(), locale, data.OptionText);
        ObjectMgr::AddLocaleString(fields[4].GetString(), locale, data.BoxText);

    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u gossip_menu_option locale strings in %u ms", static_cast<uint32>(_gossipMenuItemsLocaleStore.size()), GetMSTimeDiffToNow(oldMSTime));
}

void GossipDataStoreMgr::LoadGossipMenu()
{
    auto oldMSTime = getMSTime();

    _gossipMenusStore.clear();

    auto result = WorldDatabase.Query("SELECT MenuID, TextID FROM gossip_menu");
    if (!result)
    {
        TC_LOG_ERROR("server.loading", ">> Loaded 0  gossip_menu entries. DB table `gossip_menu` is empty!");
        return;
    }

    do
    {
        auto fields = result->Fetch();

        GossipMenus gMenu;
        gMenu.MenuID = fields[0].GetUInt32();
        gMenu.TextID = fields[1].GetUInt32();

        if (!sObjectMgr->GetNpcText(gMenu.TextID))
        {
            TC_LOG_ERROR("sql.sql", "Table gossip_menu Entry %u are using non-existing TextID %u", gMenu.MenuID, gMenu.TextID);
            continue;
        }

        _gossipMenusStore.insert(std::make_pair(gMenu.MenuID, gMenu));
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u gossip_menu entries in %u ms", (uint32)_gossipMenusStore.size(), GetMSTimeDiffToNow(oldMSTime));
}

void GossipDataStoreMgr::LoadGossipMenuItems()
{
    auto oldMSTime = getMSTime();

    _gossipMenuItemsStore.clear();

        //                                                0       1         2           3          4             5            6         7         8
    auto result = WorldDatabase.Query("SELECT MenuID, OptionID, OptionNpc, OptionText, ActionMenuID, ActionPoiID, BoxCoded, BoxMoney, BoxText, "
        //9                     10
        "OptionBroadcastTextID, BoxBroadcastTextID FROM gossip_menu_option ORDER BY MenuID, OptionID");

    if (!result)
    {
        TC_LOG_ERROR("server.loading", ">> Loaded 0 gossip_menu_option entries. DB table `gossip_menu_option` is empty!");
        return;
    }

    uint32 count = 0;

    do
    {
        auto fields = result->Fetch();

        GossipMenuItems gMenuItem;
        gMenuItem.MenuID = fields[0].GetUInt32();
        gMenuItem.OptionIndex = fields[1].GetUInt16();
        gMenuItem.OptionNpc = GossipOptionNpc(fields[2].GetUInt8());
        gMenuItem.OptionText = fields[3].GetString();
        gMenuItem.ActionMenuID = fields[4].GetUInt32();
        gMenuItem.ActionPoiID = fields[5].GetUInt32();
        gMenuItem.BoxCoded = fields[6].GetBool();
        gMenuItem.BoxMoney = fields[7].GetUInt32();
        gMenuItem.BoxText = fields[8].GetString();
        gMenuItem.OptionBroadcastTextID = fields[9].GetUInt32();
        gMenuItem.BoxBroadcastTextID = fields[10].GetUInt32();

        if (gMenuItem.OptionNpc >= GossipOptionNpc::Count)
        {
            TC_LOG_ERROR("sql.sql", "Table gossip_menu_option for menu %u, id %u has unknown NPC option id %u. Replacing with GossipOptionNpc::None", gMenuItem.MenuID, gMenuItem.OptionIndex, AsUnderlyingType(gMenuItem.OptionNpc));
            gMenuItem.OptionNpc = GossipOptionNpc::None;
        }

        if (gMenuItem.ActionMenuID && gMenuItem.OptionNpc != GossipOptionNpc::None)
        {
            TC_LOG_ERROR("sql.sql", "Table `gossip_menu_option` for menu %u, id %u can not use ActionMenuID for GossipOptionNpc different from GossipOptionNpc::None, ignoring", gMenuItem.MenuID, gMenuItem.OptionIndex);
            gMenuItem.ActionMenuID = 0;
        }

        if (gMenuItem.ActionPoiID)
        {
            if (gMenuItem.OptionNpc != GossipOptionNpc::None)
                TC_LOG_ERROR("sql.sql", "Table `gossip_menu_option` for menu %u, id %u can not use ActionPoiID for GossipOptionNpc different from GossipOptionNpc::None, ignoring", gMenuItem.MenuID, gMenuItem.OptionIndex);
            else if (!sQuestDataStore->GetPointOfInterest(gMenuItem.ActionPoiID))
                TC_LOG_ERROR("sql.sql", "Table `gossip_menu_option` for menu %u, id %u use non-existing ActionPoiID %u, ignoring", gMenuItem.MenuID, gMenuItem.OptionIndex, gMenuItem.ActionPoiID);

            gMenuItem.ActionPoiID = 0;
        }

        if (gMenuItem.OptionBroadcastTextID && !sBroadcastTextStore.LookupEntry(gMenuItem.OptionBroadcastTextID))
        {
            TC_LOG_ERROR("sql.sql", "Table `gossip_menu_option` for menu %u, id %u has non-existing or incompatible OptionBroadcastTextId %u, ignoring.", gMenuItem.MenuID, gMenuItem.OptionIndex, gMenuItem.OptionBroadcastTextID);
            gMenuItem.OptionBroadcastTextID = 0;
        }

        if (gMenuItem.BoxBroadcastTextID && !sBroadcastTextStore.LookupEntry(gMenuItem.BoxBroadcastTextID))
        {
            TC_LOG_ERROR("sql.sql", "Table `gossip_menu_option` for menu %u, id %u has non-existing or incompatible BoxBroadcastTextID %u, ignoring.", gMenuItem.MenuID, gMenuItem.OptionIndex, gMenuItem.BoxBroadcastTextID);
            gMenuItem.BoxBroadcastTextID = 0;
        }

        _gossipMenuItemsStore.insert(std::make_pair(gMenuItem.MenuID, gMenuItem));
        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u gossip_menu_option entries in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

GossipMenuItemsLocale const* GossipDataStoreMgr::GetGossipMenuItemsLocale(uint32 entry) const
{
    return Trinity::Containers::MapGetValuePtr(_gossipMenuItemsLocaleStore, entry);
}

GossipMenusMapBounds GossipDataStoreMgr::GetGossipMenusMapBounds(uint32 uiMenuId) const
{
    return _gossipMenusStore.equal_range(uiMenuId);
}

GossipMenusMapBoundsNonConst GossipDataStoreMgr::GetGossipMenusMapBoundsNonConst(uint32 uiMenuId)
{
    return _gossipMenusStore.equal_range(uiMenuId);
}

GossipMenuItemsMapBounds GossipDataStoreMgr::GetGossipMenuItemsMapBounds(uint32 uiMenuId) const
{
    return _gossipMenuItemsStore.equal_range(uiMenuId);
}

GossipMenuItemsMapBoundsNonConst GossipDataStoreMgr::GetGossipMenuItemsMapBoundsNonConst(uint32 uiMenuId)
{
    return _gossipMenuItemsStore.equal_range(uiMenuId);
}
