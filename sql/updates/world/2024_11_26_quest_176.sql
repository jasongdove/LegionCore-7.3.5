--
UPDATE `creature_template` SET `ScriptName` = 'npc_hogger' WHERE `entry` = 448;
UPDATE `creature_template` SET `ScriptName` = 'npc_hogger_minion' WHERE `entry` = 46932;

-- these are temp summons
DELETE FROM `creature` WHERE `guid` = 102532 AND `id` = 46942;
DELETE FROM `creature` WHERE `guid` = 102533 AND `id` = 46941;
DELETE FROM `creature` WHERE `guid` = 102531 AND `id` = 46940;
DELETE FROM `creature` WHERE `guid` IN (102534, 102535) AND `id` = 46943;

DELETE FROM `creature_text` WHERE `Entry` = 65153;
INSERT INTO `creature_text` (`Entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `comment`)
VALUES
(65153, 0, 0, 'Hold your blade, adventurer!', 14, 0, 0, 0, 0, 0, 47004, 'General hold blade'),
(65153, 1, 0, 'This beast leads the Riverpaw gnoll gang and may be the key to ending gnoll aggression in Elwynn.', 12, 0, 0, 0, 0, 0, 47007, 'General speech'),
(65153, 2, 0, 'We''re taking him into custody in the name of King Varian Wrynn.', 12, 0, 0, 0, 0, 0, 47008, 'General take custody'),
(65153, 3, 0, 'Take us to the Stockades, Andromath.', 12, 0, 0, 0, 0, 0, 47009, 'General take custody');

DELETE FROM `creature_text` WHERE `Entry` = 448;
INSERT INTO `creature_text` (`Entry`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `comment`)
VALUES
(448, 0, 0, 'More bones to gnaw on...', 12, 0, 100, 0, 0, 0, 1871, 'Hogger Agro Say 1'),
(448, 1, 0, 'Grrrr... fresh meat!', 12, 0, 100, 0, 0, 0, 1870, 'Hogger Agro Say 2'),
(448, 2, 0, 'Yipe!  Help Hogger!', 14, 0, 0, 0, 0, 0, 46936, 'Hogger help'),
(448, 3, 0, 'No hurt Hogger!', 14, 0, 0, 0, 0, 0, 47000, 'Hogger nohurt'),
(448, 4, 0, 'Hogger is stunned!', 14, 0, 0, 0, 0, 0, 46940, 'Hogger stunned'),
(448, 5, 0, 'Hogger is eating!  Stop him!', 14, 0, 0, 0, 0, 0, 46939, 'Hogger eating'),
(448, 6, 0, 'Grrr...', 12, 0, 0, 0, 0, 0, 46937, 'Hogger grrr'),
(448, 7, 0, 'Nooooo...', 12, 0, 0, 0, 0, 0, 46938, 'Hogger no');
