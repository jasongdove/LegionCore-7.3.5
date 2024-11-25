--
DROP TABLE `transferts`;
DROP TABLE `transferts_logs`;
DROP TABLE `transfer_requests`;

ALTER TABLE `account_character_template`
    DROP COLUMN `transferId`;
