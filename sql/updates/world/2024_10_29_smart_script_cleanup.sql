-- only migrate if we need to
SELECT @needsToMigrate := IF(COUNT(*) = 0, 1, 0) FROM `smart_scripts` WHERE `source_type` > 10;

-- LC custom script type SMART_SCRIPT_TYPE_EVENTOBJECT needs to move outside of other TC script types
UPDATE `smart_scripts` SET `source_type` = 13 WHERE `source_type` = 10 AND @needsToMigrate = 1;
