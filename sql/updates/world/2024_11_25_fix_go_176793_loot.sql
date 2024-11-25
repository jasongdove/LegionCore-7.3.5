--
UPDATE `gameobject_template` SET `Data1` = 176793 WHERE `entry` = 176793;

DELETE FROM `gameobject_loot_template` WHERE `Entry` = 176793;
INSERT INTO `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES (176793, 13872, 0, 100, 1, 1, 0, 1, 1, '');
