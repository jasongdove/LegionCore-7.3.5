#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum eSpells
{
    //levantus
    SPELL_GUST_OF_WIND      = 217211,
    SPELL_RENDING_WHIRL     = 217235,
    SPELL_MASSIVE_SPOUL     = 217249,
    SPELL_ELECTRIFY         = 217344,
    SPELL_TURBULENT_VORTEX  = 217360,
    SPELL_RAMPAGING_TORRENT = 217229,

    //calamir
    SPELL_PHASE_FIRE        = 217563,
    SPELL_PHASE_FROST       = 217831,
    SPELL_PHASE_ARCANE      = 217834,
    SPELL_BURNING_BOMB      = 217874,
    SPELL_HOWLING_GALE      = 217966,
    SPELL_ARCANOPULSE       = 218005,
    SPELL_WRATHFUL_FLAMES   = 217893,
    SPELL_ICY_COMET         = 217919,
    SPELL_ARCANE_DESOLATION = 217986,

    // jim
    SPELL_MORE_MORE_MORE        = 223715,
    // General
    SPELL_NIGHTSHIFTED_BOLTS    = 223623,
    SPELL_RESONANCE             = 223614,
    SPELL_NIGHTSTABLE_ENERGY    = 223689,
};

// 108829
class boss_levantus : public CreatureScript
{
public:
    boss_levantus() : CreatureScript("boss_levantus") {}

    struct boss_levantusAI : public ScriptedAI
    {
        boss_levantusAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_REMOVE_CLIENT_CONTROL);
        }

        EventMap events;
        SummonList summons;
        void Reset() override
        {
            events.Reset();
            summons.DespawnAll();
            me->RemoveAllAreaObjects();
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void EnterCombat(Unit* unit) override
        {
           // DoCast(SPELL_GUST_OF_WIND);
            events.RescheduleEvent(EVENT_1, urand(7000, 8000)); //SPELL_RENDING_WHIRL + 40
            events.RescheduleEvent(EVENT_2, urand(25000, 27000)); //SPELL_MASSIVE_SPOUL + 43
            events.RescheduleEvent(EVENT_3, urand(50000, 51000)); //SPELL_ELECTRIFY + 43  (доделать)
            events.RescheduleEvent(EVENT_4, 11000); // SPELL_TURBULENT_VORTEX
            events.RescheduleEvent(EVENT_5, 1000); //check
            events.RescheduleEvent(EVENT_6, 3000); // not repeat
        }

        void EnterEvadeMove()
        {
            me->SetReactState(REACT_AGGRESSIVE);
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
        }

        void SpellHit(Unit* /*caster */, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_ELECTRIFY)
            {
                std::list<HostileReference*> threatlist = me->getThreatManager().getThreatList();
                if (!threatlist.empty())
                {
                    for (std::list<HostileReference*>::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
                    {
                        if (Player* pl = me->GetPlayer(*me, (*itr)->getUnitGuid()))
                        {
                            if (pl && pl->GetPositionZ() < 0)
                                me->CastSpell(pl, 217352, true);
                        }
                    }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_1:
                        DoCast(SPELL_RENDING_WHIRL);
                        events.RescheduleEvent(EVENT_1, urand(39000, 41000)); //SPELL_RENDING_WHIRL + 40
                        break;
                    case EVENT_2:
                        DoCast(SPELL_MASSIVE_SPOUL);
                        events.RescheduleEvent(EVENT_2, urand(39000, 41000)); //SPELL_MASSIVE_SPOUL + 43
                        break;
                    case EVENT_3:
                        DoCast(SPELL_ELECTRIFY);
                        events.RescheduleEvent(EVENT_3, urand (39000, 41000));
                        break;
                    case EVENT_4:
                        DoCast(SPELL_TURBULENT_VORTEX);
                        events.RescheduleEvent(EVENT_4, 10000);
                        break;
                    case EVENT_5:
                        if (auto target = me->FindNearestPlayer(100.0f))
                            if (!me->IsWithinMeleeRange(target))
                                DoCast(SPELL_RAMPAGING_TORRENT);
                        events.RescheduleEvent(EVENT_5, 1000); //check
                        break;
                    case EVENT_6:
                        for (int8 i = 0; i < 25; i++)
                            me->SummonCreature(109211, me->GetPositionX() + irand (-30, 30), me->GetPositionY() + irand (-30, 30), 0.0f, 0.0f);
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_levantusAI(creature);
    }
};

// 217249
class spell_massive_spoul : public SpellScriptLoader
{
    public:
        spell_massive_spoul() : SpellScriptLoader("spell_massive_spoul") {}

        class spell_massive_spoul_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_massive_spoul_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetCaster() && GetCaster()->ToCreature())
                {
                    GetCaster()->GetMotionMaster()->MoveRotate(20000, ROTATE_DIRECTION_RIGHT);
                    GetCaster()->ToCreature()->AttackStop();
                    GetCaster()->ToCreature()->SetReactState(REACT_PASSIVE);
                }
            }

            void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetCaster() && GetCaster()->ToCreature())
                {
                    GetCaster()->StopMoving();
                    GetCaster()->GetMotionMaster()->Clear(false);
                    GetCaster()->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                    GetCaster()->ToCreature()->AI()->DoZoneInCombat(GetCaster()->ToCreature(), 150.0f);

                }
            }

            void Register() override
            {
                OnEffectApply += AuraEffectApplyFn(spell_massive_spoul_AuraScript::OnApply, EFFECT_0, SPELL_AURA_CREATE_AREATRIGGER, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_massive_spoul_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_CREATE_AREATRIGGER, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_massive_spoul_AuraScript();
        }
};

