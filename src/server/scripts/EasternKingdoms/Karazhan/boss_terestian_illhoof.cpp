/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Boss_Terestian_Illhoof
SD%Complete: 95
SDComment: Complete! Needs adjustments to use spell though.
SDCategory: Karazhan
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"
#include "PassiveAI.h"

enum Says
{
    SAY_SLAY = 0,
    SAY_DEATH,
    SAY_AGGRO,
    SAY_SACRIFICE,
    SAY_SUMMON
};

#define SPELL_SUMMON_DEMONCHAINS    30120                   // Summons demonic chains that maintain the ritual of sacrifice.
#define SPELL_DEMON_CHAINS          30206                   // Instant - Visual Effect
#define SPELL_ENRAGE                23537                   // Increases the caster's attack speed by 50% and the Physical damage it deals by 219 to 281 for 10 min.
#define SPELL_SHADOW_BOLT           30055                   // Hurls a bolt of dark magic at an enemy, inflicting Shadow damage.
#define SPELL_SACRIFICE             30115                   // Teleports and adds the debuff
#define SPELL_BERSERK               32965                   // Increases attack speed by 75%. Periodically casts Shadow Bolt Volley.
#define SPELL_SUMMON_FIENDISIMP     30184                   // Summons a Fiendish Imp.
#define SPELL_SUMMON_IMP            30066                   // Summons Kil'rek

#define SPELL_FIENDISH_PORTAL       30171                   // Opens portal and summons Fiendish Portal, 2 sec cast
#define SPELL_FIENDISH_PORTAL_1     30179                   // Opens portal and summons Fiendish Portal, instant cast

#define SPELL_FIREBOLT              30050                   // Blasts a target for 150 Fire damage.
#define SPELL_BROKEN_PACT           30065                   // All damage taken increased by 25%.
#define SPELL_AMPLIFY_FLAMES        30053                   // Increases the Fire damage taken by an enemy by 500 for 25 sec.

#define CREATURE_DEMONCHAINS    17248
#define CREATURE_FIENDISHIMP    17267
#define CREATURE_PORTAL         17265
#define CREATURE_KILREK         17229

class mob_kilrek : public CreatureScript
{
public:
    mob_kilrek() : CreatureScript("mob_kilrek") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_kilrekAI (creature);
    }

    struct mob_kilrekAI : public ScriptedAI
    {
        mob_kilrekAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        ObjectGuid TerestianGUID;

        uint32 AmplifyTimer;

        void Reset() override
        {
            TerestianGUID.Clear();
            AmplifyTimer = 2000;
        }

        void EnterCombat(Unit* /*who*/) override
        {
            if (!instance)
            {
                ERROR_INST_DATA(me);
                return;
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (instance)
            {
                ObjectGuid TerestianGUID = instance->GetGuidData(DATA_TERESTIAN);
                if (TerestianGUID)
                {
                    Unit* Terestian = Unit::GetUnit(*me, TerestianGUID);
                    if (Terestian && Terestian->IsAlive())
                        DoCast(Terestian, SPELL_BROKEN_PACT, true);
                }
            }
            else
                ERROR_INST_DATA(me);
        }

        void UpdateAI(uint32 diff) override
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (AmplifyTimer <= diff)
            {
                me->InterruptNonMeleeSpells(false);

                if (auto victim = me->getVictim())
                    DoCast(victim, SPELL_AMPLIFY_FLAMES, false);

                AmplifyTimer = urand(10000, 20000);
            }
            else
                AmplifyTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class mob_demon_chain : public CreatureScript
{
public:
    mob_demon_chain() : CreatureScript("mob_demon_chain") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_demon_chainAI(creature);
    }

    struct mob_demon_chainAI : public ScriptedAI
    {
        mob_demon_chainAI(Creature* creature) : ScriptedAI(creature) {}

        ObjectGuid SacrificeGUID;

        void Reset() override
        {
            SacrificeGUID.Clear();
        }

        void EnterCombat(Unit* /*who*/) override {}
        void AttackStart(Unit* /*who*/) override {}
        void MoveInLineOfSight(Unit* /*who*/) override {}

        void JustDied(Unit* /*killer*/) override
        {
            if (SacrificeGUID)
            {
                if (Unit* Sacrifice = Unit::GetUnit(*me, SacrificeGUID))
                    Sacrifice->RemoveAurasDueToSpell(SPELL_SACRIFICE);
            }
        }
    };
};

class mob_fiendish_portal : public CreatureScript
{
public:
    mob_fiendish_portal() : CreatureScript("mob_fiendish_portal") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_fiendish_portalAI (creature);
    }

    struct mob_fiendish_portalAI : public PassiveAI
    {
        mob_fiendish_portalAI(Creature* creature) : PassiveAI(creature), summons(me) {}

        SummonList summons;

        void Reset() override
        {
            DespawnAllImp();
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
            DoZoneInCombat(summon);
        }

        void DespawnAllImp()
        {
            summons.DespawnAll();
        }
    };
};

#define SPELL_FIREBOLT  30050   // Blasts a target for 181-209 Fire damage.

