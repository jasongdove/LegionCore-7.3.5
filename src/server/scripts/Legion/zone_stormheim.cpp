#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum eSpells
{
    // nithogg
    SPELL_TAIL_LASH         = 212835,
    SPELL_STORM_BREATH      = 212852,
    SPELL_ELECTRICAL_STORM  = 212867,
    SPELL_STATIC_CHARGE     = 212887,
    SPELL_CRACKLING_JOLT    = 212837,

    // SOULTAKERS
    // capitan
    SPELL_TENTACLE_BASH         = 213420,
    SPELL_SHATTER_CREWMEN       = 213532,
    SPELL_CURSED_CREW           = 213522,
    //ydorn
    SPELL_MARAUDING_MISTS       = 213665,
    SPELL_SEADOG_SCUTTLE_COST   = 213580,
    SPELL_SEADOG_SCUTTLE        = 213584,
    SPELL_SEADOG_SCUTTLE_TRIG   = 213588,
    // mevra
    SPELL_TELEPORT              = 215681,
    SPELL_EXPEL_SOUL            = 213625,
    SPELL_SOUL_REND             = 213605,
    SPELL_SOUL_REND_TRIG        = 213638,

    //add
    SPELL_SHATTER_CREWMEN_ADD   = 213533,
};

// 107023
class boss_nithogg : public CreatureScript
{
public:
    boss_nithogg() : CreatureScript("boss_nithogg") {}

    struct boss_nithoggAI : public ScriptedAI
    {
        boss_nithoggAI(Creature* creature) : ScriptedAI(creature), summons(me), healthPct(0)
        {
        }

        EventMap events;
        SummonList summons;
        uint32 healthPct;

        void Reset() override
        {
            events.Reset();
            summons.DespawnAll();
            me->RemoveAllAreaObjects();
            healthPct = 80;
        }

        void EnterCombat(Unit* unit) override
        {
            events.RescheduleEvent(EVENT_1, urand(2000, 4000)); // SPELL_TAIL_LASH  скилл проверяет перед, а не зад. Должен зад
            events.RescheduleEvent(EVENT_2, urand(20000, 21000)); // SPELL_STORM_BREATH
            events.RescheduleEvent(EVENT_3, 30000); // SPELL_ELECTRICAL_STORM
            events.RescheduleEvent(EVENT_4, 41000); // SPELL_STATIC_CHARGE
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
            summon->SetReactState(REACT_PASSIVE);
            if (summon->GetEntry() == 107338)
                summon->GetMotionMaster()->MoveRandom(7.0f);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType dmgType) override
        {
            if (me->HealthBelowPct(healthPct))
            {
                healthPct -= 20;
                events.RescheduleEvent(EVENT_5, 10);
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
                        DoCast(SPELL_TAIL_LASH);
                        events.RescheduleEvent(EVENT_1, 5000);
                        break;
                    case EVENT_2:
                        DoCast(SPELL_STORM_BREATH);
                        events.RescheduleEvent(EVENT_2, urand(20000, 21000));
                        break;
                    case EVENT_3:
                        DoCast(SPELL_ELECTRICAL_STORM);
                        events.RescheduleEvent(EVENT_3, 30000);
                        break;
                    case EVENT_4:
                        {
                            for (int8 i = 0; i < 5; i++)
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40, true))
                                    if (!target->HasAura(SPELL_STATIC_CHARGE))
                                        me->CastSpell(target, SPELL_STATIC_CHARGE);
                            }
                            events.RescheduleEvent(EVENT_4, 41000);
                        }
                        break;
                    case EVENT_5:
                        DoCast(SPELL_CRACKLING_JOLT);
                        std::list<HostileReference*> threatlist = me->getThreatManager().getThreatList();
                        if (!threatlist.empty())
                        {
                            for (std::list<HostileReference*>::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
                            {
                                    if (Player* pl = me->GetPlayer(*me, (*itr)->getUnitGuid()))
                                        Talk(0, pl->GetGUID());
                            }
                        }
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_nithoggAI(creature);
    }
};

// 107353
class npc_static_orb : public CreatureScript
{
public:
    npc_static_orb() : CreatureScript("npc_static_orb") {}

    struct npc_static_orbAI : public ScriptedAI
    {
        npc_static_orbAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            CheckComplete = false;
            checkTimer = 2000;
            moveComplete = true;
            DoCast(212915);
        }

        ObjectGuid targetMove;
        bool moveComplete;
        uint32 moveTimer;
        bool CheckComplete;
        uint32 checkTimer;

