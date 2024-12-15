#include "LegacyPhaseMgr.h"
#include "ConditionMgr.h"

bool LegacyPhaseMgr::IsConditionTypeSupported(ConditionTypes const conditionType)
{
    switch (conditionType)
    {
        case CONDITION_AURA:
        case CONDITION_QUESTREWARDED:
        case CONDITION_QUESTTAKEN:
        case CONDITION_QUEST_COMPLETE:
        case CONDITION_QUEST_NONE:
        case CONDITION_TEAM:
        case CONDITION_CLASS:
        case CONDITION_RACE:
        case CONDITION_INSTANCE_INFO:
        case CONDITION_LEVEL:
        case CONDITION_AREA_EXPLORED:
        case CONDITION_SCENE_SEEN:
        case CONDITION_SCENE_TRIGER_EVENT:
        case CONDITION_QUEST_OBJECTIVE_DONE:
        case CONDITION_AREAID:
        case CONDITION_ZONEID:
        case CONDITION_SCENARION_STEP:
        case CONDITION_ACTIVE_EVENT:
        case CONDITION_ON_TRANSPORT:
        case CONDITION_CLASS_HALL_ADVANCEMENT:
            return true;
        default:
            return false;
    }
}
