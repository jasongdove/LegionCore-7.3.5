-- The Deadmines
-- Helix Gearbreaker
DELETE FROM `creature_loot_template` WHERE `entry`=47296 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (47296, 5191, 0, 1, 0, 1, 1, 0),
    (47296, 5199, 0, 1, 0, 1, 1, 0),
    (47296, 5200, 0, 1, 0, 1, 1, 0),
    (47296, 5443, 0, 1, 0, 1, 1, 0),
    (47296, 132556, 0, 1, 0, 1, 1, 0),
    (47296, 151062, 0, 1, 0, 1, 1, 0),
    (47296, 151063, 0, 1, 0, 1, 1, 0);

-- The Deadmines
-- Foe Reaper 5000
DELETE FROM `creature_loot_template` WHERE `entry`=43778 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (43778, 1937, 0, 1, 0, 1, 1, 0),
    (43778, 5187, 0, 1, 0, 1, 1, 0),
    (43778, 5201, 0, 1, 0, 1, 1, 0),
    (43778, 151064, 0, 1, 0, 1, 1, 0),
    (43778, 151065, 0, 1, 0, 1, 1, 0),
    (43778, 151066, 0, 1, 0, 1, 1, 0);

-- Ragefire Chasm
-- Adarogg
DELETE FROM `creature_loot_template` WHERE `entry`=61408 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid` IN (0,1) AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (61408, 82772, 0, 1, 0, 1, 1, 0),
    (61408, 82879, 0, 1, 0, 1, 1, 0),
    (61408, 82880, 0, 1, 0, 1, 1, 0),
    (61408, 151421, 0, 1, 0, 1, 1, 0),
    (61408, 151422, 0, 1, 0, 1, 1, 0);

-- Ragefire Chasm
-- Dark Shaman Koranthal
DELETE FROM `creature_loot_template` WHERE `entry`=61412 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid` IN (0,1) AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (61412, 82882, 0, 1, 0, 1, 1, 0),
    (61412, 82877, 0, 1, 0, 1, 1, 0),
    (61412, 82881, 0, 1, 0, 1, 1, 0),
    (61412, 132551, 0, 1, 0, 1, 1, 0);

-- Ragefire Chasm
-- Slagmaw
DELETE FROM `creature_loot_template` WHERE `entry`=61463 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid` IN (0,1) AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (61463, 82878, 0, 1, 0, 1, 1, 0),
    (61463, 82884, 0, 1, 0, 1, 1, 0),
    (61463, 82885, 0, 1, 0, 1, 1, 0),
    (61463, 132552, 0, 1, 0, 1, 1, 0);

-- Ragefire Chasm
-- Lava Guard Gordoth
DELETE FROM `creature_loot_template` WHERE `entry`=61528 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid` IN (0,1) AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (61528, 82883, 0, 1, 0, 1, 1, 0),
    (61528, 82886, 0, 1, 0, 1, 1, 0),
    (61528, 82888, 0, 1, 0, 1, 1, 0),
    (61528, 151424, 0, 1, 0, 1, 1, 0),
    (61528, 151425, 0, 1, 0, 1, 1, 0);

-- Shadowfang Keep
-- Commander Springvale
DELETE FROM `creature_loot_template` WHERE `entry`=4278 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (4278, 3191, 0, 1, 0, 1, 1, 0),
    (4278, 6320, 0, 1, 0, 1, 1, 0),
    (4278, 151067, 0, 1, 0, 1, 1, 0),
    (4278, 151068, 0, 1, 0, 1, 1, 0),
    (4278, 151069, 0, 1, 0, 1, 1, 0),
    (4278, 151070, 0, 1, 0, 1, 1, 0);

