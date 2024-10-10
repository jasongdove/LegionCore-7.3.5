#include "the_stonecore.h"

class instance_the_stonecore : public InstanceMapScript
{
public:
    instance_the_stonecore() : InstanceMapScript("instance_the_stonecore", 725) {}

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_the_stonecore_InstanceMapScript(map);
    }

    struct instance_the_stonecore_InstanceMapScript : public InstanceScript
    {
        instance_the_stonecore_InstanceMapScript(InstanceMap* map) : InstanceScript(map) {};

        void Initialize() override
        {
            SetHeaders(DataHeader);
            SetBossNumber(MAX_ENCOUNTER);
        }

        bool SetBossState(uint32 type, EncounterState state) override
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            return true;
        }
    };
};

void AddSC_instance_the_stonecore()
{
    new instance_the_stonecore();
}