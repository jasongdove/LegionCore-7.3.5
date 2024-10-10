#include "grim_batol.h"

class instance_grim_batol : public InstanceMapScript
{
public:
    instance_grim_batol() : InstanceMapScript("instance_grim_batol", 670) {}

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_grim_batol_InstanceMapScript(map);
    }

    struct instance_grim_batol_InstanceMapScript : public InstanceScript
    {
        instance_grim_batol_InstanceMapScript(InstanceMap* map) : InstanceScript(map) {}
        
        ObjectGuid uiGeneralUmbrissGUID;
        ObjectGuid uiForgemasterThrongusGUID;
        ObjectGuid uiDrahgaShadowburnerGUID;
        ObjectGuid uiErudaxGUID;
        
        void Initialize() override
        {
            SetHeaders(DataHeader);
            SetBossNumber(MAX_ENCOUNTER);
                
            uiGeneralUmbrissGUID.Clear();
            uiForgemasterThrongusGUID.Clear();
            uiDrahgaShadowburnerGUID.Clear();
            uiErudaxGUID.Clear();
        }     
        
        void OnCreatureCreate(Creature* creature) override
        {
            switch(creature->GetEntry())
            {
                case NPC_GENERAL_UMBRISS:
                    uiGeneralUmbrissGUID = creature->GetGUID();
                    break;
                case NPC_FORGEMASTER_THRONGUS:
                    uiForgemasterThrongusGUID = creature->GetGUID();
                    break;
                case NPC_DRAHGA_SHADOWBURNER:
                    uiDrahgaShadowburnerGUID = creature->GetGUID();
                    break;
                case NPC_ERUDAX:
                    uiErudaxGUID = creature->GetGUID();
                    break;
            }
        }
        
        ObjectGuid GetGuidData(uint32 identifier) const
        {
            switch(identifier)
            {
                case DATA_GENERAL_UMBRISS:
                    return uiGeneralUmbrissGUID;
                case DATA_FORGEMASTER_THRONGUS:
                    return uiForgemasterThrongusGUID;
                case DATA_DRAHGA_SHADOWBURNER:
                    return uiDrahgaShadowburnerGUID;
                case DATA_ERUDAX:
                    return uiErudaxGUID;
            }
            return ObjectGuid::Empty;
        }
    };
};

void AddSC_instance_grim_batol()
{
    new instance_grim_batol();
}
