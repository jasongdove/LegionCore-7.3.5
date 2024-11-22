--
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 55342;

DELETE FROM `spell_script_names` WHERE `spell_id` = 55342;
INSERT INTO `spell_script_names` (spell_id, ScriptName) VALUES (55342, 'spell_mage_mirror_image_summon');
