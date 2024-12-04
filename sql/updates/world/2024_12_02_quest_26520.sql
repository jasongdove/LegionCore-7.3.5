--
DELETE FROM `creature_template_addon` WHERE `entry` IN (341,382,43194,43196);
DELETE FROM `creature_template_addon` WHERE `entry` BETWEEN 648 AND 653;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(341,0,0,65543,1,0,'80694'),
(382,0,0,65536,1,0, '80698'),
(648,0,0,65536,1,0,'80698'),
(649,0,0,65536,1,0,'80698'),
(650,0,0,65536,1,0,'80698'),
(651,0,0,65536,1,0,'80698'),
(652,0,0,65536,1,0,'80698'),
(653,0,0,65536,1,0,'80698'),
(43194,0,0,65536,1,0, '80699'),
(43196,0,0,65536,1,0,'80694');

-- bridge workers animation
UPDATE `creature` SET `AiID` = 726 WHERE `id` BETWEEN 648 AND 653;

-- Detect Quest Invis Zone 1
DELETE FROM `spell_area` WHERE `spell` IN (80695) AND `area` = 44;
INSERT INTO `spell_area` (`spell`,`area`,`quest_start`,`quest_end`,`aura_spell`,`racemask`,`gender`,`autocast`,`quest_start_status`,`quest_end_status`) VALUES
(80695,44,0,26520,0,18875469,2,1,0,11); -- Zone Wide

