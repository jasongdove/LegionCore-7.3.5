-- fix link on second spell
UPDATE `smart_scripts` SET `event_type` = 61, `link` = 0 WHERE `entryorguid` = 79243 AND `source_type` = 0 AND `id` = 1;
