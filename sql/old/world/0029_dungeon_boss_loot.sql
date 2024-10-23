-- Razorfen Kraul
-- Hunter Bonetusk <Pack Leader>
DELETE FROM `creature_loot_template` WHERE `entry`=75001 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (75001, 6681, 0, 1, 0, 1, 1, 0),
    (75001, 6689, 0, 1, 0, 1, 1, 0),
    (75001, 151442, 0, 1, 0, 1, 1, 0);

-- Razorfen Kraul
-- Roogug <Geomagus Overseer>
DELETE FROM `creature_loot_template` WHERE `entry`=74948 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74948, 6690, 0, 1, 0, 1, 1, 0),
    (74948, 6691, 0, 1, 0, 1, 1, 0),
    (74948, 132565, 0, 1, 0, 1, 1, 0),
    (74948, 151443, 0, 1, 0, 1, 1, 0);

-- Razorfen Kraul
-- Warlord Ramtusk
DELETE FROM `creature_loot_template` WHERE `entry`=74462 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74462, 6685, 0, 1, 0, 1, 1, 0),
    (74462, 6686, 0, 1, 0, 1, 1, 0),
    (74462, 6687, 0, 1, 0, 1, 1, 0),
    (74462, 6688, 0, 1, 0, 1, 1, 0),
    (74462, 151445, 0, 1, 0, 1, 1, 0);

-- Dire Maul
-- Zevrim Thornhoof
DELETE FROM `creature_loot_template` WHERE `entry`=11490 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (11490, 18306, 0, 1, 0, 1, 1, 0),
    (11490, 18308, 0, 1, 0, 1, 1, 0),
    (11490, 18313, 0, 1, 0, 1, 1, 0),
    (11490, 18315, 0, 1, 0, 1, 1, 0),
    (11490, 18319, 0, 1, 0, 1, 1, 0),
    (11490, 18323, 0, 1, 0, 1, 1, 0);

-- Dire Maul
-- Illyanna Ravenoak
DELETE FROM `creature_loot_template` WHERE `entry`=11488 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (11488, 18347, 0, 1, 0, 1, 1, 0),
    (11488, 18349, 0, 1, 0, 1, 1, 0),
    (11488, 18377, 0, 1, 0, 1, 1, 0),
    (11488, 18383, 0, 1, 0, 1, 1, 0),
    (11488, 18386, 0, 1, 0, 1, 1, 0);

-- Dire Maul
-- Stomper Kreeg <The Drunk>
DELETE FROM `creature_loot_template` WHERE `entry`=14322 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (14322, 18425, 0, 1, 0, 1, 1, 0),
    (14322, 18464, 0, 1, 0, 1, 1, 0);

-- Dire Maul
-- Guard Fengus
DELETE FROM `creature_loot_template` WHERE `entry`=14321 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1 AND `item`=7909;

-- Dire Maul
-- Captain Kromcrush
DELETE FROM `creature_loot_template` WHERE `entry`=14325 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (14325, 18502, 0, 1, 0, 1, 1, 0),
    (14325, 18503, 0, 1, 0, 1, 1, 0),
    (14325, 18505, 0, 1, 0, 1, 1, 0),
    (14325, 18507, 0, 1, 0, 1, 1, 0),
    (14325, 18458, 0, 1, 0, 1, 1, 0);

-- Dire Maul
-- Cho'Rush the Observer
DELETE FROM `creature_loot_template` WHERE `entry`=14324 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (14324, 18459, 0, 1, 0, 1, 1, 0),
    (14324, 18483, 0, 1, 0, 1, 1, 0),
    (14324, 18484, 0, 1, 0, 1, 1, 0),
    (14324, 18485, 0, 1, 0, 1, 1, 0),
    (14324, 18490, 0, 1, 0, 1, 1, 0),
    (14324, 18527, 0, 1, 0, 1, 1, 0);

-- Razorfen Downs
-- Aarux <The Plagued Nightmare>
DELETE FROM `creature_loot_template` WHERE `entry`=74412 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74412, 10775, 0, 1, 0, 1, 1, 0),
    (74412, 10776, 0, 1, 0, 1, 1, 0),
    (74412, 10777, 0, 1, 0, 1, 1, 0);