        void UpdateAI(uint32 diff) override
        {
            if (!moveComplete)
            {
                if (moveTimer <= diff)
                {
                    Player* target = ObjectAccessor::GetPlayer(*me, targetMove);
                    if (!target)
                    {
                        me->DespawnOrUnsummon();
                        return;
                    }

                    if (me->GetDistance(target) < 3.0f)
                    {
                        moveComplete = true;
                        me->CastStop();
                        DoCast(target, 212948, true);
                        me->DespawnOrUnsummon(1000);
                    }
                    moveTimer = 1000;
                }
                else
                    moveTimer -= diff;
            }

            if (!CheckComplete)
            {
                if (checkTimer <= diff)
                {
                    std::list<Player*> targets;
                    targets.clear();
                    GetPlayerListInGrid(targets, me, 70.0f);
                    if (!targets.empty())
                    {
                        std::list<Player*>::const_iterator itr = targets.begin();
                        std::advance(itr, urand(0, targets.size() - 1));
                        if (*itr)
                            targetMove = (*itr)->GetGUID();

                        if ((*itr) && !(*itr)->HasAura(212943) && !(*itr)->HasAura(212887))
                        {
                            moveTimer = 1000;
                            moveComplete = false;
                            CheckComplete = true;
                            if (!me->HasUnitState(UNIT_STATE_STUNNED))
                            {
                                me->GetMotionMaster()->MoveFollow((*itr), PET_FOLLOW_DIST, (*itr)->GetFollowAngle());
                                me->CastSpell((*itr), 212943);
                            }
                        }
                        else
                        {
                            checkTimer = 500;
                        }
                    }
                }
                else
                    checkTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_static_orbAI(creature);
    }
};

// 212887
class spell_static_charge : public SpellScriptLoader
{
    public:
        spell_static_charge() : SpellScriptLoader("spell_static_charge") {}

        class spell_static_charge_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_static_charge_AuraScript);

            void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (GetCaster() && GetCaster()->ToCreature() && GetTarget())
                {
                    Unit* caster = GetCaster()->ToCreature();
                    if (caster && caster->GetEntry() == 107023)
                    {
                        caster->SummonCreature(107353, GetTarget()->GetPositionX(), GetTarget()->GetPositionY(), GetTarget()->GetPositionZ(), GetTarget()->GetOrientation());
                    }
                }
            }

            void Register() override
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_static_charge_AuraScript::HandleEffectRemove, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_static_charge_AuraScript();
        }
};

enum Bosses
{
    NPC_CAPITAN     = 106981,
    NPC_YDORN       = 106982,
    NPC_MEVRA       = 106984,
};

uint32 const _Bosses[3]
{
    NPC_CAPITAN,
    NPC_YDORN,
    NPC_MEVRA
};

Position const tpPos[6] =
{
    {4930.69f, 489.92f, -53.34f, 2.71f},
    {4904.75f, 471.04f, -53.34f, 2.21f},
    {4863.42f, 449.40f, -53.34f, 1.36f},
    {4840.75f, 476.77f, -53.34f, 0.60f},
    {4820.06f, 510.35f, -53.34f, 0.11f},
    {4878.81f, 524.31f, -48.90f, 4.52f}
};

// 106981 106982 106984
class boss_soultakers : public CreatureScript
{
public:
    boss_soultakers() : CreatureScript("boss_soultakers") {}

    struct boss_soultakersAI : public ScriptedAI
    {
        boss_soultakersAI(Creature* creature) : ScriptedAI(creature), timer_for_energy(0)
        {
        }

        EventMap events;
        uint32 timer_for_energy;

        void Reset() override
        {
            events.Reset();
            me->RemoveAllAreaObjects();
           // me->setPowerType(POWER_ENERGY);
            me->SetPower(POWER_ENERGY, 0);
            timer_for_energy = 1000;
        }

