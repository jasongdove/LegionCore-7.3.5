--
ALTER TABLE `gossip_menu`
    DROP COLUMN `FriendshipFactionID`,
    CHANGE COLUMN `Entry` `MenuID` INT UNSIGNED NOT NULL;

ALTER TABLE `gossip_menu_option`
    CHANGE COLUMN `OptionIndex` `OptionID` SMALLINT UNSIGNED NOT NULL DEFAULT '0',
    CHANGE COLUMN `OptionNPC` `OptionIcon` MEDIUMINT UNSIGNED NOT NULL DEFAULT '0',
    CHANGE COLUMN `OptionText` `OptionText` TEXT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
    CHANGE COLUMN `OptionBroadcastTextID` `OptionBroadcastTextID` INT UNSIGNED NOT NULL DEFAULT '0' AFTER `OptionText`,
    CHANGE COLUMN `OptionNpcflag` `OptionNpcFlag` INT UNSIGNED NOT NULL DEFAULT '0',
    DROP COLUMN `OptionNpcflag2`,
    CHANGE COLUMN `BoxText` `BoxText` TEXT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
    DROP COLUMN `BoxCurrency`;

ALTER TABLE `gossip_menu_option_locale`
    CHANGE COLUMN `ID` `OptionID` MEDIUMINT UNSIGNED NOT NULL DEFAULT '0',
    CHANGE COLUMN `Locale` `Locale` VARCHAR(4) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
    CHANGE COLUMN `OptionText` `OptionText` TEXT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
    CHANGE COLUMN `BoxText` `BoxText` TEXT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
    DROP COLUMN `VerifiedBuild`;