-- Razorfen Downs
-- Mordresh Fire Eye
DELETE FROM `creature_loot_template` WHERE `entry`=74347 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74347, 10771, 0, 1, 0, 1, 1, 0),
    (74347, 10769, 0, 1, 0, 1, 1, 0),
    (74347, 10770, 0, 1, 0, 1, 1, 0);

-- Razorfen Downs
-- Mushlump
DELETE FROM `creature_loot_template` WHERE `entry`=74435 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74435, 151453, 0, 1, 0, 1, 1, 0),
    (74435, 10772, 0, 1, 0, 1, 1, 0),
    (74435, 10774, 0, 1, 0, 1, 1, 0);

-- Razorfen Downs
-- Death Speaker Blackthorn
DELETE FROM `creature_loot_template` WHERE `entry`=74875 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74875, 10766, 0, 1, 0, 1, 1, 0),
    (74875, 10767, 0, 1, 0, 1, 1, 0),
    (74875, 10760, 0, 1, 0, 1, 1, 0),
    (74875, 10768, 0, 1, 0, 1, 1, 0),
    (74875, 10758, 0, 1, 0, 1, 1, 0),
    (74875, 151454, 0, 1, 0, 1, 1, 0);

-- Uldaman
-- Revelosh
DELETE FROM `creature_loot_template` WHERE `entry`=6910 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (6910, 9390, 0, 1, 0, 1, 1, 0),
    (6910, 9388, 0, 1, 0, 1, 1, 0),
    (6910, 9389, 0, 1, 0, 1, 1, 0),
    (6910, 9387, 0, 1, 0, 1, 1, 0),
    (6910, 132736, 0, 1, 0, 1, 1, 0),
    (6910, 151395, 0, 1, 0, 1, 1, 0);

-- Uldaman
-- Baelog
DELETE FROM `creature_loot_template` WHERE `entry`=6906 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (6906, 9400, 0, 1, 0, 1, 1, 0),
    (6906, 9401, 0, 1, 0, 1, 1, 0),
    (6906, 151396, 0, 1, 0, 1, 1, 0),
    (6906, 9404, 0, 1, 0, 1, 1, 0),
    (6906, 132734, 0, 1, 0, 1, 1, 0),
    (6906, 9398, 0, 1, 0, 1, 1, 0),
    (6906, 9394, 0, 1, 0, 1, 1, 0),
    (6906, 9403, 0, 1, 0, 1, 1, 0);

-- Uldaman
-- Eric "The Swift"
DELETE FROM `creature_loot_template` WHERE `entry`=6907 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (6907, 9394, 0, 1, 0, 1, 1, 0),
    (6907, 9398, 0, 1, 0, 1, 1, 0),
    (6907, 9400, 0, 1, 0, 1, 1, 0),
    (6907, 9403, 0, 1, 0, 1, 1, 0),
    (6907, 151396, 0, 1, 0, 1, 1, 0),
    (6907, 9401, 0, 1, 0, 1, 1, 0),
    (6907, 9404, 0, 1, 0, 1, 1, 0),
    (6907, 132734, 0, 1, 0, 1, 1, 0);

-- Uldaman
-- Olaf
DELETE FROM `creature_loot_template` WHERE `entry`=6908 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (6908, 9403, 0, 1, 0, 1, 1, 0),
    (6908, 9404, 0, 1, 0, 1, 1, 0),
    (6908, 132734, 0, 1, 0, 1, 1, 0),
    (6908, 9400, 0, 1, 0, 1, 1, 0),
    (6908, 151396, 0, 1, 0, 1, 1, 0),
    (6908, 9394, 0, 1, 0, 1, 1, 0),
    (6908, 9401, 0, 1, 0, 1, 1, 0),
    (6908, 9398, 0, 1, 0, 1, 1, 0);

-- Uldaman
-- Ironaya
DELETE FROM `creature_loot_template` WHERE `entry`=7228 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7228, 9407, 0, 1, 0, 1, 1, 0),
    (7228, 9408, 0, 1, 0, 1, 1, 0),
    (7228, 9409, 0, 1, 0, 1, 1, 0),
    (7228, 151420, 0, 1, 0, 1, 1, 0),
    (7228, 151398, 0, 1, 0, 1, 1, 0);

-- Uldaman
-- Obsidian Sentinel
DELETE FROM `creature_loot_template` WHERE `entry`=7023 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7023, 151399, 0, 1, 0, 1, 1, 0);

