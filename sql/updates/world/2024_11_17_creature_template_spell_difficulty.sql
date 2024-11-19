--
ALTER TABLE `creature_template_spell`
    ADD COLUMN `Difficulties` VARCHAR(100) NOT NULL DEFAULT '' COLLATE 'utf8mb4_unicode_ci' AFTER `difficultyMask`,
    DROP COLUMN `timerCast`;

