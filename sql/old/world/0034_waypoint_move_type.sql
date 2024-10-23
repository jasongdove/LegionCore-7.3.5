ALTER TABLE `waypoint_data` CHANGE `move_flag` `move_type` INT(11) NOT NULL DEFAULT 0;

ALTER TABLE `waypoint_data_script` CHANGE `move_flag` `move_type` INT(11) NOT NULL DEFAULT 0;
