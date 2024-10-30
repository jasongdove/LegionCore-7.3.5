DELETE FROM `smart_scripts` WHERE `entryorguid` IN (3840, 384000);

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `Difficulties`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`)
VALUES
(3840, 0, 0, 0, '1', 4, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang  - On Aggro - Set Event Phase 1 (Normal Dungeon)'),
(3840, 0, 1, 0, '1', 25, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang  - On Reset - Set Event Phase 0 (Normal Dungeon)'),
(3840, 0, 2, 0, '1', 0, 1, 100, 0, 0, 0, 3500, 4000, 11, 9532, 64, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang - In Combat CMC - Cast ''Lightning Bolt'' (Phase 1) (Normal Dungeon)'),
(3840, 0, 3, 0, '1', 0, 1, 100, 0, 37000, 37000, 24000, 26000, 80, 384000, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang  - In Combat - Run Script (Phase 1) (Normal Dungeon)'),
(3840, 0, 4, 0, '1', 0, 0, 100, 0, 8000, 11000, 10000, 20000, 11, 8040, 33, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang - In Combat - Cast ''Druid''s Slumber'' (Normal Dungeon)'),
(3840, 0, 5, 0, '1', 74, 0, 100, 0, 0, 40, 12000, 18000, 11, 23381, 1, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang - On Friendly Between 0-40% Health - Cast ''Healing Touch'' (Normal Dungeon)'),
(384000, 9, 0, 0, '1', 0, 0, 100, 0, 100, 100, 0, 0, 22, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang - Script - Set Event Phase 0'),
(384000, 9, 1, 0, '1', 0, 0, 100, 0, 100, 100, 0, 0, 21, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang - Script - Enable Combat Movement'),
(384000, 9, 2, 0, '1', 0, 0, 100, 0, 100, 100, 0, 0, 11, 8041, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang - Script - Cast ''Serpent Form'''),
(384000, 9, 3, 0, '1', 0, 0, 100, 0, 10000, 12000, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Druid of the Fang - Script - Set Event Phase 1');
