-- Greater Plainstrider, Fleeting Plainstrider do not cast Claw
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (3244, 3246) AND `source_type`=0 AND `action_param1`=31289;

-- Adarogg
UPDATE creature_loot_template SET `groupid`=1 WHERE `item` IN (82772, 82879, 82880) AND `entry`=61408;

-- Corrupted Insignia requires the quest
UPDATE creature_loot_template SET `ChanceOrQuestChance` = ABS(`ChanceOrQuestChance`) * -1 WHERE `item`=82605;

-- Dark Shaman Koranthal
UPDATE creature_loot_template SET `groupid`=1 WHERE `item` IN (82877, 82881, 82882, 132551) AND `entry`=61412;

-- Slagmaw
UPDATE creature_loot_template SET `groupid`=1 WHERE `item` IN (82878, 82884, 82885, 132552) AND `entry`=61463;

-- Lava Guard Gordoth
UPDATE creature_loot_template SET `groupid`=1 WHERE `item` IN (82883, 82886, 82888) AND `entry`=61528;
DELETE FROM creature_loot_template WHERE `item` IN (151424, 151425) AND `entry`=61528;
INSERT INTO world.creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount, shared) VALUES (61528, 151424, 0, 1, 1, 1, 1, 0);
INSERT INTO world.creature_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount, shared) VALUES (61528, 151425, 0, 1, 1, 1, 1, 0);

ALTER TABLE `smart_scripts` ADD COLUMN `Difficulties` VARCHAR(100) NOT NULL DEFAULT '' COLLATE 'utf8mb4_unicode_ci' AFTER `link`;

UPDATE `smart_scripts` SET `Difficulties` = '1,2,3,4,5,6' WHERE source_type = 0 AND event_flags & 2 = 2 AND event_flags & 4 = 4 AND event_flags & 8 = 8 AND event_flags & 16 = 16;

UPDATE `smart_scripts` SET `Difficulties` = '1,2,3,4,5' WHERE source_type = 0 AND event_flags & 2 = 2 AND event_flags & 4 = 4 AND event_flags & 8 = 8 AND event_flags & 16 != 16;
UPDATE `smart_scripts` SET `Difficulties` = '1,2,3,4,6' WHERE source_type = 0 AND event_flags & 2 = 2 AND event_flags & 4 = 4 AND event_flags & 8 != 8 AND event_flags & 16 = 16;
UPDATE `smart_scripts` SET `Difficulties` = '1,3,5,6' WHERE source_type = 0 AND event_flags & 2 = 2 AND event_flags & 4 != 4 AND event_flags & 8 = 8 AND event_flags & 16 = 16;
UPDATE `smart_scripts` SET `Difficulties` = '2,4,5,6' WHERE source_type = 0 AND event_flags & 2 != 2 AND event_flags & 4 = 4 AND event_flags & 8 = 8 AND event_flags & 16 = 16;

UPDATE `smart_scripts` SET `Difficulties` = '1,2,3,4' WHERE source_type = 0 AND event_flags & 2 = 2 AND event_flags & 4 = 4 AND event_flags & 8 != 8 AND event_flags & 16 != 16;
UPDATE `smart_scripts` SET `Difficulties` = '1,3,5' WHERE source_type = 0 AND event_flags & 2 = 2 AND event_flags & 4 != 4 AND event_flags & 8 = 8 AND event_flags & 16 != 16;
UPDATE `smart_scripts` SET `Difficulties` = '1,3,6' WHERE source_type = 0 AND event_flags & 2 = 2 AND event_flags & 4 != 4 AND event_flags & 8 != 8 AND event_flags & 16 = 16;
UPDATE `smart_scripts` SET `Difficulties` = '2,4,5' WHERE source_type = 0 AND event_flags & 2 != 2 AND event_flags & 4 = 4 AND event_flags & 8 = 8 AND event_flags & 16 != 16;
UPDATE `smart_scripts` SET `Difficulties` = '2,4,6' WHERE source_type = 0 AND event_flags & 2 != 2 AND event_flags & 4 = 4 AND event_flags & 8 != 8 AND event_flags & 16 = 16;
UPDATE `smart_scripts` SET `Difficulties` = '5,6' WHERE source_type = 0 AND event_flags & 2 != 2 AND event_flags & 4 != 4 AND event_flags & 8 = 8 AND event_flags & 16 = 16;

UPDATE `smart_scripts` SET `Difficulties` = '1,3' WHERE source_type = 0 AND event_flags & 2 = 2 AND event_flags & 4 != 4 AND event_flags & 8 != 8 AND event_flags & 16 != 16;
UPDATE `smart_scripts` SET `Difficulties` = '2,4' WHERE source_type = 0 AND event_flags & 2 != 2 AND event_flags & 4 = 4 AND event_flags & 8 != 8 AND event_flags & 16 != 16;
UPDATE `smart_scripts` SET `Difficulties` = '5' WHERE source_type = 0 AND event_flags & 2 != 2 AND event_flags & 4 != 4 AND event_flags & 8 = 8 AND event_flags & 16 != 16;
UPDATE `smart_scripts` SET `Difficulties` = '6' WHERE source_type = 0 AND event_flags & 2 != 2 AND event_flags & 4 != 4 AND event_flags & 8 != 8 AND event_flags & 16 = 16;

-- Corpse Eater
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry`=47134;
