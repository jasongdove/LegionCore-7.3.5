ALTER TABLE `character_pet`
    ADD COLUMN `slot` tinyint(3) unsigned NOT NULL DEFAULT '0';

ALTER TABLE `character_pet`
    ADD KEY `idx_slot` (`slot`);

-- current pet is now stored in character_pet.slot 0
ALTER TABLE `characters`
    DROP COLUMN `currentpetnumber`,
    DROP COLUMN `petslot`,
    ADD COLUMN `stable_slots` tinyint(3) unsigned NOT NULL DEFAULT '0' AFTER `extra_flags`;
