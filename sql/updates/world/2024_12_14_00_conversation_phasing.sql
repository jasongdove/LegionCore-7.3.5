--
ALTER TABLE `conversation`
    CHANGE COLUMN `PhaseId` `LegacyPhaseId` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
    ADD `PhaseId` INT(10) DEFAULT '0' AFTER `LegacyPhaseId`,
    ADD `PhaseGroup` INT(10) DEFAULT '0' AFTER `PhaseId`,
    ADD `terrainSwapMap` int(11) NOT NULL DEFAULT '-1' AFTER `PhaseGroup`,
    ADD `phaseUseFlags` tinyint(3) unsigned NOT NULL DEFAULT '0' AFTER `spawnMask`;
