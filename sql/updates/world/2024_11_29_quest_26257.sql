-- Creature Overloaded Harvest Golem 42381 SAI
SET @ENTRY := 42381;
UPDATE `creature_template` SET `AIName`='SmartAI', `unit_flags2` = 2049 WHERE `entry`= @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@ENTRY, 0, 0, 0, 1, 0, 100, 0, 3000, 6000, 3500, 6000, 11, 79084, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'When out of combat and timer at the begining between 3000 and 6000 ms (and later repeats every 3500 and 6000 ms) - Self: Cast spell Unbound Energy (79084) on Self // ');

DELETE FROM `conditions` WHERE `SourceEntry`= 79084 AND `SourceTypeOrReferenceId`= 13;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ScriptName`, `Comment`) VALUES
(13, 1, 79084, 0, 0, 31, 0, 3, 42381, 0, 0, '', 'Unbound Energy - Target Overloaded Harvest Golem');

DELETE FROM `spell_script_names` WHERE `ScriptName`= 'spell_westfall_unbound_energy';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(79084, 'spell_westfall_unbound_energy');

-- Creature Overloaded Harvest Golem Vehicle 42601
SET @ENTRY := 42601;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;

UPDATE `creature_template` SET `VehicleId`= 907, `spell1`= 79425, `spell2`= 79430, `ScriptName`= 'npc_westfall_overloaded_harvest_golem', `AIName` = '' WHERE `entry`= @ENTRY;

DELETE FROM `conditions` WHERE `SourceEntry` = 79436 AND `SourceTypeOrReferenceId` IN (13, 17);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ScriptName`, `Comment`) VALUES
(13, 2, 79436, 0, 0, 31, 0, 3, 42381, 0, 0, '', 'Wake Harvest Golem - Target Overloaded Harvest Golem');

DELETE FROM `spell_script_names` WHERE `ScriptName` IN
('spell_westfall_reaping_blows',
'spell_westfall_wake_harvest_golem');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(79425, 'spell_westfall_reaping_blows'),
(79436, 'spell_westfall_wake_harvest_golem');

DELETE FROM `creature_text` WHERE `CreatureID`= 42601;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `Comment`) VALUES
(42601, 0, 0, 'You may only ride the Overloaded Harvest Golem at the Molsen Farm.', 42, 0, 100, 0, 0, 0, 42475, '');

-- Creature Energized Harvest Reaper 42342
SET @ENTRY := 42342;

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = @ENTRY;

UPDATE `creature` SET `spawndist` = 8, `MovementType` = 1 WHERE `id` = @ENTRY;

DELETE FROM `creature_template_spell` WHERE `entry` = @ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`)
VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 5000, 8000, 15000, 20000,  11, 7342, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Energized Harvest Reaper - In Combat - Cast \'Wide Slash\''),
(@ENTRY, 0, 1, 0, 2, 0, 100, 0, 0, 40, 25000, 29000,  11, 80572, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Energized Harvest Reaper - Between 0-40% Health - Cast \'Energize!\'');
