--
ALTER TABLE `gossip_menu_option`
    DROP `OptionType`,
    DROP `OptionNpcFlag`,
    CHANGE COLUMN `OptionIcon` `OptionNpc` MEDIUMINT UNSIGNED NOT NULL DEFAULT '0';

-- Drop "npc_experience" script use
UPDATE `creature_template` SET `ScriptName`='' WHERE `entry` IN (35364, 35365);

-- Update default option
DELETE FROM `gossip_menu_option` WHERE `MenuID`=0;
INSERT INTO `gossip_menu_option` (`MenuID`, `OptionID`, `OptionNpc`, `OptionText`, `OptionBroadcastTextId`, `ActionMenuID`, `ActionPoiID`, `BoxCoded`, `BoxMoney`, `BoxText`, `BoxBroadcastTextID`, `VerifiedBuild`) VALUES
(0, 1 , 1 , 'I want to browse your goods.', 3370, 0, 0, 0, 0, NULL, 0, 0),
(0, 2 , 2 , 'I''d like to travel by air.', 53141, 0, 0, 0, 0, NULL, 0, 0),
(0, 3 , 3 , 'Train me.', 3266, 0, 0, 0, 0, NULL, 0, 0),
(0, 4 , 4 , 'Return me to life.', 2547, 0, 0, 0, 0, NULL, 0, 0),
(0, 5 , 5 , 'Make this inn your home.', 2822, 0, 0, 0, 0, NULL, 0, 0),
(0, 6 , 6 , 'I would like to check my deposit box.', 3398, 0, 0, 0, 0, NULL, 0, 0),
(0, 7 , 7 , 'How do I form a guild?', 3413,  0, 0, 0, 0, NULL, 0, 0),
(0, 8 , 8 , 'I want to create a guild crest.', 3415, 0, 0, 0, 0, NULL, 0, 0),
(0, 9,  9 , 'I would like to go to the battleground.', 10355, 0, 0, 0, 0, NULL, 0, 0),
(0, 10, 10, 'I''d like to browse the items up for auction.', 52635, 0, 0, 0, 0, NULL, 0, 0),
(0, 12, 12, 'I''d like to stable my pet here.', 30181, 0, 0, 0, 0, NULL, 0, 0),
(0, 18, 18, 'I''d like to check my mail.', 146045, 0, 0, 0, 0, NULL, 0, 0),
(0, 34, 34, 'I want to transmogrify my gear.', 130510, 0, 0, 0, 0, NULL, 0, 0);
