--
SET @id := 1978;
UPDATE creature_template SET `AIName` = '', `ScriptName` = '' WHERE `entry` = @id;
DELETE FROM script_waypoint WHERE `entry` = @id;