-- Shadowfang Keep
-- Lord Godfrey
DELETE FROM `creature_loot_template` WHERE `entry`=46964 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid` IN (0,1) AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (46964, 3748, 0, 1, 0, 1, 1, 0),
    (46964, 6220, 0, 1, 0, 1, 1, 0),
    (46964, 6318, 0, 1, 0, 1, 1, 0),
    (46964, 6641, 0, 1, 0, 1, 1, 0),
    (46964, 151071, 0, 1, 0, 1, 1, 0),
    (46964, 151072, 0, 1, 0, 1, 1, 0),
    (46964, 151073, 0, 1, 0, 1, 1, 0);

-- Wailing Caverns
-- Lady Anacondra <Fanglord>
DELETE FROM `creature_loot_template` WHERE `entry`=3671 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (3671, 5404, 0, 1, 0, 1, 1, 0),
    (3671, 6446, 0, 1, 0, 1, 1, 0),
    (3671, 10412, 0, 1, 0, 1, 1, 0),
    (3671, 132737, 0, 1, 0, 1, 1, 0),
    (3671, 132740, 0, 1, 0, 1, 1, 0),
    (3671, 151426, 0, 1, 0, 1, 1, 0),
    (3671, 151427, 0, 1, 0, 1, 1, 0);

-- Wailing Caverns
-- Kresh
DELETE FROM `creature_loot_template` WHERE `entry`=3653 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (3653, 6447, 0, 1, 0, 1, 1, 0),
    (3653, 13245, 0, 1, 0, 1, 1, 0),
    (3653, 151430, 0, 1, 0, 1, 1, 0);

-- Wailing Caverns
-- Lord Pythas <Fanglord>
DELETE FROM `creature_loot_template` WHERE `entry`=3670 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (3670, 6472, 0, 1, 0, 1, 1, 0),
    (3670, 6473, 0, 1, 0, 1, 1, 0),
    (3670, 132739, 0, 1, 0, 1, 1, 0),
    (3670, 151428, 0, 1, 0, 1, 1, 0),
    (3670, 151429, 0, 1, 0, 1, 1, 0);

-- Wailing Caverns
-- Mutanus the Devourer
DELETE FROM `creature_loot_template` WHERE `entry`=3654 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (3654, 6461, 0, 1, 0, 1, 1, 0),
    (3654, 6463, 0, 1, 0, 1, 1, 0),
    (3654, 6627, 0, 1, 0, 1, 1, 0);

-- Blackfathom Deeps
-- Ghamoo-Ra
DELETE FROM `creature_loot_template` WHERE `entry`=74446 AND `item` IN (6907, 6908, 151432, 151433) AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74446, 6907, 0, 1, 0, 1, 1, 0),
    (74446, 6908, 0, 1, 0, 1, 1, 0),
    (74446, 151432, 0, 1, 0, 1, 1, 0),
    (74446, 151433, 0, 1, 0, 1, 1, 0);

-- Blackfathom Deeps
-- Domina <Mistress of Shadows>
DELETE FROM `creature_loot_template` WHERE `entry`=74476 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74476, 888, 0, 1, 0, 1, 1, 0),
    (74476, 3078, 0, 1, 0, 1, 1, 0),
    (74476, 11121, 0, 1, 0, 1, 1, 0),
    (74476, 132554, 0, 1, 0, 1, 1, 0),
    (74476, 151434, 0, 1, 0, 1, 1, 0),
    (74476, 151435, 0, 1, 0, 1, 1, 0);

-- Blackfathom Deeps
-- Subjugator Kor'ul
DELETE FROM `creature_loot_template` WHERE `entry`=74565 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74565, 1470, 0, 1, 0, 1, 1, 0),
    (74565, 6905, 0, 1, 0, 1, 1, 0),
    (74565, 6906, 0, 1, 0, 1, 1, 0),
    (74565, 151436, 0, 1, 0, 1, 1, 0);

-- Blackfathom Deeps
-- Twilight Lord Bathiel
DELETE FROM `creature_loot_template` WHERE `entry`=74728 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (74728, 1155, 0, 1, 0, 1, 1, 0),
    (74728, 6903, 0, 1, 0, 1, 1, 0),
    (74728, 151438, 0, 1, 0, 1, 1, 0),
    (74728, 151439, 0, 1, 0, 1, 1, 0),
    (74728, 151440, 0, 1, 0, 1, 1, 0);

-- Blackfathom Deeps
-- Aku'mai
DELETE FROM `creature_loot_template` WHERE `entry`=75408 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (75408, 6909, 0, 1, 0, 1, 1, 0),
    (75408, 6910, 0, 1, 0, 1, 1, 0),
    (75408, 6911, 0, 1, 0, 1, 1, 0),
    (75408, 132553, 0, 1, 0, 1, 1, 0),
    (75408, 151441, 0, 1, 0, 1, 1, 0);

-- Maraudon
-- Noxxion
DELETE FROM `creature_loot_template` WHERE `entry`=13282 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (13282, 17744, 0, 1, 0, 1, 1, 0),
    (13282, 17745, 0, 1, 0, 1, 1, 0),
    (13282, 17746, 0, 1, 0, 1, 1, 0),
    (13282, 151449, 0, 1, 0, 1, 1, 0),
    (13282, 151450, 0, 1, 0, 1, 1, 0);

-- Maraudon
-- Razorlash
DELETE FROM `creature_loot_template` WHERE `entry`=12258 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (12258, 17748, 0, 1, 0, 1, 1, 0),
    (12258, 17749, 0, 1, 0, 1, 1, 0),
    (12258, 17750, 0, 1, 0, 1, 1, 0),
    (12258, 17751, 0, 1, 0, 1, 1, 0),
    (12258, 132562, 0, 1, 0, 1, 1, 0),
    (12258, 132563, 0, 1, 0, 1, 1, 0),
    (12258, 151451, 0, 1, 0, 1, 1, 0);

-- Maraudon
-- Lord Vyletongue
DELETE FROM `creature_loot_template` WHERE `entry`=12236 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (12236, 17752, 0, 1, 0, 1, 1, 0),
    (12236, 17754, 0, 1, 0, 1, 1, 0),
    (12236, 17755, 0, 1, 0, 1, 1, 0),
    (12236, 151447, 0, 1, 0, 1, 1, 0),
    (12236, 151448, 0, 1, 0, 1, 1, 0);

-- Maraudon
-- Landslide
DELETE FROM `creature_loot_template` WHERE `entry`=12203 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (12203, 17713, 0, 1, 0, 1, 1, 0),
    (12203, 17734, 0, 1, 0, 1, 1, 0),
    (12203, 17736, 0, 1, 0, 1, 1, 0),
    (12203, 17737, 0, 1, 0, 1, 1, 0),
    (12203, 17943, 0, 1, 0, 1, 1, 0);

-- Maraudon
-- Tinkerer Gizlock
DELETE FROM `creature_loot_template` WHERE `entry`=13601 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (13601, 17717, 0, 1, 0, 1, 1, 0),
    (13601, 17718, 0, 1, 0, 1, 1, 0),
    (13601, 17719, 0, 1, 0, 1, 1, 0),
    (13601, 151446, 0, 1, 0, 1, 1, 0);

-- Maraudon
-- Rotgrip
DELETE FROM `creature_loot_template` WHERE `entry`=13596 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (13596, 17728, 0, 1, 0, 1, 1, 0),
    (13596, 17730, 0, 1, 0, 1, 1, 0),
    (13596, 17732, 0, 1, 0, 1, 1, 0),
    (13596, 132564, 0, 1, 0, 1, 1, 0),
    (13596, 151452, 0, 1, 0, 1, 1, 0);

-- Gnomeregan
-- Grubbis
DELETE FROM `creature_loot_template` WHERE `entry`=7361 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7361, 9445, 0, 1, 0, 1, 1, 0),
    (7361, 151080, 0, 1, 0, 1, 1, 0),
    (7361, 151079, 0, 1, 0, 1, 1, 0),
    (7361, 151078, 0, 1, 0, 1, 1, 0);

-- Gnomeregan
-- Viscous Fallout
DELETE FROM `creature_loot_template` WHERE `entry`=7079 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (7079, 9452, 0, 1, 0, 1, 1, 0),
    (7079, 9453, 0, 1, 0, 1, 1, 0),
    (7079, 9454, 0, 1, 0, 1, 1, 0),
    (7079, 151081, 0, 1, 0, 1, 1, 0),
    (7079, 151082, 0, 1, 0, 1, 1, 0),
    (7079, 151083, 0, 1, 0, 1, 1, 0);

-- Gnomeregan
-- Crowd Pummeler 9-60
DELETE FROM `creature_loot_template` WHERE `entry`=6229 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (6229, 9449, 0, 1, 0, 1, 1, 0),
    (6229, 9450, 0, 1, 0, 1, 1, 0),
    (6229, 132558, 0, 1, 0, 1, 1, 0),
    (6229, 151084, 0, 1, 0, 1, 1, 0),
    (6229, 151085, 0, 1, 0, 1, 1, 0);

-- The Stockade
-- Randolph Moloch
DELETE FROM `creature_loot_template` WHERE `entry`=46383 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (46383, 63344, 0, 1, 0, 1, 1, 0),
    (46383, 63345, 0, 1, 0, 1, 1, 0),
    (46383, 63346, 0, 1, 0, 1, 1, 0),
    (46383, 132570, 0, 1, 0, 1, 1, 0),
    (46383, 151077, 0, 1, 0, 1, 1, 0);

-- The Stockade
-- Lord Overheat
DELETE FROM `creature_loot_template` WHERE `entry`=46264 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (46264, 1929, 0, 1, 0, 1, 1, 0),
    (46264, 4676, 0, 1, 0, 1, 1, 0),
    (46264, 5967, 0, 1, 0, 1, 1, 0),
    (46264, 151075, 0, 1, 0, 1, 1, 0),
    (46264, 151076, 0, 1, 0, 1, 1, 0);

-- The Stockade
-- Hogger
DELETE FROM `creature_loot_template` WHERE `entry`=46254 AND `ChanceOrQuestChance`=0 AND `lootmode`=1 AND `groupid`=0 AND `mincountOrRef`=1;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `shared`)
VALUES
    (46254, 1934, 0, 1, 0, 1, 1, 0),
    (46254, 1959, 0, 1, 0, 1, 1, 0),
    (46254, 2168, 0, 1, 0, 1, 1, 0),
    (46254, 132569, 0, 1, 0, 1, 1, 0),
    (46254, 151074, 0, 1, 0, 1, 1, 0);
