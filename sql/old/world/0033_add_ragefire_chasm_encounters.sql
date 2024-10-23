DELETE FROM `instance_encounters` WHERE `entry` IN (1443, 1444, 1445, 1446);

INSERT INTO `instance_encounters` (`entry`, `difficulty`, `creditType`, `creditEntry`, `lastEncounterDungeon`, `comment`) VALUES
(1443, -1, 0, 61408, 0, 'Adarogg'),
(1444, -1, 0, 61412, 0, 'Dark Shaman Koranthal'),
(1445, -1, 0, 61463, 0, 'Slagmaw'),
(1446, -1, 0, 61528, 4, 'Lava Guard Gordoth');

DELETE FROM `instance_template` WHERE `map` = 389;

INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`, `bonusChance`) VALUES
(389, 1, 'instance_ragefire_chasm', 1, 20);

UPDATE `creature_template` SET `ScriptName` = 'boss_adarogg' WHERE `entry` = 61408;
UPDATE `creature_template` SET `ScriptName` = 'boss_dark_shaman_koranthal' WHERE `entry` = 61412;
UPDATE `creature_template` SET `ScriptName` = 'boss_slagmaw' WHERE `entry` = 61463;
UPDATE `creature_template` SET `ScriptName` = 'boss_lava_guard_gordoth' WHERE `entry` = 61528;

DELETE FROM `areatrigger_scripts` WHERE `entry`=7899;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
    (7899, 'at_lava_guard_gordoth_intro');
