#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum eSpells
{
    // Ana-Muz
    SPELL_FEL_GEYZER            = 218823, // 22 sec + filter + script to geyzer (197376) + npc 109946 ?  197217
    SPELL_IMPISH_FLAMES         = 218888, // 22 sec after spell above
    SPELL_GASEOUS_BREATH        = 219255, // 31 sec + at + adds
    SPELL_MOTHERS_EMBRACE       = 219045, // 65 sec + script for charm
    SPELL_REMOVE_CHARM          = 227351, // reset or dead

    // Nazak
    SPELL_CORRODING_SPRAY       = 219349, // 23
    SPELL_WEB_WRAP              = 219861, // 42
    SPELL_FOUNDATIONAL_COLLAPSE = 219591, // 57 + cast. + script for crystalls
    SPELL_ABSORB_LEYSTONES      = 219813, // after above. Script for stacks
    SPELL_LEY_INFUSION          = 219836,
};

// 109943
class boss_ana_muz : public CreatureScript
{
public:
    boss_ana_muz() : CreatureScript("boss_ana_muz") {}

    struct boss_ana_muzAI : public ScriptedAI
    {
        boss_ana_muzAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_REMOVE_CLIENT_CONTROL);
        }

        EventMap events;
        SummonList summons;

        void Reset() override
        {
            events.Reset();
            me->RemoveAllAreaObjects();
            summons.DespawnAll();
            DoCast(SPELL_REMOVE_CHARM);
        }

        void EnterCombat(Unit* unit) override
        {
            events.RescheduleEvent(EVENT_1, 4000); // SPELL_FEL_GEYZER
            events.RescheduleEvent(EVENT_3, 7000); // SPELL_GASEOUS_BREATH
            events.RescheduleEvent(EVENT_4, 31000); // SPELL_MOTHERS_EMBRACE
        }

        void JustDied(Unit* who) override
        {
            summons.DespawnAll();
            DoCast(SPELL_REMOVE_CHARM);
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
        }


        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_1:
                        DoCast(SPELL_FEL_GEYZER);
                        events.RescheduleEvent(EVENT_1, 22000);
                        events.RescheduleEvent(EVENT_2, 3000);
                        break;
                    case EVENT_2:
                        DoCast(SPELL_IMPISH_FLAMES);
                        break;
                    case EVENT_3:
                        DoCast(SPELL_GASEOUS_BREATH);
                        events.RescheduleEvent(EVENT_3, 31000);
                        break;
                    case EVENT_4:
                        DoCast(SPELL_MOTHERS_EMBRACE);
                        events.RescheduleEvent(EVENT_4, 65000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_ana_muzAI(creature);
    }
};

// 219045
class spell_mothers_embrace : public SpellScriptLoader
{
    public:
        spell_mothers_embrace() : SpellScriptLoader("spell_mothers_embrace") {}

        class spell_mothers_embrace_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mothers_embrace_AuraScript);

            void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster() || !GetTarget() || GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL)
                    return;
                if (GetCaster()->IsAlive() && GetTarget()->IsAlive())
                    GetCaster()->CastSpell(GetTarget(), 219068, true);
            }

            void Register() override
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_mothers_embrace_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_mothers_embrace_AuraScript();
        }
};

// 110321
class boss_nazak_the_fiend : public CreatureScript
{
public:
    boss_nazak_the_fiend() : CreatureScript("boss_nazak_the_fiend") {}

    struct boss_nazak_the_fiendAI : public ScriptedAI
    {
        boss_nazak_the_fiendAI(Creature* creature) : ScriptedAI(creature), summons(me) {}

        EventMap events;
        SummonList summons;

        void Reset() override
        {
            events.Reset();
            me->RemoveAllAreaObjects();
            summons.DespawnAll();
        }

        void EnterCombat(Unit* unit) override
        {
            events.RescheduleEvent(EVENT_1, 23000);
            events.RescheduleEvent(EVENT_2, 42000);
            events.RescheduleEvent(EVENT_3, 57000);
        }

        void JustDied(Unit* who) override
        {
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
        }

        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_ABSORB_LEYSTONES)
            {
                std::list<Creature*> adds;
                GetCreatureListWithEntryInGrid(adds, me, 110417, 60.0f);
                if (!adds.empty())
                    for (std::list<Creature*>::iterator itr = adds.begin(); itr != adds.end(); ++itr)
                    {
                        if ((*itr)->IsAlive())
                        {
                            (*itr)->DespawnOrUnsummon(1000);
                            DoCast(me, SPELL_LEY_INFUSION, true);
                        }
                    }
            }
        }


        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_1:
                        DoCast(SPELL_CORRODING_SPRAY);
                        events.RescheduleEvent(EVENT_1, 23000);
                        break;
                    case EVENT_2:
                        DoCast(SPELL_WEB_WRAP);
                        events.RescheduleEvent(EVENT_2, 42000);
                        break;
                    case EVENT_3:
                        DoCast(SPELL_FOUNDATIONAL_COLLAPSE);
                        events.RescheduleEvent(EVENT_3, 57000);
                        events.RescheduleEvent(EVENT_4, 2000);
                        break;
                    case EVENT_4:
                        DoCast(SPELL_ABSORB_LEYSTONES);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_nazak_the_fiendAI(creature);
    }
};

// 219591
class spell_foundational_collapse : public SpellScriptLoader
{
    public:
        spell_foundational_collapse() : SpellScriptLoader("spell_foundational_collapse") {}

        class spell_foundational_collapse_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_foundational_collapse_AuraScript)

            void OnPereodic(AuraEffect const* aurEff)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                Position pos = GetCaster()->GetRandomNearPosition(27.0f);
                GetCaster()->CastSpell(pos, GetSpellInfo()->Effects[EFFECT_0]->TriggerSpell, true);
            }

            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_foundational_collapse_AuraScript::OnPereodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_foundational_collapse_AuraScript();
        }
};

void AddSC_suramar()
{
    new boss_ana_muz();
    new spell_mothers_embrace();
    new boss_nazak_the_fiend();
    new spell_foundational_collapse();
}