#include "shadowfang_keep.h"

DoorData const doorData[] =
{
    {GO_COURTYARD_DOOR, DATA_ASHBURY,   DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_SORCERER_DOOR,  DATA_VALDEN,    DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_ARUGAL_DOOR,    DATA_VALDEN,    DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_ARUGAL_DOOR,    DATA_GODFREY,   DOOR_TYPE_ROOM,     BOUNDARY_NONE},
};

class instance_shadowfang_keep : public InstanceMapScript
{
    public:
        instance_shadowfang_keep() : InstanceMapScript("instance_shadowfang_keep", 33) { }

        InstanceScript* GetInstanceScript(InstanceMap* pMap) const
        {
            return new instance_shadowfang_keep_InstanceMapScript(pMap);
        }

        struct instance_shadowfang_keep_InstanceMapScript : public InstanceScript
        {
            instance_shadowfang_keep_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetHeaders(DataHeader);
                SetBossNumber(EncounterCount);
                LoadDoorData(doorData);
                uiAshburyGUID.Clear();
                uiSilverlaineGUID.Clear();
                uiSpringvaleGUID.Clear();
                uiValdenGUID.Clear();
                uiGodfreyGUID.Clear();
                teamInInstance = 0;
            };

            void OnPlayerEnter(Player* player) override
            {
                if (!teamInInstance)
                    teamInInstance = player->GetTeam();
            }

            void OnCreatureCreate(Creature* creature)
            {
                if (!teamInInstance)
                {
                    Map::PlayerList const &players = instance->GetPlayers();
                    if (!players.isEmpty())
                        if (Player* player = players.begin()->getSource())
                            teamInInstance = player->GetTeam();
                }

                switch(creature->GetEntry())
                {
                    case NPC_BELMONT:
                        if (teamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_IVAR);
                        break;
                    case NPC_GUARD_HORDE1:
                        if (teamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_GUARD_ALLY);
                        break;
                    case NPC_GUARD_HORDE2:
                        if (teamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_GUARD_ALLY);
                        break;
                    case NPC_CROMUSH:
                        if (teamInInstance == ALLIANCE)
                            creature->SetPhaseMask(2, true);
                        break;
                    case NPC_ASHBURY:
                        uiAshburyGUID = creature->GetGUID();
                        break;
                    case NPC_SILVERLAINE:
                        uiSilverlaineGUID = creature->GetGUID();
                        break;
                    case NPC_SPRINGVALE:
                        uiSpringvaleGUID = creature->GetGUID();
                        break;
                    case NPC_VALDEN:
                        uiValdenGUID = creature->GetGUID();
                        break;
                    case NPC_GODFREY:
                        uiGodfreyGUID = creature->GetGUID();
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch(go->GetEntry())
                {
                    case GO_COURTYARD_DOOR:
                    case GO_SORCERER_DOOR:
                    case GO_ARUGAL_DOOR:
                        AddDoor(go, true);
                        break;
                }
            }

            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;
                return true;
            }

            uint32 GetData(uint32 type) const override
            {
                if (type == DATA_TEAM)
                    return teamInInstance;

                return 0;
            }

            ObjectGuid GetGuidData(uint32 data) const
            {
                switch (data)
                {
                    case DATA_ASHBURY: return uiAshburyGUID;
                    case DATA_SILVERLAINE: return uiSilverlaineGUID;
                    case DATA_SPRINGVALE: return uiSpringvaleGUID;
                    case DATA_VALDEN: return uiValdenGUID;
                    case DATA_GODFREY: return uiGodfreyGUID;
                }
                return ObjectGuid::Empty;
            }

        private:
            ObjectGuid uiAshburyGUID;
            ObjectGuid uiSilverlaineGUID;
            ObjectGuid uiSpringvaleGUID;
            ObjectGuid uiValdenGUID;
            ObjectGuid uiGodfreyGUID;
            uint32 teamInInstance;
        };

};


void AddSC_instance_shadowfang_keep()
{
    new instance_shadowfang_keep();
}