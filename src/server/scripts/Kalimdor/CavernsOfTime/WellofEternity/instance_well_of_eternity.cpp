#include "ScriptedEscortAI.h"
#include "well_of_eternity.h"

#define MAX_ENCOUNTER 5

class instance_well_of_eternity : public InstanceMapScript
{
public:
    instance_well_of_eternity() : InstanceMapScript("instance_well_of_eternity", 939) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_well_of_eternity_InstanceMapScript(map);
    }

    struct instance_well_of_eternity_InstanceMapScript : public InstanceScript
    {
        instance_well_of_eternity_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            SetHeaders(DataHeader);
            SetBossNumber(MAX_ENCOUNTER);
            //LoadDoorData(doordata);
        }

        void OnPlayerEnter(Player* pPlayer)
        {
            if (!uiTeamInInstance)
                uiTeamInInstance = pPlayer->GetTeam();
        }

        void OnCreatureCreate(Creature* pCreature)
        {
        }

        void SetData(uint32 type, uint32 data)
        {
        }

        uint32 GetData(uint32 type) const override
        {
            return 0;
        }

        ObjectGuid GetGuidData(uint32 type) const
        {
            return ObjectGuid::Empty;
        }

        bool SetBossState(uint32 type, EncounterState state)
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            return true;
        }

        private:
            uint32 uiTeamInInstance;
           
    };
};

class spell_mannoroth_lunar_shot : public SpellScriptLoader
{
    public:
        spell_mannoroth_lunar_shot() : SpellScriptLoader("spell_mannoroth_lunar_shot") { }

        class spell_mannoroth_lunar_shot_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mannoroth_lunar_shot_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                for (std::list<WorldObject*>::iterator itr = unitList.begin(); itr != unitList.end();)
                {
                    if ((*itr)->GetEntry() == 57410)
                        ++itr;
                    else
                        unitList.erase(itr++);
                }
                if (unitList.size() > 3)
                    Trinity::Containers::RandomResizeList(unitList, 3);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mannoroth_lunar_shot_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mannoroth_lunar_shot_SpellScript();
        }
};

class spell_mannoroth_wrath_of_elune : public SpellScriptLoader
{
    public:
        spell_mannoroth_wrath_of_elune() : SpellScriptLoader("spell_mannoroth_wrath_of_elune") { }

        class spell_mannoroth_wrath_of_elune_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mannoroth_wrath_of_elune_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                if (unitList.size() > 4)
                    Trinity::Containers::RandomResizeList(unitList, 4);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mannoroth_wrath_of_elune_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mannoroth_wrath_of_elune_SpellScript();
        }
};

void AddSC_instance_well_of_eternity()
{
    new instance_well_of_eternity();
    new spell_mannoroth_lunar_shot();
    new spell_mannoroth_wrath_of_elune();
}