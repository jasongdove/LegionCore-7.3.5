--
DELETE FROM `spell_script_names` WHERE `spell_id` IN (49998, 49576, 195182, 50842, 43265);

INSERT INTO `spell_script_names` (spell_id, ScriptName)
VALUES
(49998, 'spell_dk_death_strike'),
(49576, 'spell_dk_death_grip_initial'),
(195182, 'spell_dk_marrowrend'),
(50842, 'spell_dk_blood_boil'),
(43265, 'spell_dk_death_and_decay');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 49998;