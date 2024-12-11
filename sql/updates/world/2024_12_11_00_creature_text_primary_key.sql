-- change primary key; should not include text, but lots of cleanup will be needed to remove it
ALTER TABLE `creature_text` DROP PRIMARY KEY, ADD PRIMARY KEY (`CreatureID`,`GroupID`,`ID`,`Text`(250));
