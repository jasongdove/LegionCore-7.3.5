/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef TRINITY_COMBATAI_H
#define TRINITY_COMBATAI_H

#include "CreatureAI.h"
#include "CreatureAIImpl.h"
#include "ConditionMgr.h"
#include "CreatureTextMgr.h"

class Creature;

typedef std::map<ObjectGuid, EventMap> PlayerEventMap;

class AggressorAI : public CreatureAI
{
    public:
        explicit AggressorAI(Creature* c) : CreatureAI(c), m_checkTimer(0), CreatureTexts(nullptr), CreatureCombatTexts(nullptr) {}

        void Reset() override;
        void InitializeAI() override;
        void UpdateAI(uint32) override;
        void EnterCombat(Unit* who) override;
        void JustDied(Unit* killer) override;
        static int Permissible(const Creature*);
        void DoActionAI(uint32 diff, CreatureActionType type);
        void MoveInLineOfSight(Unit*) override;

        void AddClientVisibility(ObjectGuid guid) override;
        void RemoveClientVisibility(ObjectGuid guid) override;

        uint32 m_checkTimer;
    protected:
        EventMap spellCasts;
        EventMap events;
        EventMap textCombatEvents;
        PlayerEventMap textEvents;
        CreatureTextGroup const* CreatureTexts;
        CreatureTextGroup const* CreatureCombatTexts;
};

class AnyPetAI : public CreatureAI
{
    public:
        explicit AnyPetAI(Creature* c) : CreatureAI(c), m_updateAlliesTimer(0) {}

        void InitializeAI() override;
        void UpdateAI(uint32) override;
        static int Permissible(const Creature*);
        void UpdateAllies();
        GuidSet m_AllySet;
        uint32 m_updateAlliesTimer;
        void MovementInform(uint32 moveType, uint32 data) override;
};

typedef std::vector<uint32> SpellVct;

class CombatAI : public CreatureAI
{
    public:
        explicit CombatAI(Creature* c) : CreatureAI(c) {}

        void InitializeAI() override;
        void Reset() override;
        void EnterCombat(Unit* who) override;
        void JustDied(Unit* killer) override;
        void UpdateAI(uint32 diff) override;
        static int Permissible(const Creature*);
    protected:
        EventMap events;
        SpellVct spells;
};

class CasterAI : public CombatAI
{
    public:
        explicit CasterAI(Creature* c) : CombatAI(c) { m_attackDist = MELEE_RANGE; }
        void InitializeAI() override;
        void AttackStart(Unit* victim) override { AttackStartCaster(victim, m_attackDist); }
        void UpdateAI(uint32 diff) override;
        void EnterCombat(Unit* /*who*/) override;
    private:
        float m_attackDist;
};

struct ArcherAI : public CreatureAI
{
    public:
        explicit ArcherAI(Creature* c);
        void AttackStart(Unit* who) override;
        void UpdateAI(uint32 diff) override;

        static int Permissible(const Creature*);
    protected:
        float m_minRange;
};

struct TurretAI : public CreatureAI
{
    public:
        explicit TurretAI(Creature* c);
        bool CanAIAttack(const Unit* who) const override;
        void AttackStart(Unit* who) override;
        void UpdateAI(uint32 diff) override;

        static int Permissible(const Creature*);
    protected:
        float m_minRange;
};

#define VEHICLE_CONDITION_CHECK_TIME 1000
#define VEHICLE_DISMISS_TIME 5000
struct VehicleAI : public CreatureAI
{
    public:
        explicit VehicleAI(Creature* c);

        void UpdateAI(uint32 diff) override;
        static int Permissible(const Creature*);
        void Reset() override;
        void MoveInLineOfSight(Unit*) override {}
        void AttackStart(Unit*) override {}
        void OnCharmed(bool apply) override;

    private:
        Vehicle* m_vehicle;
        bool m_IsVehicleInUse;
        void LoadConditions();
        void CheckConditions(uint32 diff);
        ConditionList conditions;
        uint32 m_ConditionsTimer;
        bool m_DoDismiss;
        uint32 m_DismissTimer;
};

class BattlePetAI : public CreatureAI
{
    public:
        explicit BattlePetAI(Creature* c) : CreatureAI(c) {}

        void InitializeAI() override;
        void UpdateAI(uint32) override;
        static int Permissible(const Creature*);
        void MovementInform(uint32 moveType, uint32 data) override;
};

#endif
