--
UPDATE `creature_template_spell` SET `Difficulties` = '';

-- DIFFICULTY_NORMAL, DIFFICULTY_10_N
UPDATE `creature_template_spell` SET `Difficulties` = '1,3' WHERE `difficultyMask` = 1;

-- DIFFICULTY_HEROIC
UPDATE `creature_template_spell` SET `Difficulties` = '2' WHERE `difficultyMask` = 2;

UPDATE `creature_template_spell` SET `Difficulties` = '1,2,3' WHERE `difficultyMask` = 3;
