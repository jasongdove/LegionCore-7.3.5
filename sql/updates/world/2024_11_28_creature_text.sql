ALTER TABLE `creature_text`
    CHANGE COLUMN `Entry` `CreatureID` MEDIUMINT UNSIGNED NOT NULL DEFAULT '0',
    CHANGE COLUMN `Text` `Text` TEXT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
    CHANGE COLUMN `comment` `comment` VARCHAR(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT '';
