#include "baradin_hold.h"

DoorData const doorData[] =
{
    {GO_TOLBARAD_DOOR_2,    DATA_ARGALOTH,  DOOR_TYPE_ROOM,       BOUNDARY_NONE},
    {GO_CELL_DOOR,          DATA_OCCUTHAR,  DOOR_TYPE_ROOM,       BOUNDARY_NONE},
    {GO_TOLBARAD_DOOR_1,    DATA_ALIZABAL,  DOOR_TYPE_ROOM,       BOUNDARY_NONE},
    {0,                     0,              DOOR_TYPE_ROOM,       BOUNDARY_NONE}, // END
};

class instance_baradin_hold : public InstanceMapScript
{
    public:
        instance_baradin_hold() : InstanceMapScript("instance_baradin_hold", 757) { }

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_baradin_hold_InstanceMapScript(map);
        }

        struct instance_baradin_hold_InstanceMapScript : public InstanceScript
        {
            instance_baradin_hold_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetHeaders(DataHeader);
                SetBossNumber(MAX_ENCOUNTER);
                LoadDoorData(doorData);
            }
            
            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;
                
                return true;
            }

            void OnGameObjectCreate(GameObject* pGo)
            {
                switch (pGo->GetEntry())
                {
                    case GO_TOLBARAD_DOOR_2:
                    case GO_CELL_DOOR:
                    case GO_TOLBARAD_DOOR_1:
                        AddDoor(pGo, true);
                        break;
                }
            }
        };
};

void AddSC_instance_baradin_hold()
{
    new instance_baradin_hold();
}
