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

#ifndef PET_H
#define PET_H

#include "PetDefines.h"
#include "TemporarySummon.h"

enum PetNameInvalidReason
{
    // custom, not send
    PET_NAME_SUCCESS                                        = 0,

    PET_NAME_INVALID                                        = 1,
    PET_NAME_NO_NAME                                        = 2,
    PET_NAME_TOO_SHORT                                      = 3,
    PET_NAME_TOO_LONG                                       = 4,
    PET_NAME_MIXED_LANGUAGES                                = 6,
    PET_NAME_PROFANE                                        = 7,
    PET_NAME_RESERVED                                       = 8,
    PET_NAME_THREE_CONSECUTIVE                              = 11,
    PET_NAME_INVALID_SPACE                                  = 12,
    PET_NAME_CONSECUTIVE_SPACES                             = 13,
    PET_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS          = 14,
    PET_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END   = 15,
    PET_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME              = 16
};

#define ACTIVE_SPELLS_MAX           4

struct PetSpell
{
    ActiveStates active;
    PetSpellState state;
    PetSpellType type;
};

enum PetStableinfo
{
    PET_STABLE_ACTIVE = 1,
    PET_STABLE_INACTIVE = 2
};

typedef std::unordered_map<uint32, PetSpell> PetSpellMap;
typedef std::vector<uint32> AutoSpellList;

class Player;

class TC_GAME_API Pet : public Guardian
{
    public:
        explicit Pet(Player* owner, PetType type = MAX_PET_TYPE);
        virtual ~Pet();

        void AddToWorld() override;
        void RemoveFromWorld() override;

        bool isControlled() const;
        bool isTemporarySummoned() const;

        bool IsPermanentPetFor(Player* owner);              // pet have tab in character windows and set UNIT_FIELD_PET_NUMBER

        bool Create(ObjectGuid::LowType const& guidlow, Map* map, uint32 phaseMask, uint32 Entry, uint32 pet_number);
        bool CreateBaseAtCreature(Creature* creature);
        bool CreateBaseAtCreatureInfo(CreatureTemplate const* cinfo, Unit* owner);
        bool CreateBaseAtTamed(CreatureTemplate const* cinfo, Map* map, uint32 phaseMask);
        static std::pair<PetStable::PetInfo const*, PetSaveMode> GetLoadPetInfo(PetStable const& stable, uint32 petEntry, uint32 petNumber, Optional<PetSaveMode> slot);
        bool LoadPetFromDB(Player* owner, uint32 petEntry, uint32 petnumber, bool current, Optional<PetSaveMode> forcedSlot = {});
        bool isBeingLoaded() const override { return m_loading;}
        void SavePetToDB(PetSaveMode mode);
        void FillPetInfo(PetStable::PetInfo* petInfo) const;
        void Remove(PetSaveMode mode, bool returnreagent = false);
        static void DeleteFromDB(uint32 petNumber);

        void setDeathState(DeathState s) override;                   // overwrite virtual Creature::setDeathState and Unit::setDeathState
        void Update(uint32 diff) override;                           // overwrite virtual Creature::Update and Unit::Update

        uint8 GetPetAutoSpellSize() const override { return uint8(m_autospells.size()); }
        uint32 GetPetAutoSpellOnPos(uint8 pos) const override
        {
            if (pos >= m_autospells.size())
                return 0;
            else
                return m_autospells[pos];
        }

        void GivePetLevel(uint8 level);
        void SynchronizeLevelWithOwner();
        bool HaveInDiet(ItemTemplate const* item) const;
        uint32 GetCurrentFoodBenefitLevel(uint32 itemlevel);
        void SetDuration(int32 dur) { m_duration = dur; }
        int32 GetDuration() { return m_duration; }

        void ToggleAutocast(SpellInfo const* spellInfo, bool apply);

        bool HasSpell(uint32 spell) override;

        void LearnPetPassives();
        void CastPetAuras(bool current, uint32 spellId = 0);
        bool IsPetAura(Aura const* aura);

        void ProhibitSpellSchool(SpellSchoolMask idSchoolMask, uint32 unTimeMs) override;

        void _LoadSpellCooldowns();
        void _SaveSpellCooldowns(CharacterDatabaseTransaction& trans);
        void _LoadAuras(PreparedQueryResult auraResult, PreparedQueryResult effectResult, uint32 timediff);
        void _SaveAuras(CharacterDatabaseTransaction& trans);
        void _LoadSpells(PreparedQueryResult result);
        void _SaveSpells(CharacterDatabaseTransaction& trans);

        bool addSpell(uint32 spellId, ActiveStates active = ACT_DECIDE, PetSpellState state = PETSPELL_NEW, PetSpellType type = PETSPELL_NORMAL);
        bool learnSpell(uint32 spell_id);
        void InitLevelupSpellsForLevel();
        bool unlearnSpell(uint32 spell_id);
        bool removeSpell(uint32 spell_id);
        void CleanupActionBar();
        std::string GenerateActionBarData() const;

        void InitPetCreateSpells();

        DeclinedName const* GetDeclinedNames() const { return m_declinedname.get(); }

        AutoSpellList   m_autospells;
        AutoSpellList   m_castspells;
        PetSpellMap     m_spells;
        bool    m_removed;                                  // prevent overwrite pet state in DB at next Pet::Update if pet already removed(saved)

        Unit* GetOwner() { return m_owner; }

        uint16 GetSpecialization() const { return m_petSpecialization; }
        void SetSpecialization(uint16 spec);
        void LearnSpecializationSpell();
        void UnlearnSpecializationSpell();
        void CheckSpecialization();

        uint32 GetGroupUpdateFlag() const { return m_groupUpdateMask; }
        void SetGroupUpdateFlag(uint32 flag);
        void ResetGroupUpdateFlag();

    protected:
        int32   m_duration;                                 // time until unsummon (used mostly for summoned guardians and not used for controlled pets)
        uint16 m_petSpecialization;
        uint32 m_groupUpdateMask;

        std::unique_ptr<DeclinedName> m_declinedname;

    private:
        void SaveToDB(uint32, uint64, uint32) override
        // override of Creature::SaveToDB     - must not be called
        {
            ASSERT(false);
        }
        void DeleteFromDB() override
        // override of Creature::DeleteFromDB - must not be called
        {
            ASSERT(false);
        }
};
#endif