        void EnterCombat(Unit* unit) override
        {
            if (me->GetEntry() == NPC_CAPITAN || me->GetEntry() == NPC_YDORN)
                events.RescheduleEvent(EVENT_1, urand(13000, 16000));
            if (me->GetEntry() == NPC_MEVRA)
                events.RescheduleEvent(EVENT_3, 1000); // 9000

            events.RescheduleEvent(EVENT_10, 1000); // check for energy

            for (int32 n = 0; n < 3; n++)
                if (me->GetEntry() != _Bosses[n])
                    if (Creature* targ = me->FindNearestCreature(_Bosses[n], 100.0f))
                    {
                        if (targ->IsAlive())
                            targ->AI()->AttackStart(unit);
                        else
                            targ->Respawn(false);
                    }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell) override
        {
            if (me->GetEntry() == NPC_CAPITAN)
            {
                if (spell->Id == SPELL_SHATTER_CREWMEN)
                {
                    if (target->GetTypeId() == TYPEID_UNIT)
                    {
                        if (target->ToCreature()->GetEntry() == 107569)
                        {
                            if (target->IsAlive())
                            {
                                target->CastSpell(target, SPELL_SHATTER_CREWMEN_ADD);
                                target->ToCreature()->DespawnOrUnsummon(500);
                            }
                        }
                    }
                }
            }

            if (me->GetEntry() == NPC_MEVRA)
            {
                if (spell->Id == SPELL_SOUL_REND_TRIG)
                {
                    me->CastSpell(target, 213648, true);
                }
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType dmgType) override
        {
            if (attacker != me)
                for (int32 n = 0; n < 3; n++)
                    if (me->GetEntry() != _Bosses[n])
                        if (Creature* targ = me->FindNearestCreature(_Bosses[n], 100.0f, true))
                        {
                            if (damage >= me->GetHealth())
                                attacker->Kill(targ);
                            else
                                targ->DealDamage(targ, damage); // targ->GetHealth()
                        }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (timer_for_energy <= diff)
            {
                uint32 power = me->GetPower(POWER_ENERGY);
                if (power < 100)
                    me->SetPower(POWER_ENERGY, ++power);
                timer_for_energy = urand(1000, 1300);
            }
            else
                timer_for_energy -= diff;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_1:
                        if (me->GetEntry() == NPC_CAPITAN)
                            DoCast(SPELL_TENTACLE_BASH);
                        else
                            DoCast(SPELL_MARAUDING_MISTS);
                        events.RescheduleEvent(EVENT_1, urand(15000, 17000));
                        break;
                    case EVENT_2:
                        DoCast(SPELL_SHATTER_CREWMEN);
                        break;
                    case EVENT_3:
                        {
                            uint32 rand = urand(0, 5);
                            me->CastSpell(tpPos[rand].GetPositionX(), tpPos[rand].GetPositionY(), tpPos[rand].GetPositionZ(), SPELL_TELEPORT);
                            if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 70.0f, true))
                                me->CastSpell(target, SPELL_EXPEL_SOUL);
                            events.RescheduleEvent(EVENT_3, 8500);
                        }
                        break;
                    case EVENT_10:
                        {
                            uint32 power = me->GetPower(POWER_ENERGY);
                            if (power == 100)
                            {
                                switch(me->GetEntry())
                                {
                                    case NPC_CAPITAN:
                                        DoCast(SPELL_CURSED_CREW);
                                        events.RescheduleEvent(EVENT_2, 4000);
                                        break;
                                    case NPC_YDORN:
                                        // repeat this 3 time
                                        me->StopAttack();
                                        me->SetReactState(REACT_PASSIVE);
                                        DoCast(SPELL_SEADOG_SCUTTLE_COST);
                                        if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 70.0f, true))
                                        {
                                            me->CastSpell(target, SPELL_SEADOG_SCUTTLE);
                                            me->CastSpell(target, SPELL_SEADOG_SCUTTLE_TRIG);
                                        }

                                        me->AddDelayedEvent(5000, [this]() -> void
                                        {
                                            if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 70.0f, true))
                                            {
                                                me->CastSpell(target, SPELL_SEADOG_SCUTTLE);
                                                me->CastSpell(target, SPELL_SEADOG_SCUTTLE_TRIG);
                                            }
                                        });

                                        me->AddDelayedEvent(10000, [this]() -> void
                                        {
                                            if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 70.0f, true))
                                            {
                                                me->CastSpell(target, SPELL_SEADOG_SCUTTLE);
                                                me->CastSpell(target, SPELL_SEADOG_SCUTTLE_TRIG);
                                            }
                                        });

                                        me->AddDelayedEvent(15000, [this] () -> void
                                        {
                                            me->SetReactState(REACT_AGGRESSIVE);
                                        });
                                        break;
                                    case NPC_MEVRA:
                                        DoCast(SPELL_SOUL_REND);
                                        break;
                                }
                             //  me->SetPower(POWER_ENERGY, 0);
                            }
                            // else
                                // me->SetPower(POWER_ENERGY, ++power);
                            events.RescheduleEvent(EVENT_10, urand(1000, 1100));
                        }
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_soultakersAI(creature);
    }
};

void AddSC_stormheim()
{
    new boss_nithogg();
    new npc_static_orb();
    new spell_static_charge();
    new boss_soultakers();
}