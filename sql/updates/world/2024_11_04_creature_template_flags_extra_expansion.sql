-- remove LC CREATURE_FLAG_EXTRA_AUTO_LOOT 0x400 which is not used in code
UPDATE `creature_template` SET `flags_extra` = `flags_extra` & ~0x400;

-- remove LC value for CREATURE_FLAG_EXTRA_EVENT_LOOT 0x800, replace with TC value CREATURE_FLAG_EXTRA_UNUSED_22 0x400000
UPDATE `creature_template` SET `flags_extra` = `flags_extra` & ~0x800;
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 0x400000 WHERE `entry` IN (81252, 81535, 83746, 94015, 542159, 542160, 542185, 542191);

-- remove LC value for CREATURE_FLAG_EXTRA_EVENT_NPC 0x1000, replace with TC value CREATURE_FLAG_EXTRA_UNUSED_23 0x800000
UPDATE `creature_template` SET `flags_extra` = `flags_extra` & ~0x1000;
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 0x800000 WHERE `entry` IN (542100, 542101, 542102, 542103, 542104, 542105, 542106, 542111, 542112, 542118, 542119, 542130, 542131, 542132, 542133, 542134, 542185, 542191);

-- remove LC value for CREATURE_FLAG_EXTRA_VEHICLE_ATTACKABLE_PASSENGERS 0x20000000, replace with TC value CREATURE_FLAG_EXTRA_UNUSED_24 0x1000000
UPDATE `creature_template` SET `flags_extra` = `flags_extra` & ~0x20000000;
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 0x1000000 WHERE `entry` IN (37672, 38285, 39984, 44566, 44896, 44897, 45467, 45476, 47297, 47739, 48092, 48097, 48348, 48350, 48571, 49317, 52389, 52558, 52559, 52560, 52561, 52577, 53087, 53358, 53359, 53719, 53720, 53721, 53722, 56167, 56168, 56188, 56846, 57972, 57973, 57974, 57978, 58129, 58130, 58131, 58132, 58133, 58134, 58142, 58143, 67490, 67491, 67492, 67495, 71086, 72438, 76267, 77128, 77182, 77477, 77557, 78714, 91005, 92146, 93635, 93926, 97099, 99560, 99800, 99803, 100353, 100359, 100361, 103344, 104596, 107767, 109494, 122554, 122773, 122778, 123013, 123020);

-- remove LC value for CREATURE_FLAG_EXTRA_VEH_INSTANT_DESPAWN_PASSENGERS 0x40000000, replace with TC value CREATURE_FLAG_EXTRA_UNUSED_25 0x2000000
UPDATE `creature_template` SET `flags_extra` = `flags_extra` & ~0x40000000;
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 0x2000000 WHERE `entry` IN (48702, 122450);

-- remove LC value for CREATURE_FLAG_EXTRA_HP_85_PERC 0x80000000, replace with TC value CREATURE_FLAG_EXTRA_UNUSED_26 0x4000000
UPDATE `creature_template` SET `flags_extra` = `flags_extra` & ~0x80000000;
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 0x4000000 WHERE `entry` IN (28921, 45847, 46391, 54969, 55524, 55532);

-- remove LC value for CREATURE_FLAG_EXTRA_IMMUNITY_KNOCKBACK 0x2000, replace with TC value 0x40000000
UPDATE `creature_template` SET `flags_extra` = `flags_extra` & ~0x2000;
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 0x40000000 WHERE `entry` IN (91782, 91792, 91796, 92387, 95939, 97097, 97173, 97182, 97185, 97200, 98243, 98368, 98521, 98538, 98706, 102788, 105304, 105322, 105906, 111405, 111528, 111852, 111856, 111858, 111860, 111975, 112474, 113088, 113920);