-- Detect Quest Invis Zone 2
DELETE FROM `spell_area` WHERE `spell` IN (80696) AND `area` = 44;
INSERT INTO `spell_area` (`spell`,`area`,`quest_start`,`quest_end`,`aura_spell`,`racemask`,`gender`,`autocast`,`quest_start_status`,`quest_end_status`) VALUES
(80696,44,26520,0,0,18875469,2,1,64,0); -- Zone Wide

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` IN (80704, 80739);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 2, 80704, 0, 0, 31, 0, 3, 43094, 0, 0, 0, '', 'Control Ettin - Target Canyon Ettin'),
(13, 2, 80704, 0, 1, 31, 0, 3, 43196, 0, 0, 0, '', 'Control Ettin - Target Huge Boulder'),
(13, 1, 80739, 0, 0, 31, 0, 3, 43197, 0, 0, 0, '', 'Lift Huge Boulder - Target Subdued Canyon Ettin');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 80704;
UPDATE `creature_template` SET `AIName` = '' WHERE `entry` IN (341, 648, 649, 650, 651, 652, 653, 43196, 43197);
UPDATE `creature_template` SET `ScriptName` = 'npc_redridge_huge_boulder' WHERE `entry` = 43196;
UPDATE `creature_template` SET `ScriptName` = 'npc_redridge_subdued_ettin' WHERE `entry` = 43197;
UPDATE `creature_template` SET `VehicleId` = 938 WHERE `entry` = 43197;

-- clean out old data
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (341, 648, 649, 650, 651, 652, 653, 43196, 43197) AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 4319600 AND `source_type` = 9;

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43094;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 43094 AND `source_type` = 0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(43094, 0, 0, 0, 8, 0, 100, 0, 80702, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Canyon Ettin - On Spellhit - Despawn');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (80702, 80704, 80739);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(80704, 'spell_redridge_control_ettin'),
(80739, 'spell_redridge_lift_huge_boulder');

DELETE FROM `creature_text` WHERE `CreatureID` = 43197;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `comment`) VALUES
(43197, 0, 0, 'ROCK NOT SO HEAVY! PUNY HUMIES!', 12, 0, 100, 0, 0, 0, 43218, ''),
(43197, 1, 0, 'Where trow? TROW ON BRIDGE??', 12, 0, 100, 0, 0, 0, 43220, ''),
(43197, 2, 0, 'OK! Me trow in water!', 12, 0, 100, 0, 0, 0, 43222, '');

-- marshall marris should be sitting and drinking
SET @ENTRY := 382;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
UPDATE `creature_template_addon` SET `bytes1` = 65541 WHERE `entry` = @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=-38726 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-38726,0,0,0,1,0,100,0,8000,8000,8000,8000,11,58952,0,0,0,0,0,1,0,0,0,0,0,0,0,'Marshal Marris - OOC - Cast ''Drink Alcohol''');

-- Pathing for Guard Ashlock Entry: 932
SET @NPC := 38725;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9281.391,`position_y`=-2286.225,`position_z`=67.7533 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,257,0, '5301');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9281.391,-2286.225,67.7533,0,0,0,0,100,0),
(@PATH,2,-9326.391,-2282.725,71.5033,0,0,0,0,100,0),
(@PATH,3,-9365.141,-2279.975,71.5033,0,0,0,0,100,0),
(@PATH,4,-9401.141,-2268.725,68.0033,0,0,0,0,100,0),
(@PATH,5,-9406.141,-2265.225,67.7533,0,0,0,0,100,0),
(@PATH,6,-9411.66,-2264.84,67.44,0,120000,0,0,100,0),
(@PATH,7,-9412.391,-2266.225,67.5033,0,0,0,0,100,0),
(@PATH,8,-9412.891,-2274.725,67.7533,0,0,0,0,100,0),
(@PATH,9,-9364.891,-2279.725,71.5033,0,0,0,0,100,0),
(@PATH,10,-9330.391,-2282.725,71.7533,0,0,0,0,100,0),
(@PATH,11,-9291.391,-2285.975,67.7533,0,0,0,0,100,0),
(@PATH,12,-9282.12,-2287.61,67.5666,0,120000,0,0,100,0);

-- Pathing for Guard Clarke Entry: 934
SET @NPC := 38634;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9344.355,`position_y`=-2206.349,`position_z`=61.89775 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,257,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9344.355,-2206.349,61.89775,0,0,0,0,100,0),
(@PATH,2,-9335.028,-2207.953,61.89775,0,0,0,0,100,0),
(@PATH,3,-9322.396,-2210.031,61.89775,0,0,0,0,100,0),
(@PATH,4,-9311.435,-2210.67,61.89775,0,0,0,0,100,0),
(@PATH,5,-9297.224,-2212.776,61.89775,0,0,0,0,100,0),
(@PATH,6,-9285.208,-2216.076,63.25996,0,0,0,0,100,0),
(@PATH,7,-9284.114,-2226.769,63.39107,0,0,0,0,100,0),
(@PATH,8,-9283.647,-2243.695,63.57106,0,0,0,0,100,0),
(@PATH,9,-9281.135,-2260.52,65.97218,0,0,0,0,100,0),
(@PATH,10,-9275.419,-2273.584,67.4109,0,0,0,0,100,0),
(@PATH,11,-9271.06,-2266.026,66.2466,0,0,0,0,100,0),
(@PATH,12,-9270.646,-2245.761,64.04616,0,0,0,0,100,0),
(@PATH,13,-9269.661,-2222.433,64.04756,0,0,0,0,100,0),
(@PATH,14,-9268.26,-2200.005,64.05788,0,0,0,0,100,0),
(@PATH,15,-9266.45,-2182.234,64.08961,0,0,0,0,100,0),
(@PATH,16,-9268.26,-2200.005,64.05788,0,0,0,0,100,0),
(@PATH,17,-9269.661,-2222.433,64.04756,0,0,0,0,100,0),
(@PATH,18,-9270.646,-2245.761,64.04616,0,0,0,0,100,0),
(@PATH,19,-9271.06,-2266.026,66.2466,0,0,0,0,100,0),
(@PATH,20,-9275.419,-2273.584,67.4109,0,0,0,0,100,0),
(@PATH,21,-9281.135,-2260.52,65.97218,0,0,0,0,100,0),
(@PATH,22,-9283.647,-2243.695,63.57106,0,0,0,0,100,0),
(@PATH,23,-9284.114,-2226.769,63.39107,0,0,0,0,100,0),
(@PATH,24,-9285.208,-2216.076,63.25996,0,0,0,0,100,0),
(@PATH,25,-9296.33,-2212.813,61.89775,0,0,0,0,100,0),
(@PATH,26,-9311.435,-2210.67,61.89775,0,0,0,0,100,0),
(@PATH,27,-9322.396,-2210.031,61.89775,0,0,0,0,100,0),
(@PATH,28,-9335.001,-2207.957,61.89775,0,0,0,0,100,0);

-- Pathing for Guard Adams Entry: 936
SET @NPC := 38537;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9212.636,`position_y`=-2174.064,`position_z`=64.05842 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,257,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9212.636,-2174.064,64.05842,0,0,0,0,100,0),
(@PATH,2,-9245.297,-2171.292,63.93879,0,0,0,0,100,0),
(@PATH,3,-9245.685,-2167.466,63.93879,0,30000,0,0,100,0),
(@PATH,4,-9253.704,-2167.139,64.05788,0,0,0,0,100,0),
(@PATH,5,-9254.052,-2135.928,63.93991,0,0,0,0,100,0),
(@PATH,6,-9246.497,-2115.215,66.55289,0,0,0,0,100,0),
(@PATH,7,-9243.474,-2098.984,72.62241,0,0,0,0,100,0),
(@PATH,8,-9239.848,-2075.51,75.75473,0,0,0,0,100,0),
(@PATH,9,-9234.389,-2072.974,76.53476,0,0,0,0,100,0),
(@PATH,10,-9234.089,-2083.617,76.79282,0,0,0,0,100,0),
(@PATH,11,-9220.588,-2089.068,81.41252,0,0,0,0,100,0),
(@PATH,12,-9206.651,-2088.978,86.12273,0,0,0,0,100,0),
(@PATH,13,-9189.044,-2094.362,87.86027,0,15000,0,0,100,0),
(@PATH,14,-9235.082,-2087.048,76.55405,0,0,0,0,100,0),
(@PATH,15,-9245.788,-2099.052,72.19589,0,0,0,0,100,0),
(@PATH,16,-9246.594,-2118.702,65.59097,0,0,0,0,100,0),
(@PATH,17,-9232.146,-2130.648,64.05843,0,0,0,0,100,0),
(@PATH,18,-9212.241,-2135.419,64.05843,0,0,0,0,100,0),
(@PATH,19,-9187.412,-2138.506,64.00642,0,0,0,0,100,0),
(@PATH,20,-9187.227,-2160.702,64.05843,0,0,0,0,100,0);

-- Pathing for Dorin Songblade Entry: 956
SET @NPC := 38684;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9247.676,`position_y`=-2240.278,`position_z`=64.05842 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9247.676,-2240.278,64.05842,0,0,0,0,100,0),
(@PATH,2,-9247.676,-2240.278,64.05842,2.583087,42000,0,0,100,0),
(@PATH,3,-9250.197,-2244.496,64.05842,0,42000,0,0,100,0);

-- remove duplicate ettins, duplicate master pet tamer
DELETE FROM `creature` WHERE `guid` IN (38740, 38849, 261577);

-- insert second marshal marris
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `PhaseId`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `unit_flags3`) VALUES
(38740, 382, 0, 0, 0, 1, 1, '',0, 1, -9276.96, -2242.86, 64.1778, 1.13446, 120, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = 38740;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(38740, 0, 0, 0, 0, 0, '80699');

-- Pathing for Canyon Ettin Entry: 43094
SET @NPC := 38410;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-9105.46,`position_y`=-2208.16,`position_z`=126.5163 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-9105.46,-2208.16,126.5163,0,0,0,0,100,0),
(@PATH,2,-9134.289,-2211.389,121.312,0,0,0,0,100,0),
(@PATH,3,-9137.49,-2173.55,121.3245,0,0,0,0,100,0),
(@PATH,4,-9127.85,-2137.67,123.4426,0,0,0,0,100,0),
(@PATH,5,-9128.25,-2095.07,122.8061,0,0,0,0,100,0),
(@PATH,6,-9103.65,-2086.67,127.4204,0,0,0,0,100,0),
(@PATH,7,-9117.41,-2069.33,128.6535,0,0,0,0,100,0),
(@PATH,8,-9111.11,-2064.42,128.7022,0,0,0,0,100,0),
(@PATH,9,-9093.48,-2076.93,128.7146,0,0,0,0,100,0),
(@PATH,10,-9070.16,-2087.55,129.0393,0,0,0,0,100,0),
(@PATH,11,-9039.8,-2095.06,130.9568,0,0,0,0,100,0),
(@PATH,12,-9015.53,-2091.76,132.5085,0,0,0,0,100,0),
(@PATH,13,-9002.63,-2119.99,137.521,0,0,0,0,100,0),
(@PATH,14,-9002.05,-2138.25,143.4562,0,0,0,0,100,0),
(@PATH,15,-9001.05,-2160,133.3666,0,0,0,0,100,0),
(@PATH,16,-9009.8,-2185.88,136.2239,0,0,0,0,100,0),
(@PATH,17,-9041.53,-2193.89,131.472,0,0,0,0,100,0),
(@PATH,18,-9068.82,-2174.21,132.5518,0,0,0,0,100,0),
(@PATH,19,-9087,-2190.03,132.4278,0,0,0,0,100,0);

-- Pathing for Canyon Ettin Entry: 43094
SET @NPC := 38466;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-8923.51,`position_y`=-2304.27,`position_z`=133.0706 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-8923.51,-2304.27,133.0706,0,0,0,0,100,0),
(@PATH,2,-8931.27,-2331.67,132.8773,0,0,0,0,100,0),
(@PATH,3,-8962.34,-2333.7,132.5694,0,0,0,0,100,0),
(@PATH,4,-8982.57,-2351.04,132.5728,0,0,0,0,100,0),
(@PATH,5,-9000.23,-2379.13,132.4703,0,0,0,0,100,0),
(@PATH,6,-9017.43,-2401.64,130.3283,0,0,0,0,100,0),
(@PATH,7,-9021.813,-2423.211,131.7126,0,0,0,0,100,0),
(@PATH,8,-9050.23,-2437.75,128.3464,0,0,0,0,100,0),
(@PATH,9,-9062.48,-2407.44,127.3151,0,0,0,0,100,0),
(@PATH,10,-9094.87,-2388.64,124.0265,0,0,0,0,100,0),
(@PATH,11,-9112.47,-2360.19,121.6273,0,0,0,0,100,0),
(@PATH,12,-9111.24,-2354.57,122.5619,0,0,0,0,100,0),
(@PATH,13,-9095.8,-2382.87,123.9354,0,0,0,0,100,0),
(@PATH,14,-9061.45,-2399.56,128.0016,0,0,0,0,100,0),
(@PATH,15,-9018.48,-2392.57,130.7203,0,0,0,0,100,0),
(@PATH,16,-8992.11,-2368.29,132.5635,0,0,0,0,100,0),
(@PATH,17,-8964.82,-2329.2,132.5481,0,0,0,0,100,0),
(@PATH,18,-8956.58,-2292.35,132.5678,0,0,0,0,100,0),
(@PATH,19,-8926.41,-2279.25,132.7044,0,0,0,0,100,0),
(@PATH,20,-8905.42,-2245.47,133.3376,0,0,0,0,100,0),
(@PATH,21,-8881.15,-2266.83,133.1034,0,0,0,0,100,0),
(@PATH,22,-8895.5,-2281.12,133.7757,0,0,0,0,100,0),
(@PATH,23,-8915.54,-2283.71,132.3846,0,0,0,0,100,0);

-- Foreman Oslow text
DELETE FROM `creature_text` WHERE `CreatureID`=341;
INSERT INTO `creature_text` (`CreatureID`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES
(341, 0, 0, 'Somebody... please... get... rock... off... me...', 12, 0, 100, 0, 0, 0, 43173, 'Foreman Oslow'),
(341, 0, 1, 'Hurts... Hurts so bad...', 12, 0, 100, 0, 0, 0, 43174, 'Foreman Oslow'),
(341, 0, 2, 'Please... kill... me...', 12, 0, 100, 0, 0, 0, 43175, 'Foreman Oslow'),
(341, 0, 3, 'I... just... wanted... to... build... the... damned... bridge...', 12, 0, 100, 0, 0, 0, 43176, 'Foreman Oslow');

-- Bridge Worker Alex text
DELETE FROM `creature_text` WHERE `CreatureID` IN (653,648,649,650,651,652);
INSERT INTO `creature_text` (`CreatureID`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES
(653, 0, 0, 'PUT YOUR BACKS INTO IT, BOYS!', 12, 0, 100, 0, 0, 0, 43181, 'Bridge Worker Alex'),
(653, 1, 0, 'HEAVE!', 12, 0, 100, 0, 0, 0, 43182, 'Bridge Worker Alex'),
(653, 2, 0, 'DAMN ROCK WON''T BUDGE!', 12, 0, 100, 0, 0, 0, 43184, 'Bridge Worker Alex'),
(653, 4, 0, 'PUSH HARDER!', 12, 0, 100, 0, 0, 0, 43185, 'Bridge Worker Alex'),
(653, 3, 0, 'We''ll get you out of there, Foreman, just HANG ON!', 12, 0, 100, 0, 0, 0, 43187, 'Bridge Worker Alex'),
(648, 0, 0, 'HO!', 12, 0, 100, 0, 0, 0, 43183, 'Bridge Worker Trent'),
(649, 0, 0, 'HO!', 12, 0, 100, 0, 0, 0, 43183, 'Bridge Worker Dimitri'),
(650, 0, 0, 'HO!', 12, 0, 100, 0, 0, 0, 43183, 'Bridge Worker Jess'),
(651, 0, 0, 'HO!', 12, 0, 100, 0, 0, 0, 43183, 'Bridge Worker Daniel'),
(652, 0, 0, 'HO!', 12, 0, 100, 0, 0, 0, 43183, 'Bridge Worker Matthew'),
(652, 1, 0, 'I''M PUSHIN'' AS HARD AS I CAN! THING WEIGHS A TON!', 12, 0, 100, 0, 0, 0, 43186, 'Bridge Worker Matthew');
