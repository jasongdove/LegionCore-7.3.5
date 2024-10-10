#include "the_vortex_pinnacle.h"

#define MAX_ENCOUNTER 3

class instance_the_vortex_pinnacle : public InstanceMapScript
{
    public:
        instance_the_vortex_pinnacle() : InstanceMapScript("instance_the_vortex_pinnacle", 657) { }
        
        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_the_vortex_pinnacle_InstanceMapScript(map);
        }

        struct instance_the_vortex_pinnacle_InstanceMapScript: public InstanceScript
        {
            instance_the_vortex_pinnacle_InstanceMapScript(InstanceMap* map) : InstanceScript(map) { }

            ObjectGuid uiGrandVizierErtanGUID;
            ObjectGuid uiAltairusGUID;
            ObjectGuid uiAsaadGUID;
            uint8 OrbsCount;

            void Initialize()
            {
                SetHeaders(DataHeader);
                SetBossNumber(MAX_ENCOUNTER);
                uiGrandVizierErtanGUID.Clear();
                uiAltairusGUID.Clear();
                uiAsaadGUID.Clear();
                OrbsCount = 0;
            }

            void OnPlayerEnter(Player* player)
            {
                player->SendUpdateWorldState(5649, OrbsCount);
            }

            void OnCreatureCreate(Creature* pCreature)
            {
                switch(pCreature->GetEntry())
                {
                    case NPC_GRAND_VIZIER_ERTAN:
                        uiGrandVizierErtanGUID = pCreature->GetGUID();
                        break;
                    case NPC_ALTAIRUS:
                        uiAltairusGUID = pCreature->GetGUID();
                        break;
                    case NPC_ASAAD:
                        uiAsaadGUID = pCreature->GetGUID();
                        break;
                }
            }

            void SetData(uint32 data, uint32 value)
            {
                switch (data)
                {
                    case DATA_ORB:
                        OrbsCount = value;
                        break;
                    default:
                        break;
                }
            }

            uint32 GetData(uint32 type) const override
            {
                switch (type)
                {
                    case DATA_ORB:
                        return OrbsCount;
                }
    
                return 0;
            }

            ObjectGuid GetGuidData(uint32 identifier) const
            {
                switch(identifier)
                {
                    case DATA_ERTAN:
                        return uiGrandVizierErtanGUID;
                    case DATA_ALTAIRUS:
                        return uiAltairusGUID;
                    case DATA_ASAAD:
                        return uiAsaadGUID;
                }
                return ObjectGuid::Empty;
            }
        };
};

void AddSC_instance_the_vortex_pinnacle()
{
    new instance_the_vortex_pinnacle();
}
