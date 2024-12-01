--
DELETE FROM `trinity_string` WHERE `entry` IN (1204, 1265);
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES
(1204, 'You have entered areatrigger %u.'),
(1265, 'You have left areatrigger %u.');