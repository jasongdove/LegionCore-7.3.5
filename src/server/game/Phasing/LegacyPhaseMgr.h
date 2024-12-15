#ifndef LEGACY_PHASE_MGR_H
#define LEGACY_PHASE_MGR_H

#include "Define.h"
#include <list>
#include <unordered_map>

// Phasing (visibility)
enum LegacyPhasingFlags
{
    PHASE_FLAG_OVERWRITE_EXISTING           = 0x01,       // don't stack with existing phases, overwrites existing phases
    PHASE_FLAG_NO_MORE_PHASES               = 0x02,       // stop calculating phases after this phase was applied (no more phases will be applied)
    PHASE_FLAG_NEGATE_PHASE                 = 0x04        // negate instead to add the phasemask
};

struct LegacyPhaseDefinition
{
    std::list<uint16> phaseId;
    uint32 zoneId;
    uint32 entry;
    uint32 phasemask;
    uint16 terrainswapmap;
    uint16 wmAreaId;
    uint8 flags;

    bool IsOverwritingExistingPhases() const { return flags & PHASE_FLAG_OVERWRITE_EXISTING; }
    bool IsLastDefinition() const { return flags & PHASE_FLAG_NO_MORE_PHASES; }
    bool IsNegatingPhasemask() const { return flags & PHASE_FLAG_NEGATE_PHASE; }

    bool operator<(const LegacyPhaseDefinition& other) const { return std::tie(zoneId, entry) < std::tie(other.zoneId, other.entry); }
    bool operator==(const LegacyPhaseDefinition& other) const { return zoneId == other.zoneId && entry == other.entry; }
};

typedef std::list<LegacyPhaseDefinition> LegacyPhaseDefinitionContainer;
typedef std::unordered_map<uint32 /*zoneId*/, LegacyPhaseDefinitionContainer> LegacyPhaseDefinitionStore;

class LegacyPhaseMgr
{
public:
    static bool IsConditionTypeSupported(ConditionTypes conditionType);
};

#endif