uint32 const phaseSpell[3]
{
    SPELL_PHASE_FIRE,
    SPELL_PHASE_FROST,
    SPELL_PHASE_ARCANE
};

// 109331
class boss_calamir : public CreatureScript
{
public:
    boss_calamir() : CreatureScript("boss_calamir") {}

    struct boss_calamirAI : public ScriptedAI
    {
        boss_calamirAI(Creature* creature) : ScriptedAI(creature)
        {
            timerphase = 100;
            phase = 0;
        }

        EventMap events;
        uint32 timerphase;
        uint8 phase;

        void Reset() override
        {
            events.Reset();
            me->RemoveAllAreaObjects();
        }

        void EnterCombat(Unit* unit) override
        {
            events.RescheduleEvent(EVENT_1, urand(5000, 6000)); // SPELL_1 13
            events.RescheduleEvent(EVENT_2, urand(15000, 16000)); // SPELL_2 25
        }

        void UpdateAI(uint32 diff) override
        {
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (timerphase <= diff)
            {
                DoCast(me, phaseSpell[phase], true);

                if (phase >= 2)
                    phase = 0;
                else
                    phase++;

                timerphase = 25000;

            } else timerphase -= diff;

            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_1:
                        if (me->HasAura(SPELL_PHASE_FIRE) || me->HasAura(SPELL_PHASE_FROST) || me->HasAura(SPELL_PHASE_ARCANE))
                        {
                            if (me->HasAura(SPELL_PHASE_FIRE))
                                DoCast(SPELL_BURNING_BOMB);
                            else if (me->HasAura(SPELL_PHASE_FROST))
                                DoCast(SPELL_HOWLING_GALE);
                            // else if (me->HasAura(SPELL_PHASE_ARCANE))
                            //    DoCast(SPELL_ARCANOPULSE);

                            events.RescheduleEvent(EVENT_1, 13000);
                        }
                        else
                            events.RescheduleEvent(EVENT_1, 1000);

                        break;
                    case EVENT_2:
                         if (me->HasAura(SPELL_PHASE_FIRE) || me->HasAura(SPELL_PHASE_FROST) || me->HasAura(SPELL_PHASE_ARCANE))
                        {
                            if (me->HasAura(SPELL_PHASE_FIRE))
                                DoCast(SPELL_WRATHFUL_FLAMES);
                            else if (me->HasAura(SPELL_PHASE_FROST))
                                DoCast(SPELL_ICY_COMET);
                            else if (me->HasAura(SPELL_PHASE_ARCANE))
                                DoCast(SPELL_ARCANE_DESOLATION);

                            events.RescheduleEvent(EVENT_2, 25000);
                        }
                        else
                            events.RescheduleEvent(EVENT_2, 1000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_calamirAI(creature);
    }
};

// 112350
class boss_withered_jim : public CreatureScript
{
public:
    boss_withered_jim() : CreatureScript("boss_withered_jim") {}

