-- convert CONDITION_SOURCE_TYPE_PHASE_DEFINITION_DEPRECATED to CONDITION_SOURCE_TYPE_PHASE

-- CONDITION_SOURCE_TYPE_PHASE_DEFINITION_DEPRECATED
-- SourceGroup: ZoneID
-- SourceEntry: PhaseID

-- CONDITION_SOURCE_TYPE_PHASE
-- SourceGroup: PhaseID
-- SourceEntry: ZoneID

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 26;

INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, ConditionTypeOrReference, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`)
SELECT 26, `SourceEntry`, `SourceGroup`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`
FROM `conditions` WHERE `SourceTypeOrReferenceId` = 44;

DELETE FROM `phase_area` WHERE `Comment` = 'LEGACY_LC';

INSERT INTO `phase_area` (`AreaId`, `PhaseId`, `Comment`)
SELECT DISTINCT `SourceEntry`, `SourceGroup`, 'LEGACY_LC'
FROM `conditions` WHERE `SourceTypeOrReferenceId` = 26;
