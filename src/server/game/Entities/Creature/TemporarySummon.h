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

#ifndef TEMPSUMMON_H
#define TEMPSUMMON_H

#include "Creature.h"

enum PetEntry
{
    // Warlock pets
    PET_IMP             = 416,
    PET_FEL_HUNTER      = 691,
    PET_VOID_WALKER     = 1860,
    PET_SUCCUBUS        = 1863,
    PET_DOOMGUARD       = 18540,
    PET_FELGUARD        = 30146,

    // Death Knight pets
    PET_GHOUL           = 26125,
    PET_GARGOYLE        = 27829,
    PET_ABOMINATION     = 106848,

    // Shaman pet
    PET_SPIRIT_WOLF     = 29264
};

enum SummonActionType
{
    SUMMON_ACTION_TYPE_DEFAULT               = 0,
    SUMMON_ACTION_TYPE_ROUND_HOME_POS        = 1,
    SUMMON_ACTION_TYPE_ROUND_SUMMONER        = 2,
};

/// Stores data for temp summons
struct TempSummonData
{
    Position pos;           ///< Position, where should be creature spawned
    uint32 time;            ///< Despawn time, usable only with certain temp summon types
    uint32 entry;           ///< Entry of summoned creature
    float distance;         ///< Distance from caster for non default action
    uint8 count;            ///< Summon count  for non default action
    uint8 actionType;       ///< Summon action type, option for any summon options
    TempSummonType sumType; ///< Summon type, see TempSummonType for available types
};

class TC_GAME_API TempSummon : public Creature
{
    public:
        explicit TempSummon(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject);
        virtual ~TempSummon() {}
        void Update(uint32 time) override;
        virtual void InitStats(uint32 lifetime);
        virtual void InitSummon();
        virtual void UnSummon(uint32 msTime = 0);
        void RemoveFromWorld() override;
        bool InitBaseStat(uint32 creatureId, bool& damageSet);
        void SetTempSummonType(TempSummonType type);
        void SaveToDB(uint32 /*mapid*/, uint64 /*spawnMask*/, uint32 /*phaseMask*/) override {}
        Unit* GetSummoner() const;
        ObjectGuid GetSummonerGUID() const { return m_summonerGUID; }
        void SetSummonerGUID(ObjectGuid guid)  { m_summonerGUID = guid; }
        TempSummonType const& GetSummonType() { return m_type; }
        uint32 GetTimer() { return m_timer; }
		void AddDuration(uint32 time) { m_timer += time; }
        void UpdateAttackPowerAndDamage(bool ranged = false) override;

        PetType getPetType() const { return m_petType; }
        void setPetType(PetType type) { m_petType = type; }

        int32 GetRequiredAreas() const { return m_requiredAreasID; }
        void SetRequiredAreas(int32 requiredAreasID) { m_requiredAreasID = requiredAreasID; }
        void CheckLocation();

        int32 GetBonusDamage() { return m_bonusSpellDamage; }

        const SummonPropertiesEntry* const m_Properties;
        bool    m_loading;
        Unit*   m_owner;
        int32 m_bonusSpellDamage;

    private:
        TempSummonType m_type;
        uint32 m_timer;
        uint32 m_lifetime;
        int32 m_timerCheckLocation;
        ObjectGuid m_summonerGUID;
        bool onUnload;
        PetType m_petType;
        int32 m_requiredAreasID;
};

class Minion : public TempSummon
{
    public:
        Minion(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject);
        void InitStats(uint32 duration) override;
        void RemoveFromWorld() override;

        Unit* GetOwner() { return m_owner; }

        // Warlock pets
        bool IsPetImp() const { return GetEntry() == PET_IMP; }
        bool IsPetFelHunter() const { return GetEntry() == PET_FEL_HUNTER; }
        bool IsPetVoidwalker() const { return GetEntry() == PET_VOID_WALKER; }
        bool IsPetSuccubus() const { return GetEntry() == PET_SUCCUBUS; }
        bool IsPetDoomguard() const { return GetEntry() == PET_DOOMGUARD; }
        bool IsPetFelguard() const { return GetEntry() == PET_FELGUARD; }

        // Death Knight pets
        bool IsPetGhoul() const {return GetEntry() == PET_GHOUL;} // Ghoul may be guardian or pet
        bool IsPetGargoyle() const { return GetEntry() == PET_GARGOYLE; }
        bool IsPetAbomination() const { return GetEntry() == PET_ABOMINATION; } // Sludge Belcher dk talent

        // Shaman pet
        bool IsSpiritWolf() const { return GetEntry() == PET_SPIRIT_WOLF; } // Spirit wolf from feral spirits

        bool IsWarlockPet() const { return IsPetImp() || IsPetFelHunter() || IsPetVoidwalker() || IsPetSuccubus() || IsPetDoomguard() || IsPetFelguard(); }
        bool IsGuardianPet() const;
};

class TC_GAME_API Guardian : public Minion
{
    public:
        Guardian(SummonPropertiesEntry const* properties, Unit* owner, bool isWorldObject);
        void InitStats(uint32 duration) override;
        bool InitStatsForLevel(uint8 level);
        void InitSummon() override;

        bool UpdateStats(Stats stat) override;
        bool UpdateAllStats() override;
        void UpdateResistances(uint32 school) override;
        void UpdateArmor() override;
        void UpdateMaxHealth() override;
        void UpdateMaxPower(Powers power) override;
        void UpdateAttackPowerAndDamage(bool ranged = false) override;
        void UpdateDamagePhysical(WeaponAttackType attType) override;

        void SetBonusDamage(int32 SPD);

    protected:
        float   m_statFromOwner[MAX_STATS]{};
};

class Puppet : public Minion
{
    public:
        Puppet(SummonPropertiesEntry const* properties, Unit* owner);
        void InitStats(uint32 duration) override;
        void InitSummon() override;
        void Update(uint32 time) override;
        void RemoveFromWorld() override;
};

class ForcedUnsummonDelayEvent : public BasicEvent
{
public:
    ForcedUnsummonDelayEvent(TempSummon& owner) : BasicEvent(), m_owner(owner) { }
    bool Execute(uint64 e_time, uint32 p_time) override;

private:
    TempSummon& m_owner;
};
#endif
