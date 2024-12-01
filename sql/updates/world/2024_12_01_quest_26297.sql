-- don't summon shadowy figure on quest accept (with timed action)
DELETE FROM `smart_scripts` WHERE `entryorguid` = 42425 AND `source_type` = 0 AND `event_type` = 19;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 4242500 AND `source_type` = 9;
UPDATE `creature_template` SET `ScriptName` = '' WHERE `entry` = 42425;

-- don't use condition or smart script for areatrigger (now using c++ script)
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 5998;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 5998 AND `source_type` = 2;

DELETE FROM `areatrigger_scripts` WHERE `entry` = 5998;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`)
VALUES (5998, 'areatrigger_westfall_dawning_of_a_new_day');

-- raid boss whisper warning
UPDATE `creature_text` SET `Type` = 42, `Sound` = 37666 WHERE `CreatureID` = 42680 AND BroadcastTextID = 42569;

-- tweaked from existing; no delay on first text, end with cheer sound
DELETE FROM `smart_scripts` WHERE `entryorguid` = 4268000;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `Difficulties`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`)
VALUES
(4268000, 9, 0, 0, '', 0, 0, 100, 0, 0, 0, 0, 0, 1, 8, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - text'),
(4268000, 9, 1, 0, '', 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - text'),
(4268000, 9, 2, 0, '', 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - text'),
(4268000, 9, 3, 0, '', 0, 0, 100, 0, 8000, 8000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - text'),
(4268000, 9, 4, 0, '', 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - text'),
(4268000, 9, 5, 0, '', 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - text'),
(4268000, 9, 6, 0, '', 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - text'),
(4268000, 9, 7, 0, '', 0, 0, 100, 0, 7000, 7000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - text'),
(4268000, 9, 8, 0, '', 0, 0, 100, 0, 0, 0, 0, 0, 5, 25, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - emote'),
(4268000, 9, 9, 0, '', 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - text'),
(4268000, 9, 10, 0, '', 0, 0, 100, 0, 2000, 2000, 0, 0, 33, 42680, 0, 0, 0, 0, 0, 18, 30, 0, 0, 0, 0, 0, 0, 'Shadowy Figure - killcredit'),
(4268000, 9, 11, 0, '', 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 42390, 25, 0, 0, 0, 0, 0, 'data'),
(4268000, 9, 12, 0, '', 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 42386, 25, 0, 0, 0, 0, 0, 'data'),
(4268000, 9, 13, 0, '', 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 42391, 25, 0, 0, 0, 0, 0, 'data'),
(4268000, 9, 14, 0, '', 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 11, 42383, 25, 0, 0, 0, 0, 0, 'data'),
(4268000, 9, 15, 0, '', 0, 0, 100, 0, 0, 0, 0, 0, 4, 13840, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'cheer'),
(4268000, 9, 16, 0, '', 0, 0, 100, 0, 10000, 10000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'despawn');
