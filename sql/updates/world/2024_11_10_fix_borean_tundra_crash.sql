-- change FLEEING_MOTION_TYPE to IDLE_MOTION_TYPE (2 rows)
UPDATE `creature` SET `MovementType` = 0 WHERE `MovementType` = 9;