    struct boss_withered_jimAI : public ScriptedAI
    {
        boss_withered_jimAI(Creature* creature) : ScriptedAI(creature), summons(me), countclons(0)
        {
        }

        EventMap events;
        SummonList summons;
        uint8 countclons;

        void Reset() override
        {
            events.Reset();
            me->RemoveAllAreaObjects();
            summons.DespawnAll();
            countclons=0;
        }

        void EnterCombat(Unit* unit) override
        {
            events.RescheduleEvent(EVENT_1, 18000);
            events.RescheduleEvent(EVENT_2, 24000);
            events.RescheduleEvent(EVENT_3, 22000);
            if (me->GetEntry() == 102075)
                events.RescheduleEvent(EVENT_4, 30000);
            DoCast(223632); // AT
            DoCast(223599);
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
            DoZoneInCombat(me, 150.0f);
            if (summon->GetEntry() == 112350)
                summon->CastSpell(summon, 223599);
            if (summon->GetEntry() == 112342)
                summon->DespawnOrUnsummon(9000);
        }

        void JustDied(Unit* who) override
        {
            summons.DespawnAll();
        }

        void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType dmgType) override
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                return;

            if (attacker->GetPositionZ() >= 60.0f)
                me->Kill(attacker); //cheaters and others
        }


        void UpdateAI(uint32 diff) override
        {
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_1:
                        DoCast(SPELL_NIGHTSHIFTED_BOLTS);
                        events.RescheduleEvent(EVENT_1, urand(25000, 30000));
                        break;
                    case EVENT_2:
                        DoCast(SPELL_RESONANCE);
                        events.RescheduleEvent(EVENT_1, urand(24000, 30000));
                        break;
                    case EVENT_3:
                        DoCast(SPELL_NIGHTSTABLE_ENERGY);
                        events.RescheduleEvent(EVENT_1, urand(29000, 34000));
                        break;
                    case EVENT_4:
                        ++countclons;
                        DoCast(SPELL_MORE_MORE_MORE);
                        if (countclons < 5)
                            events.RescheduleEvent(EVENT_4, 30000);
                        events.RescheduleEvent(EVENT_5, 1000);
                        break;
                    case EVENT_5:
                        if (me->HasAura(SPELL_MORE_MORE_MORE))
                            events.RescheduleEvent(EVENT_5, 1000);
                        else
                        {
                            if (auto add = me->SummonCreature(112350, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation()))
                                add->CastSpell(add, 223723);
                        }
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_withered_jimAI(creature);
    }
};

// 223614
class spell_resonance : public SpellScriptLoader
{
public:
    spell_resonance() : SpellScriptLoader("spell_resonance") {}

    class spell_resonance_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_resonance_AuraScript);

        void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            Unit* target = GetTarget();
            if (!target)
                return;
            target->CastSpell(target, 223616);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_resonance_AuraScript::OnProc, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_resonance_AuraScript();
    }
};

void AddSC_azsuna()
{
    new boss_levantus();
    new spell_massive_spoul();
    new boss_calamir();
    new boss_withered_jim();
    new spell_resonance();
}