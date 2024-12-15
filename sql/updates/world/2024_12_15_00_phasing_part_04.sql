-- UiWorldMapAreaID is all zero, no need to keep
ALTER TABLE `lc_phase_definitions`
    DROP COLUMN `UiWorldMapAreaID`,
    CHANGE COLUMN `PreloadMapID` `TerrainSwapMap`  SMALLINT UNSIGNED NOT NULL DEFAULT '0';

-- insert missing data
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 0 AND `TerrainSwapMap` IN (736, 1066, 1190);
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 1 AND `TerrainSwapMap` IN (1074, 1817);
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 654 AND `TerrainSwapMap` IN (638, 655, 656);
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 648 AND `TerrainSwapMap` IN (659, 661);
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 860 AND `TerrainSwapMap` IN (975, 976);
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 870 AND `TerrainSwapMap` IN (1061, 1062);
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 1064 AND `TerrainSwapMap` IN (1120, 1121);
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 1220 AND `TerrainSwapMap` IN (1527, 1532);
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 1265 AND `TerrainSwapMap` IN (1307);
DELETE FROM `terrain_swap_defaults` WHERE `MapId` = 1464 AND `TerrainSwapMap` IN (1465);

INSERT INTO `terrain_swap_defaults` (MapId, TerrainSwapMap, Comment) VALUES
(654, 638, 'Gilneas default terrain'),
(654, 655, 'Gilneas duskhaven phase 1'),
(654, 656, 'Gilneas duskhaven phase 2'),
(648, 659, 'Lost Isles - Volcano Eruption'),
(648, 661, 'Lost Isles - Town in the Box'),
(0, 736, 'Twilight Highlands Dragonmaw Phase'),
(0, 1066, 'Stormwind Gunship Pandaria Start Area'),
(0, 1190, 'Blasted Lands Phase'),
(1, 1074, 'Orgrimmar Gunship Pandaria Start'),
(1, 1817, 'Silithus: The Wound'),
(860, 975, 'Wandering Isle terrain injured'),
(860, 976, 'Wandering Isle terrain healed'),
(870, 1061, 'Horde Beach Daily Area'),
(870, 1062, 'Alliance Beach Daily Area'),
(1064, 1120, 'Thunder King Horde Hub'),
(1064, 1121, 'Thunder Island Alliance Hub'),
(1265, 1307, 'Tanaan Jungle Intro - Forge Phase'),
(1220, 1527, 'High Mountain Scenario'),
(1220, 1532, 'High Mountain Mesa Scenario'),
(1464, 1465, 'Tanaan Jungle - No Hubs Phase');
