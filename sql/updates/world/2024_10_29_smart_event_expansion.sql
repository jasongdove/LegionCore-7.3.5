-- only migrate if we need to (no smart_scripts with event_type >= 88)
SELECT @needsToMigrate := IF(COUNT(*) = 0, 1, 0) FROM `smart_scripts` WHERE `event_type` >= 88;

UPDATE `smart_scripts` SET `event_type` = 88 WHERE `event_type` = 74 AND @needsToMigrate = 1;
UPDATE `smart_scripts` SET `event_type` = 89 WHERE `event_type` = 75 AND @needsToMigrate = 1;
UPDATE `smart_scripts` SET `event_type` = 90 WHERE `event_type` = 76 AND @needsToMigrate = 1;
UPDATE `smart_scripts` SET `event_type` = 91 WHERE `event_type` = 77 AND @needsToMigrate = 1;
UPDATE `smart_scripts` SET `event_type` = 92 WHERE `event_type` = 78 AND @needsToMigrate = 1;
UPDATE `smart_scripts` SET `event_type` = 75 WHERE `event_type` = 79 AND @needsToMigrate = 1;
