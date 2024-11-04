--
-- hack? not sure how other cores work without this
UPDATE `creature_template_movement` SET `Flight` = 2 WHERE `CreatureId` = 28511;

-- fix action bar
DELETE FROM `creature_template_spell` WHERE `entry` = 28511;
UPDATE `creature_template` SET `spell1` = 51859, `spell2` = 51904, `spell3` = 52006, `spell4` = 0, `spell5` = 52694, `spell6` = 0, `spell7` = 0, `spell8` = 0 WHERE `entry` = 28511;

-- fix recall spell
DELETE FROM `spell_script_names` WHERE `spell_id` = 52694;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (52694, 'spell_q12641_recall_eye_of_acherus');

-- fix siphon spell
DELETE FROM `spell_script_names` WHERE `spell_id` = 51858;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (51858, 'spell_q12641_death_comes_from_on_high');