-- Uldaman
-- Ancient Stone Keeper
DELETE FROM `creature_loot_template` WHERE `entry`=7206 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7206, 9411, 0, 1, 0, 1, 1, 0),
    (7206, 9410, 0, 1, 0, 1, 1, 0),
    (7206, 132733, 0, 1, 0, 1, 1, 0),
    (7206, 151400, 0, 1, 0, 1, 1, 0),
    (7206, 151401, 0, 1, 0, 1, 1, 0);

-- Uldaman
-- Grimlok <Stonevault Chieftain>
DELETE FROM `creature_loot_template` WHERE `entry`=4854 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (4854, 9415, 0, 1, 0, 1, 1, 0),
    (4854, 9414, 0, 1, 0, 1, 1, 0),
    (4854, 9416, 0, 1, 0, 1, 1, 0),
    (4854, 132735, 0, 1, 0, 1, 1, 0),
    (4854, 151402, 0, 1, 0, 1, 1, 0);

-- Scholomance
-- Rattlegore
DELETE FROM `creature_loot_template` WHERE `entry`=59153 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (59153, 88340, 0, 1, 0, 1, 1, 0),
    (59153, 88341, 0, 1, 0, 1, 1, 0),
    (59153, 88342, 0, 1, 0, 1, 1, 0),
    (59153, 88343, 0, 1, 0, 1, 1, 0),
    (59153, 88344, 0, 1, 0, 1, 1, 0),
    (59153, 88357, 0, 1, 0, 1, 1, 0);

-- Zul'Farrak
-- Gahz'rilla
DELETE FROM `creature_loot_template` WHERE `entry`=7273 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7273, 9467, 0, 1, 0, 1, 1, 0),
    (7273, 9469, 0, 1, 0, 1, 1, 0),
    (7273, 151455, 0, 1, 0, 1, 1, 0);

-- Zul'Farrak
-- Theka the Martyr
DELETE FROM `creature_loot_template` WHERE `entry`=7272 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7272, 9243, 0, 1, 0, 1, 1, 0),
    (7272, 151456, 0, 1, 0, 1, 1, 0);

-- Zul'Farrak
-- Witch Doctor Zum'rah
DELETE FROM `creature_loot_template` WHERE `entry`=7271 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7271, 18083, 0, 1, 0, 1, 1, 0),
    (7271, 18082, 0, 1, 0, 1, 1, 0),
    (7271, 151457, 0, 1, 0, 1, 1, 0),
    (7271, 9243, 0, 1, 0, 1, 1, 0);

-- Zul'Farrak
-- Nekrum Gutchewer
DELETE FROM `creature_loot_template` WHERE `entry`=7796 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7796, 9243, 0, 1, 0, 1, 1, 0),
    (7796, 9470, 0, 1, 0, 1, 1, 0),
    (7796, 9475, 0, 1, 0, 1, 1, 0),
    (7796, 9474, 0, 1, 0, 1, 1, 0),
    (7796, 9473, 0, 1, 0, 1, 1, 0),
    (7796, 151459, 0, 1, 0, 1, 1, 0),
    (7796, 151458, 0, 1, 0, 1, 1, 0);

-- Zul'Farrak
-- Shadowpriest Sezz'ziz
DELETE FROM `creature_loot_template` WHERE `entry`=7275 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7275, 9243, 0, 1, 0, 1, 1, 0),
    (7275, 9470, 0, 1, 0, 1, 1, 0),
    (7275, 9475, 0, 1, 0, 1, 1, 0),
    (7275, 9474, 0, 1, 0, 1, 1, 0),
    (7275, 9473, 0, 1, 0, 1, 1, 0),
    (7275, 151459, 0, 1, 0, 1, 1, 0),
    (7275, 151458, 0, 1, 0, 1, 1, 0);

-- Zul'Farrak
-- Chief Ukorz Sandscalp
DELETE FROM `creature_loot_template` WHERE `entry`=7267 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7267, 9479, 0, 1, 0, 1, 1, 0),
    (7267, 9478, 0, 1, 0, 1, 1, 0),
    (7267, 9476, 0, 1, 0, 1, 1, 0),
    (7267, 11086, 0, 1, 0, 1, 1, 0),
    (7267, 9477, 0, 1, 0, 1, 1, 0),
    (7267, 151460, 0, 1, 0, 1, 1, 0),
    (7267, 151461, 0, 1, 0, 1, 1, 0),
    (7267, 9243, 0, 1, 0, 1, 1, 0);
