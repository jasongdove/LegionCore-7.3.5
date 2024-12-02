--
DELETE FROM `trinity_string` WHERE `entry` IN (11100);
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES
(11100, 'Movement type: %s');
