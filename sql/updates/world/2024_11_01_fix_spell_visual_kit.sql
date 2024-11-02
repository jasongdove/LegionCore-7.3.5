# action_param2 is now kit type
UPDATE `smart_scripts` SET `action_param2` = 0 WHERE `action_type` = 27;

# action_param3 is now duration
UPDATE `smart_scripts` SET `action_param3` = 500 WHERE `action_type` = 27 and `entryorguid` = 8885900;

UPDATE `spell_visual_kit` SET `KitRecID` = `KitType` WHERE `KitRecID` = 0;
UPDATE `spell_visual_kit` SET `KitType` = 0;
