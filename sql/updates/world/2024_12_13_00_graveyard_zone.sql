--
RENAME TABLE `game_graveyard_zone` TO `graveyard_zone`;

ALTER TABLE `graveyard_zone`
    CHANGE `id` `ID` MEDIUMINT UNSIGNED DEFAULT '0' NOT NULL,
    CHANGE `ghost_zone` `GhostZone` MEDIUMINT UNSIGNED DEFAULT '0' NOT NULL,
    CHANGE `faction` `Faction` SMALLINT UNSIGNED DEFAULT '0' NOT NULL;
