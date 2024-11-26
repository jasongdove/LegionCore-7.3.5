#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum eSpells
{
    // kazzak
    SPELL_MARK_OF_KAZZAR        = 187667, // 10
    SPELL_FEL_BREATH            = 187664, // 23
    SPELL_SUPREME_DOOM          = 187466, // 52 + trigger 187471
    SPELL_SUPREME_DOOM_TRIGGER  = 187471,
    SPELL_TWISTED_REFLECTION    = 187702, // 33% 66%
};

// 94015
class boss_kazzak_legion : public CreatureScript
{
public:
    boss_kazzak_legion() : CreatureScript("boss_kazzak_legion") { }

    struct boss_kazzak_legionAI : public ScriptedAI
    {
        boss_kazzak_legionAI(Creature* creature) : ScriptedAI(creature), summons(me) {}

        EventMap events;
        SummonList summons;
        uint32 healthPct;

        void Reset()
        {
            events.Reset();
            summons.DespawnAll();
            healthPct = 66;
        }

        void EnterCombat(Unit* unit)
        {
            events.RescheduleEvent(EVENT_1, 10000);
            events.RescheduleEvent(EVENT_2, 23000);
            events.RescheduleEvent(EVENT_3, 52000);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            DoZoneInCombat(summon, 150.0f);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType dmgType)
        {
            if (me->HealthBelowPct(healthPct))
            {
                healthPct -= 33;
                events.RescheduleEvent(EVENT_4, 10);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
				switch (eventId)
				{
                    case EVENT_1:
                        DoCast(SPELL_MARK_OF_KAZZAR);
                        events.RescheduleEvent(EVENT_1, 10000);
                        break;
                    case EVENT_2:
                        DoCast(SPELL_FEL_BREATH);
                        events.RescheduleEvent(EVENT_2, 23000);
                        break;
                    case EVENT_3:
                        DoCast(SPELL_SUPREME_DOOM);
                        events.RescheduleEvent(EVENT_3, 52000);
                        break;
                    case EVENT_4:
                        DoCast(SPELL_TWISTED_REFLECTION);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_kazzak_legionAI(creature);
    }
};

// 94712
class npc_twisted_reflection : public CreatureScript
{
public:
    npc_twisted_reflection() : CreatureScript("npc_twisted_reflection") { }

    struct npc_twisted_reflectionAI : public ScriptedAI
    {
        npc_twisted_reflectionAI(Creature* creature) : ScriptedAI(creature)
        {
            moveComplete = true;
        }

        bool moveComplete;
        uint32 moveTimer;
		ObjectGuid targetMove;


        void EnterCombat(Unit* unit)
        {
        }

        void IsSummonedBy(Unit* targ)
        {
            if (Creature* owner = me->FindNearestCreature(94015, 100.0f, true))
            {
                owner->AI()->JustSummoned(me); // hack
                me->AddAura(187709, me);
                targetMove = owner->GetGUID();
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->MoveFollow(owner, 0, 0);
                moveTimer = 2000;
                moveComplete = false;
            }
            else
                me->DespawnOrUnsummon();
        }


        void UpdateAI(uint32 diff)
        {
            if (!moveComplete)
            {
                if (moveTimer <= diff)
                {
                    Unit* target = Unit::GetUnit(*me, targetMove);
                    if (!target)
                    {
                        me->DespawnOrUnsummon();
                        return;
                    }

                    if (me->GetDistance(target) < 1.0f)
                    {
                        moveComplete = true;
                        target->CastSpell(target, 187711);
                        me->DespawnOrUnsummon();
                    }
                    moveTimer = 1000;
                }
                else
                    moveTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twisted_reflectionAI(creature);
    }
};

// 187668
class spell_mark_of_kazzak_legion : public SpellScriptLoader
{
    public:
        spell_mark_of_kazzak_legion() : SpellScriptLoader("spell_mark_of_kazzak_legion") { }

        class spell_mark_of_kazzak_legion_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mark_of_kazzak_legion_AuraScript);

            void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                Unit* caster = GetCaster();
                if(!caster)
                    return;

                if (Player* _player = caster->ToPlayer())
                {
                    float damage = int32(eventInfo.GetDamageInfo()->GetDamage());

                    if (damage)
                        _player->CastCustomSpell(_player, 187671, &damage, NULL, NULL, false);
                }
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_mark_of_kazzak_legion_AuraScript::OnProc, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_mark_of_kazzak_legion_AuraScript();
        }
};

// 187471
class spell_mark_of_kazzak_legion_trigger : public SpellScriptLoader
{
    public:
        spell_mark_of_kazzak_legion_trigger() : SpellScriptLoader("spell_mark_of_kazzak_legion_trigger") { }

        class spell_mark_of_kazzak_legion_trigger_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mark_of_kazzak_legion_trigger_AuraScript);

            void OnTick(AuraEffect const* aurEff)
            {
                PreventDefaultAction();

                if (Unit* target = GetTarget())
                {
                    if (target->GetHealthPct() < 50)
                        target->CastSpell(target, 187632);
                }
            }

            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_mark_of_kazzak_legion_trigger_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_mark_of_kazzak_legion_trigger_AuraScript();
        }
};

// 187466
class spell_supreme_doom : public SpellScriptLoader
{
    public:
        spell_supreme_doom() : SpellScriptLoader("spell_supreme_doom") { }

        class spell_supreme_doom_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_supreme_doom_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (!targets.empty())
                {
                    if (targets.size() >= 4)
                        Trinity::Containers::RandomResizeList(targets, targets.size()/ 4);
                    else
                        Trinity::Containers::RandomResizeList(targets, 1);
                }
            }

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        float damage = target->GetHealth() - 1;
                        caster->CastCustomSpell(target, SPELL_SUPREME_DOOM_TRIGGER, &damage, NULL, NULL, false);
                    }
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_supreme_doom_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_supreme_doom_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_supreme_doom_SpellScript();
        }
};

void AddSC_wod_tanaan_jungle()
{
    new boss_kazzak_legion();
    new npc_twisted_reflection();
    new spell_mark_of_kazzak_legion();
    new spell_mark_of_kazzak_legion_trigger();
    new spell_supreme_doom();
}