class mob_fiendish_imp : public CreatureScript
{
public:
    mob_fiendish_imp() : CreatureScript("mob_fiendish_imp") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_fiendish_impAI (creature);
    }

    struct mob_fiendish_impAI : public ScriptedAI
    {
        mob_fiendish_impAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 FireboltTimer;

        void Reset() override
        {
            FireboltTimer = 2000;

            me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_FIRE, true);
        }

        void EnterCombat(Unit* /*who*/) override {}

        void UpdateAI(uint32 diff) override
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (FireboltTimer <= diff)
            {
                if (auto victim = me->getVictim())
                    DoCast(victim, SPELL_FIREBOLT, false);

                FireboltTimer = 2200;
            }
            else
                FireboltTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class boss_terestian_illhoof : public CreatureScript
{
public:
    boss_terestian_illhoof() : CreatureScript("boss_terestian_illhoof") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_terestianAI (creature);
    }

    struct boss_terestianAI : public ScriptedAI
    {
        boss_terestianAI(Creature* creature) : ScriptedAI(creature)
        {
            for (uint8 i = 0; i < 2; ++i)
                PortalGUID[i].Clear();

            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        ObjectGuid PortalGUID[2];
        uint8 PortalsCount;

        uint32 SacrificeTimer;
        uint32 ShadowboltTimer;
        uint32 SummonTimer;
        uint32 BerserkTimer;

        bool SummonedPortals;
        bool Berserk;

        void Reset() override
        {
            for (uint8 i = 0; i < 2; ++i)
            {
                if (PortalGUID[i])
                {
                    if (Creature* pPortal = Unit::GetCreature(*me, PortalGUID[i]))
                    {
                        CAST_AI(mob_fiendish_portal::mob_fiendish_portalAI, pPortal->AI())->DespawnAllImp();
                        pPortal->DespawnOrUnsummon();
                    }

                    PortalGUID[i].Clear();
                }
            }

            PortalsCount        =     0;
            SacrificeTimer      = 30000;
            ShadowboltTimer     =  5000;
            SummonTimer         = 10000;
            BerserkTimer        = 600000;

            SummonedPortals     = false;
            Berserk             = false;

            if (instance)
                instance->SetData(TYPE_TERESTIAN, NOT_STARTED);

            me->RemoveAurasDueToSpell(SPELL_BROKEN_PACT);

            if (Minion* Kilrek = me->GetFirstMinion())
            {
                if (!Kilrek->IsAlive())
                {
                    Kilrek->UnSummon();
                    DoCast(me, SPELL_SUMMON_IMP, true);
                }
            }
            else
                DoCast(me, SPELL_SUMMON_IMP, true);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(SAY_AGGRO);
        }

        void JustSummoned(Creature* summoned) override
        {
            if (summoned->GetEntry() == CREATURE_PORTAL)
            {
                PortalGUID[PortalsCount] = summoned->GetGUID();
                ++PortalsCount;

                if (summoned->GetUInt32Value(UNIT_FIELD_CREATED_BY_SPELL) == SPELL_FIENDISH_PORTAL_1)
                {
                    Talk(SAY_SUMMON);
                    SummonedPortals = true;
                }
            }
        }

        void KilledUnit(Unit* /*victim*/) override
        {
            Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*killer*/) override
        {
            for (uint8 i = 0; i < 2; ++i)
            {
                if (PortalGUID[i])
                {
                    if (Creature* pPortal = Unit::GetCreature((*me), PortalGUID[i]))
                        pPortal->DespawnOrUnsummon();

                    PortalGUID[i].Clear();
                }
            }

            Talk(SAY_DEATH);

            if (instance)
                instance->SetData(TYPE_TERESTIAN, DONE);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (SacrificeTimer <= diff)
            {
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true);
                if (target && target->IsAlive())
                {
                    DoCast(target, SPELL_SACRIFICE, true);
                    DoCast(target, SPELL_SUMMON_DEMONCHAINS, true);

                    if (Creature* Chains = me->FindNearestCreature(CREATURE_DEMONCHAINS, 5000))
                    {
                        CAST_AI(mob_demon_chain::mob_demon_chainAI, Chains->AI())->SacrificeGUID = target->GetGUID();
                        Chains->CastSpell(Chains, SPELL_DEMON_CHAINS, true);
                        Talk(SAY_SACRIFICE);
                        SacrificeTimer = 30000;
                    }
                }
            }
            else
                SacrificeTimer -= diff;

            if (ShadowboltTimer <= diff)
            {
                if (auto target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0))
                    DoCast(target, SPELL_SHADOW_BOLT, false);

                ShadowboltTimer = 10000;
            }
            else
                ShadowboltTimer -= diff;

            if (SummonTimer <= diff)
            {
                if (!PortalGUID[0])
                    if (auto victim = me->getVictim())
                        DoCast(victim, SPELL_FIENDISH_PORTAL, false);

                if (!PortalGUID[1])
                    if (auto victim = me->getVictim())
                        DoCast(victim, SPELL_FIENDISH_PORTAL_1, false);

                if (PortalGUID[0] && PortalGUID[1])
                {
                    if (Creature* pPortal = Unit::GetCreature(*me, PortalGUID[urand(0, 1)]))
                        if (auto victim = me->getVictim())
                            pPortal->CastSpell(victim, SPELL_SUMMON_FIENDISIMP, false);

                    SummonTimer = 5000;
                }
            }
            else
                SummonTimer -= diff;

            if (!Berserk)
            {
                if (BerserkTimer <= diff)
                {
                    DoCast(SPELL_BERSERK);
                    Berserk = true;
                }
                else
                    BerserkTimer -= diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_terestian_illhoof()
{
    new boss_terestian_illhoof();
    new mob_fiendish_imp();
    new mob_fiendish_portal();
    new mob_kilrek();
    new mob_demon_chain();
}
