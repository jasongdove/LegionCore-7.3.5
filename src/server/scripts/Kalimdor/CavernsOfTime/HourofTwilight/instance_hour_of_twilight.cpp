#include "hour_of_twilight.h"

#define MAX_ENCOUNTER 3

static const DoorData doordata[] = 
{
    {GO_ICEWALL_1, DATA_ARCURION,   DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {GO_ICEWALL_2, DATA_ARCURION,   DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_GATE,      DATA_BENEDICTUS, DOOR_TYPE_ROOM,     BOUNDARY_NONE}
};

class instance_hour_of_twilight : public InstanceMapScript
{
    public:
        instance_hour_of_twilight() : InstanceMapScript("instance_hour_of_twilight", 940) { }

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_hour_of_twilight_InstanceMapScript(map);
        }

        struct instance_hour_of_twilight_InstanceMapScript : public InstanceScript
        {
            instance_hour_of_twilight_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetHeaders(DataHeader);
                SetBossNumber(MAX_ENCOUNTER);
                LoadDoorData(doordata);
                
                uiAsira.Clear();
            }
            
            void OnCreatureCreate(Creature* pCreature)
            {
                switch (pCreature->GetEntry())
                {
                    case NPC_ASIRA:
                        uiAsira = pCreature->GetGUID();
                        if (GetBossState(DATA_ASIRA)==DONE)
                            pCreature->SummonCreature(NPC_LIFE_WARDEN_2, drakePos);
                        break;
                    default:
                        break;
                }                
            }

            void OnGameObjectCreate(GameObject* pGo)
            {
                switch (pGo->GetEntry())
                {
                    case GO_ICEWALL_1:
                    case GO_ICEWALL_2:
                    case GO_GATE:
                        AddDoor(pGo, true);
                        break;
                    default:
                        break;
                }
            }

            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                return true;
            }

            private:
                ObjectGuid uiAsira;
        };
};

void AddSC_instance_hour_of_twilight()
{
    new instance_hour_of_twilight();
}