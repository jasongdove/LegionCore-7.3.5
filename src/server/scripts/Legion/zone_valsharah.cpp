#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum eSpells
{
    // humongris
    SPELL_FIRE_BOOM         = 216427,
    SPELL_EARTHSHAKE_STOMP  = 216430,
    SPELL_ICE_FIST          = 216432,
    SPELL_YOU_GO_BANG       = 216817,
    SPELL_MAKE_THE_SNOW     = 216467,

    // shartos
    SPELL_TAIL_LASH_SHARTOS     = 215806,
    SPELL_CRY_OF_THE_TORMENTED  = 216044,
    SPELL_DREAD_FLAME           = 216043,
    SPELL_NIGHTMARE_BREATH      = 215821,
    SPELL_BURNING_EARTH         = 215856,
};

// 108879
class boss_humongris : public CreatureScript
{
public:
    boss_humongris() : CreatureScript("boss_humongris") {}

    struct boss_humongrisAI : public ScriptedAI
    {
        boss_humongrisAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void Reset() override
        {
            events.Reset();
            me->RemoveAllAreaObjects();
        }

        void EnterCombat(Unit* unit) override
        {
            events.RescheduleEvent(EVENT_1, urand(15000, 16000)); // SPELL_FIRE_BOOM
            events.RescheduleEvent(EVENT_2, urand(25000, 26000)); // SPELL_EARTHSHAKE_STOMP
            events.RescheduleEvent(EVENT_3, urand(28000, 30000)); // SPELL_ICE_FIST
            events.RescheduleEvent(EVENT_4, urand(33000, 35000)); // SPELL_YOU_GO_BANG 25  rand
            events.RescheduleEvent(EVENT_5, urand(37000, 38000)); // SPELL_MAKE_THE_SNOW 34

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
                        DoCast(SPELL_FIRE_BOOM);
                        SayHelper(0);
                        events.RescheduleEvent(EVENT_1, 15000);
                        break;
                    case EVENT_2:
                        DoCast(SPELL_EARTHSHAKE_STOMP);
                        events.RescheduleEvent(EVENT_2, 25000);
                        break;
                    case EVENT_3:
                        DoCast(SPELL_ICE_FIST);
                        SayHelper(2);
                        events.RescheduleEvent(EVENT_3, urand(28000, 30000));
                        break;
                    case EVENT_4:
                        if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                            DoCast(target, SPELL_YOU_GO_BANG, false);
                        events.RescheduleEvent(EVENT_4, urand(24000, 26000));
                        break;
                    case EVENT_5:
                        DoCast(SPELL_MAKE_THE_SNOW);
                        SayHelper(1);
                        events.RescheduleEvent(EVENT_5, urand(34000, 36000));
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void SayHelper(uint32 text)
        {
            Talk(text);
            if (Creature* padosen = me->FindNearestCreature(108880, 50.0f, true))
                padosen->AI()->Talk(text);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_humongrisAI(creature);
    }
};

// 108678
class boss_shartos : public CreatureScript
{
public:
    boss_shartos() : CreatureScript("boss_shartos") {}

    struct boss_shartosAI : public ScriptedAI
    {
        boss_shartosAI(Creature* creature) : ScriptedAI(creature){}

        EventMap events;

        void Reset() override
        {
            events.Reset();
            me->RemoveAllAreaObjects();
        }

        void EnterCombat(Unit* unit) override
        {
            events.RescheduleEvent(EVENT_1, 5000);
            events.RescheduleEvent(EVENT_2, 45000);
            events.RescheduleEvent(EVENT_3, 20000);
            events.RescheduleEvent(EVENT_5, 24000);
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
                        DoCast(SPELL_TAIL_LASH_SHARTOS);
                        events.RescheduleEvent(EVENT_1, urand(7000, 10000));
                        break;
                    case EVENT_2:
                        DoCast(SPELL_CRY_OF_THE_TORMENTED);
                        events.RescheduleEvent(EVENT_2, 50000);
                        break;
                    case EVENT_3:
                        DoCast(SPELL_DREAD_FLAME);
                        events.RescheduleEvent(EVENT_3, 20000);
                        events.RescheduleEvent(EVENT_4, 10000);
                        break;
                    case EVENT_4:
                        DoCast(SPELL_NIGHTMARE_BREATH);
                        break;
                    case EVENT_5:
                        DoCast(SPELL_BURNING_EARTH);  // �� �������...
                        events.RescheduleEvent(EVENT_5, 25000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_shartosAI(creature);
    }
};

void AddSC_valsharah()
{
    new boss_humongris();
    new boss_shartos();
}
