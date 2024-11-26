#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum eSpells
{
    // drov
    SPELL_COLOSSAL_SLAM         = 175791, // 18
    SPELL_GROUND_PUNCH          = 155294, // 10
    SPELL_CALL_OF_EARTH         = 175827, // 90 + script adds
    SPELL_SUMMON_GORENS         = 175911, // 45 + script adds

    // tarlna
    SPELL_COLOSSAL_SLAM_TARLNA  = 175973, // 16
    SPELL_SUMMON_MANDRAGORA     = 176013, // 46 + script adds
    SPELL_SAVAGE_VINES          = 176001, // 16
    SPELL_SUMMON_MAIN_ADDS      = 175975, // ticks ? + script adds
    SPELL_GENESIS               = 175979, // 49
    SPELL_WAITED_FINISH         = 175123
};

// 81252
class boss_drov : public CreatureScript
{
public:
    boss_drov() : CreatureScript("boss_drov") { }

    struct boss_drovAI : public ScriptedAI
    {
        boss_drovAI(Creature* creature) : ScriptedAI(creature), summons(me) {}

        EventMap events;
        SummonList summons;

        void Reset()
        {
            events.Reset();
            summons.DespawnAll();
        }

        void EnterCombat(Unit* unit)
        {
            events.RescheduleEvent(EVENT_1, 18000);
            events.RescheduleEvent(EVENT_2, 10000);
            events.RescheduleEvent(EVENT_3, 90000);
            events.RescheduleEvent(EVENT_4, 45000);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            if (Player* pl = summon->FindNearestPlayer(70.0f, true))
                summon->AI()->AttackStart(pl);
        }

        void OnApplyOrRemoveAura(uint32 spellId, AuraRemoveMode mode, bool apply)
        {
            if (spellId == SPELL_CALL_OF_EARTH && !apply)
				summons.DespawnEntry(88106);
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
                        DoCast(SPELL_COLOSSAL_SLAM);
                        events.RescheduleEvent(EVENT_1, 18000);
                        break;
                    case EVENT_2:
                        DoCast(SPELL_GROUND_PUNCH);
                        events.RescheduleEvent(EVENT_2, 10000);
                        break;
                    case EVENT_3:
                        DoCast(SPELL_CALL_OF_EARTH);
                        events.RescheduleEvent(EVENT_3, 90000);
                        break;
                    case EVENT_4:
                        DoCast(SPELL_SUMMON_GORENS);
                        events.RescheduleEvent(EVENT_4, 45000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_drovAI(creature);
    }
};

// 81535
class boss_tarlna : public CreatureScript
{
public:
    boss_tarlna() : CreatureScript("boss_tarlna") { }

    struct boss_tarlnaAI : public ScriptedAI
    {
        boss_tarlnaAI(Creature* creature) : ScriptedAI(creature), summons(me) {}

        EventMap events;
        SummonList summons;

        void Reset()
        {
            events.Reset();
            summons.DespawnAll();
        }

        void EnterCombat(Unit* unit)
        {
            events.RescheduleEvent(EVENT_1, 16000);
            events.RescheduleEvent(EVENT_2, 36000);
            events.RescheduleEvent(EVENT_3, 26000); // 16
            events.RescheduleEvent(EVENT_4, 49000);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            DoZoneInCombat(summon, 150.0f);
            if (summon->GetEntry() == 88142)
                summon->CastSpell(summon, SPELL_WAITED_FINISH);
        }

        void OnApplyOrRemoveAura(uint32 spellId, AuraRemoveMode mode, bool apply)
        {
            if (!apply)
                return;

            if (spellId == SPELL_GENESIS)
            {
                for (uint8 i = urand(2,4); i > 0; --i)
                    me->CastSpell(me->GetPositionX() + irand(-16, 16), me->GetPositionY() + irand(-16, 16), me->GetPositionZ(), SPELL_SUMMON_MAIN_ADDS);

                std::list<HostileReference*> threat_list = me->getThreatManager().getThreatList();

                if (!threat_list.empty())
                    for (std::list<HostileReference*>::const_iterator itr = threat_list.begin(); itr!= threat_list.end(); ++itr)
                    {
                        if(Unit* target = Unit::GetUnit(*me, (*itr)->getUnitGuid()))
                            for (uint8 i = urand(2,4); i > 0; --i)
                                me->CastSpell(target->GetPositionX() + irand(-6, 6), target->GetPositionY() + irand(-6, 6), target->GetPositionZ(), SPELL_SUMMON_MAIN_ADDS);
                    }
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
                        DoCast(SPELL_COLOSSAL_SLAM_TARLNA);
                        events.RescheduleEvent(EVENT_1, 16000);
                        break;
                    case EVENT_2:
                        DoCast(SPELL_SUMMON_MANDRAGORA);
                        events.RescheduleEvent(EVENT_2, 46000);
                        break;
                    case EVENT_3:
                        DoCast(SPELL_SAVAGE_VINES);
                        events.RescheduleEvent(EVENT_3, 16000); // 16
                        break;
                    case EVENT_4:
                        DoCast(SPELL_GENESIS);
                        events.RescheduleEvent(EVENT_4, 49000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_tarlnaAI(creature);
    }
};

// 88142
class npc_giant_lasher : public CreatureScript
{
public:
    npc_giant_lasher() : CreatureScript("npc_giant_lasher") { }

    struct npc_giant_lasherAI : public ScriptedAI
    {
        npc_giant_lasherAI(Creature* creature) : ScriptedAI(creature)
        {
            justCasted = false;
        }

        EventMap events;
        bool justCasted;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* unit)
        {
            events.RescheduleEvent(EVENT_1, 4000);
        }

        void IsSummonedBy(Unit* summoner)
        {
            me->AddDelayedEvent(13000, [this] () -> void
            {
                me->RemoveAurasDueToSpell(SPELL_WAITED_FINISH);
                if (Player* pl = me->FindNearestPlayer(70.0f, true))
                    AttackStart(pl);
            });
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (who->GetTypeId() == TYPEID_PLAYER && !justCasted && me->IsWithinDistInMap(who, 2.0f) && me->HasAura(SPELL_WAITED_FINISH))
            {
                justCasted = true;
                who->CastSpell(me, 175986);
                who->Kill(me);
                me->DespawnOrUnsummon(2000);
            }
        }


        void UpdateAI(uint32 diff)
        {
            if (me->HasAura(SPELL_WAITED_FINISH))
                return;

            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_1:
                        DoCast(176000);
                        events.RescheduleEvent(EVENT_1, 4000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_giant_lasherAI(creature);
    }
};

void AddSC_wod_gorgrond()
{
    new boss_drov();
    new boss_tarlna();
    new npc_giant_lasher();
}