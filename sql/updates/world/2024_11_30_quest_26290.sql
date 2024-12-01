--
DELETE FROM `spell_script_names` WHERE `spell_id` IN (79522, 79523);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(79522, 'spell_westfall_sniper_fire_proc'),
(79523, 'spell_westfall_sniper_fire');

DELETE FROM `creature_text` WHERE `CreatureID` = 7024;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `comment`) VALUES
(7024, 0, 0, 'I\'ve got your back, $n.', 15, 0, 100, 0, 0, 0, 42531, 'Agent Kearnen to Player'),
(7024, 0, 1, 'Headshot!', 15, 0, 100, 0, 0, 0, 42532, 'Agent Kearnen to Player'),
(7024, 0, 2, 'Not a chance.', 15, 0, 100, 0, 0, 0, 42533, 'Agent Kearnen to Player'),
(7024, 0, 3, 'Easy peasy.', 15, 0, 100, 0, 0, 0, 42534, 'Agent Kearnen to Player'),
(7024, 0, 4, 'Got him!', 15, 0, 100, 0, 0, 0, 42535, 'Agent Kearnen to Player');

DELETE FROM `spell_area` WHERE `area` = 40 AND `spell` = 79522;
INSERT INTO `spell_area` (`area`, `spell`, `quest_start`, `quest_start_status`, `quest_end`, `quest_end_status`, `autocast`, `aura_spell`, `racemask`, `gender`) VALUES
(40, 79522, 26290, 10, 0, 11, 1, 0, 0, 2);

-- disable xp for mercenary
UPDATE `creature_template` SET `flags_extra` = 0x40 WHERE `entry` = 42656;
