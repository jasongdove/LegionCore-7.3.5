--
ALTER TABLE `creature`
    CHANGE COLUMN `PhaseId` `LegacyPhaseId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
    ADD `PhaseId` INT(10) DEFAULT '0' AFTER `LegacyPhaseId`,
    ADD `PhaseGroup` INT(10) DEFAULT '0' AFTER `PhaseId`;

ALTER TABLE `gameobject`
    CHANGE COLUMN `PhaseId` `LegacyPhaseId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
    ADD `PhaseId` INT(10) DEFAULT '0' AFTER `LegacyPhaseId`,
    ADD `PhaseGroup` INT(10) DEFAULT '0' AFTER `PhaseId`;

-- keep LC data in case it's needed for conversion later
RENAME TABLE `spell_phase` TO `lc_spell_phase`;
RENAME TABLE `phase_definitions` TO `lc_phase_definitions`;

DROP TABLE IF EXISTS `phase_definitions`;

CREATE TABLE `phase_definitions` (
  `zoneId` int(10) unsigned NOT NULL DEFAULT '0',
  `entry` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `phaseId` int(10) unsigned NOT NULL DEFAULT '0',
  `phaseGroup` int(10) NOT NULL DEFAULT '0',
  `comment` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  PRIMARY KEY (`zoneId`,`entry`),
  UNIQUE KEY (`entry`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `phase_info`;

CREATE TABLE `phase_info` (
  `id` int(10) unsigned NOT NULL DEFAULT '0',
  `worldmapareaswap` int(10) unsigned NOT NULL DEFAULT '0',
  `terrainswapmap` int(10) unsigned NOT NULL DEFAULT '0',
  `comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

ALTER TABLE `transports`
    ADD COLUMN `phaseid` INT(10) NOT NULL DEFAULT 0 AFTER `name`,
    ADD COLUMN `phasegroup` INT(10) NOT NULL DEFAULT 0 AFTER `phaseid`;
