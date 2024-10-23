-- MySQL dump 10.13  Distrib 8.0.37, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: auth
-- ------------------------------------------------------
-- Server version	8.4.3

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `id` int unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `username` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `sha_pass_hash` varchar(512) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `sessionkey` varchar(512) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `v` varchar(512) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `s` varchar(512) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `email` varchar(254) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `joindate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `first_ip` varchar(15) CHARACTER SET utf8mb3 NOT NULL DEFAULT '127.0.0.1',
  `last_ip` varchar(15) CHARACTER SET utf8mb3 NOT NULL DEFAULT '127.0.0.1',
  `access_ip` int unsigned NOT NULL DEFAULT '0',
  `failed_logins` int unsigned NOT NULL DEFAULT '0',
  `email_blocked` int unsigned NOT NULL DEFAULT '0',
  `locked` tinyint unsigned NOT NULL DEFAULT '0',
  `lock_country` varchar(2) CHARACTER SET utf8mb3 NOT NULL DEFAULT '00',
  `last_login` timestamp NULL DEFAULT NULL,
  `last_email` timestamp NULL DEFAULT NULL,
  `online` tinyint unsigned NOT NULL DEFAULT '0',
  `expansion` tinyint unsigned NOT NULL DEFAULT '6',
  `mutetime` bigint NOT NULL DEFAULT '0',
  `locale` tinyint unsigned NOT NULL DEFAULT '0',
  `os` varchar(10) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `recruiter` int unsigned NOT NULL DEFAULT '0',
  `invite` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `lang` enum('tw','cn','en','ua','ru') CHARACTER SET utf8mb3 NOT NULL DEFAULT 'en',
  `referer` int unsigned NOT NULL DEFAULT '0',
  `unsubscribe` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '0',
  `dt_vote` timestamp NULL DEFAULT NULL,
  `mutereason` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `muteby` varchar(50) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `AtAuthFlag` smallint unsigned NOT NULL DEFAULT '0',
  `coins` int NOT NULL DEFAULT '0',
  `hwid` bigint unsigned NOT NULL DEFAULT '0',
  `balans` int NOT NULL DEFAULT '0',
  `karma` int unsigned NOT NULL DEFAULT '0',
  `activate` tinyint unsigned NOT NULL DEFAULT '1',
  `verify` tinyint unsigned NOT NULL DEFAULT '0',
  `tested` tinyint unsigned NOT NULL DEFAULT '0',
  `donate` int unsigned NOT NULL DEFAULT '0',
  `phone` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `phone_hash` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `telegram_lock` tinyint unsigned NOT NULL DEFAULT '0',
  `telegram_id` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE KEY `username` (`username`) USING BTREE,
  KEY `recruiter` (`recruiter`) USING BTREE,
  KEY `id` (`id`) USING BTREE,
  KEY `username_idx` (`username`) USING BTREE,
  KEY `hwid` (`hwid`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT COMMENT='Account System';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,'GM@GM','586EF64D6BCF71292B55C8805E465172D876E0C79968F925A0DCE5D9B4BAA492','','','','','2020-03-30 12:36:05','127.0.0.1','127.0.0.1',0,0,0,0,'00',NULL,NULL,0,6,0,0,'',0,'','en',0,'0',NULL,'','',0,0,0,0,0,1,0,0,0,'','',0,0);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_access`
--

DROP TABLE IF EXISTS `account_access`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_access` (
  `id` int unsigned NOT NULL,
  `gmlevel` tinyint unsigned NOT NULL,
  `RealmID` int NOT NULL DEFAULT '-1',
  `comments` varchar(50) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  PRIMARY KEY (`id`,`RealmID`) USING BTREE,
  KEY `id` (`id`) USING BTREE,
  KEY `RealmID` (`RealmID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_access`
--

LOCK TABLES `account_access` WRITE;
/*!40000 ALTER TABLE `account_access` DISABLE KEYS */;
INSERT INTO `account_access` VALUES (1,6,-1,'');
/*!40000 ALTER TABLE `account_access` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_banned`
--

DROP TABLE IF EXISTS `account_banned`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_banned` (
  `id` int unsigned NOT NULL DEFAULT '0' COMMENT 'Account id',
  `bandate` int unsigned NOT NULL DEFAULT '0',
  `unbandate` int unsigned NOT NULL DEFAULT '0',
  `bannedby` varchar(50) CHARACTER SET utf8mb3 NOT NULL,
  `banreason` varchar(255) CHARACTER SET utf8mb3 NOT NULL,
  `active` tinyint unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`bandate`) USING BTREE,
  KEY `id` (`id`) USING BTREE,
  KEY `bandate` (`bandate`) USING BTREE,
  KEY `unbandate` (`unbandate`) USING BTREE,
  KEY `active` (`active`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT COMMENT='Ban List';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_banned`
--

LOCK TABLES `account_banned` WRITE;
/*!40000 ALTER TABLE `account_banned` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_banned` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_character_template`
--

DROP TABLE IF EXISTS `account_character_template`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_character_template` (
  `id` int NOT NULL AUTO_INCREMENT,
  `account` int NOT NULL DEFAULT '0',
  `bnet_account` int NOT NULL DEFAULT '0',
  `level` tinyint unsigned NOT NULL DEFAULT '100',
  `iLevel` mediumint NOT NULL DEFAULT '810',
  `money` int unsigned NOT NULL DEFAULT '100',
  `artifact` tinyint(1) NOT NULL DEFAULT '0',
  `transferId` int NOT NULL DEFAULT '0',
  `charGuid` int NOT NULL DEFAULT '0',
  `realm` int NOT NULL DEFAULT '0',
  `templateId` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE,
  KEY `id` (`id`) USING BTREE,
  KEY `account` (`account`) USING BTREE,
  KEY `bnet_account` (`bnet_account`) USING BTREE,
  KEY `transferId` (`transferId`) USING BTREE,
  KEY `charGuid` (`charGuid`) USING BTREE,
  KEY `realm` (`realm`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_character_template`
--

LOCK TABLES `account_character_template` WRITE;
/*!40000 ALTER TABLE `account_character_template` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_character_template` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_donate_token_log`
--

DROP TABLE IF EXISTS `account_donate_token_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_donate_token_log` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `accountId` int unsigned NOT NULL,
  `realmId` int unsigned NOT NULL,
  `characterId` bigint unsigned NOT NULL,
  `change` bigint NOT NULL DEFAULT '0',
  `tokenType` tinyint unsigned NOT NULL,
  `buyType` tinyint unsigned NOT NULL,
  `productId` int unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_donate_token_log`
--

LOCK TABLES `account_donate_token_log` WRITE;
/*!40000 ALTER TABLE `account_donate_token_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_donate_token_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_flagged`
--

DROP TABLE IF EXISTS `account_flagged`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_flagged` (
  `id` int unsigned NOT NULL DEFAULT '0' COMMENT 'Account Id',
  `banduration` int unsigned NOT NULL DEFAULT '0',
  `bannedby` varchar(50) CHARACTER SET utf8mb3 NOT NULL,
  `banreason` varchar(255) CHARACTER SET utf8mb3 NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_flagged`
--

LOCK TABLES `account_flagged` WRITE;
/*!40000 ALTER TABLE `account_flagged` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_flagged` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_ip_access`
--

DROP TABLE IF EXISTS `account_ip_access`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_ip_access` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `pid` int unsigned DEFAULT NULL,
  `ip` varchar(18) CHARACTER SET utf8mb3 DEFAULT NULL,
  `min` varchar(15) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `max` varchar(15) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `enable` tinyint unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE KEY `pid_ip` (`pid`,`ip`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_ip_access`
--

LOCK TABLES `account_ip_access` WRITE;
/*!40000 ALTER TABLE `account_ip_access` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_ip_access` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_last_played_character`
--

DROP TABLE IF EXISTS `account_last_played_character`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_last_played_character` (
  `accountId` int unsigned NOT NULL,
  `region` tinyint unsigned NOT NULL,
  `battlegroup` tinyint unsigned NOT NULL,
  `realmId` int unsigned DEFAULT NULL,
  `characterName` varchar(12) CHARACTER SET utf8mb3 DEFAULT NULL,
  `characterGUID` bigint unsigned DEFAULT NULL,
  `lastPlayedTime` int unsigned DEFAULT NULL,
  PRIMARY KEY (`accountId`,`region`,`battlegroup`) USING BTREE,
  KEY `accountId` (`accountId`) USING BTREE,
  KEY `region` (`region`) USING BTREE,
  KEY `battlegroup` (`battlegroup`) USING BTREE,
  KEY `realmId` (`realmId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_last_played_character`
--

LOCK TABLES `account_last_played_character` WRITE;
/*!40000 ALTER TABLE `account_last_played_character` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_last_played_character` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_mute`
--

DROP TABLE IF EXISTS `account_mute`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_mute` (
  `guid` int unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `mutedate` int unsigned NOT NULL DEFAULT '0',
  `mutetime` int unsigned NOT NULL DEFAULT '0',
  `mutedby` varchar(50) CHARACTER SET utf8mb3 NOT NULL,
  `mutereason` varchar(255) CHARACTER SET utf8mb3 NOT NULL,
  PRIMARY KEY (`guid`,`mutedate`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT COMMENT='mute List';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_mute`
--

LOCK TABLES `account_mute` WRITE;
/*!40000 ALTER TABLE `account_mute` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_mute` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_muted`
--

DROP TABLE IF EXISTS `account_muted`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_muted` (
  `id` int NOT NULL DEFAULT '0' COMMENT 'Account id',
  `bandate` bigint NOT NULL DEFAULT '0',
  `unbandate` bigint NOT NULL DEFAULT '0',
  `bannedby` varchar(50) CHARACTER SET utf8mb3 NOT NULL,
  `banreason` varchar(255) CHARACTER SET utf8mb3 NOT NULL,
  `active` tinyint NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`bandate`) USING BTREE,
  KEY `bandate` (`bandate`) USING BTREE,
  KEY `unbandate` (`unbandate`) USING BTREE,
  KEY `active` (`active`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT COMMENT='Ban List';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_muted`
--

LOCK TABLES `account_muted` WRITE;
/*!40000 ALTER TABLE `account_muted` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_muted` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_rates`
--

DROP TABLE IF EXISTS `account_rates`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_rates` (
  `account` int NOT NULL DEFAULT '0',
  `realm` int unsigned NOT NULL DEFAULT '0',
  `rate` int unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `unique` (`account`,`realm`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_rates`
--

LOCK TABLES `account_rates` WRITE;
/*!40000 ALTER TABLE `account_rates` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_rates` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_tokens`
--

DROP TABLE IF EXISTS `account_tokens`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_tokens` (
  `account_id` int unsigned NOT NULL,
  `tokenType` tinyint unsigned NOT NULL,
  `amount` bigint NOT NULL DEFAULT '0',
  PRIMARY KEY (`account_id`,`tokenType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_tokens`
--

LOCK TABLES `account_tokens` WRITE;
/*!40000 ALTER TABLE `account_tokens` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_tokens` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `build_info`
--

DROP TABLE IF EXISTS `build_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `build_info` (
  `build` int NOT NULL,
  `majorVersion` int DEFAULT NULL,
  `minorVersion` int DEFAULT NULL,
  `bugfixVersion` int DEFAULT NULL,
  `hotfixVersion` char(3) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `winAuthSeed` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `win64AuthSeed` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `mac64AuthSeed` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `winChecksumSeed` varchar(40) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `macChecksumSeed` varchar(40) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  PRIMARY KEY (`build`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `build_info`
--

LOCK TABLES `build_info` WRITE;
/*!40000 ALTER TABLE `build_info` DISABLE KEYS */;
INSERT INTO `build_info` VALUES (5875,1,12,1,NULL,NULL,NULL,NULL,'95EDB27C7823B363CBDDAB56A392E7CB73FCCA20','8D173CC381961EEBABF336F5E6675B101BB513E5'),(6005,1,12,2,NULL,NULL,NULL,NULL,NULL,NULL),(6141,1,12,3,NULL,NULL,NULL,NULL,NULL,NULL),(8606,2,4,3,NULL,NULL,NULL,NULL,'319AFAA3F2559682F9FF658BE01456255F456FB1','D8B0ECFE534BC1131E19BAD1D4C0E813EEE4994F'),(9947,3,1,3,NULL,NULL,NULL,NULL,NULL,NULL),(10505,3,2,2,'a',NULL,NULL,NULL,NULL,NULL),(11159,3,3,0,'a',NULL,NULL,NULL,NULL,NULL),(11403,3,3,2,NULL,NULL,NULL,NULL,NULL,NULL),(11723,3,3,3,'a',NULL,NULL,NULL,NULL,NULL),(12340,3,3,5,'a',NULL,NULL,NULL,'CDCBBD5188315E6B4D19449D492DBCFAF156A347','B706D13FF2F4018839729461E3F8A0E2B5FDC034'),(13623,4,0,6,'a',NULL,NULL,NULL,NULL,NULL),(13930,3,3,5,'a',NULL,NULL,NULL,NULL,NULL),(14545,4,2,2,NULL,NULL,NULL,NULL,NULL,NULL),(15595,4,3,4,NULL,NULL,NULL,NULL,NULL,NULL),(19116,6,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(19243,6,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(19342,6,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(19702,6,1,0,NULL,NULL,NULL,NULL,NULL,NULL),(19802,6,1,2,NULL,NULL,NULL,NULL,NULL,NULL),(19831,6,1,2,NULL,NULL,NULL,NULL,NULL,NULL),(19865,6,1,2,NULL,NULL,NULL,NULL,NULL,NULL),(20182,6,2,0,'a',NULL,NULL,NULL,NULL,NULL),(20201,6,2,0,NULL,NULL,NULL,NULL,NULL,NULL),(20216,6,2,0,NULL,NULL,NULL,NULL,NULL,NULL),(20253,6,2,0,NULL,NULL,NULL,NULL,NULL,NULL),(20338,6,2,0,NULL,NULL,NULL,NULL,NULL,NULL),(20444,6,2,2,NULL,NULL,NULL,NULL,NULL,NULL),(20490,6,2,2,'a',NULL,NULL,NULL,NULL,NULL),(20574,6,2,2,'a',NULL,NULL,NULL,NULL,NULL),(20726,6,2,3,NULL,NULL,NULL,NULL,NULL,NULL),(20779,6,2,3,NULL,NULL,NULL,NULL,NULL,NULL),(20886,6,2,3,NULL,NULL,NULL,NULL,NULL,NULL),(21355,6,2,4,NULL,NULL,NULL,NULL,NULL,NULL),(21463,6,2,4,NULL,NULL,NULL,NULL,NULL,NULL),(21742,6,2,4,NULL,NULL,NULL,NULL,NULL,NULL),(22248,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22293,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22345,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22410,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22423,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22498,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22522,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22566,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22594,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22624,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22747,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22810,7,0,3,NULL,NULL,NULL,NULL,NULL,NULL),(22900,7,1,0,NULL,NULL,NULL,NULL,NULL,NULL),(22908,7,1,0,NULL,NULL,NULL,NULL,NULL,NULL),(22950,7,1,0,NULL,NULL,NULL,NULL,NULL,NULL),(22995,7,1,0,NULL,NULL,NULL,NULL,NULL,NULL),(22996,7,1,0,NULL,NULL,NULL,NULL,NULL,NULL),(23171,7,1,0,NULL,NULL,NULL,NULL,NULL,NULL),(23222,7,1,0,NULL,NULL,NULL,NULL,NULL,NULL),(23360,7,1,5,NULL,NULL,NULL,NULL,NULL,NULL),(23420,7,1,5,NULL,NULL,NULL,NULL,NULL,NULL),(23911,7,2,0,NULL,NULL,NULL,NULL,NULL,NULL),(23937,7,2,0,NULL,NULL,NULL,NULL,NULL,NULL),(24015,7,2,0,NULL,NULL,NULL,NULL,NULL,NULL),(24330,7,2,5,NULL,NULL,NULL,NULL,NULL,NULL),(24367,7,2,5,NULL,NULL,NULL,NULL,NULL,NULL),(24415,7,2,5,NULL,NULL,NULL,NULL,NULL,NULL),(24430,7,2,5,NULL,NULL,NULL,NULL,NULL,NULL),(24461,7,2,5,NULL,NULL,NULL,NULL,NULL,NULL),(24742,7,2,5,NULL,NULL,NULL,NULL,NULL,NULL),(25549,7,3,2,NULL,'FE594FC35E7F9AFF86D99D8A364AB297','1252624ED8CBD6FAC7D33F5D67A535F3','66FC5E09B8706126795F140308C8C1D8',NULL,NULL),(25996,7,3,5,NULL,'23C59C5963CBEF5B728D13A50878DFCB','C7FF932D6A2174A3D538CA7212136D2B','210B970149D6F56CAC9BADF2AAC91E8E',NULL,NULL),(26124,7,3,5,NULL,'F8C05AE372DECA1D6C81DA7A8D1C5C39','46DF06D0147BA67BA49AF553435E093F','C9CA997AB8EDE1C65465CB2920869C4E',NULL,NULL),(26365,7,3,5,NULL,'2AAC82C80E829E2CA902D70CFA1A833A','59A53F307288454B419B13E694DF503C','DBE7F860276D6B400AAA86B35D51A417',NULL,NULL),(26654,7,3,5,NULL,'FAC2D693E702B9EC9F750F17245696D8','A752640E8B99FE5B57C1320BC492895A','9234C1BD5E9687ADBD19F764F2E0E811',NULL,NULL),(26822,7,3,5,NULL,'283E8D77ECF7060BE6347BE4EB99C7C7','2B05F6D746C0C6CC7EF79450B309E595','91003668C245D14ECD8DF094E065E06B',NULL,NULL),(26899,7,3,5,NULL,'F462CD2FE4EA3EADF875308FDBB18C99','3551EF0028B51E92170559BD25644B03','8368EFC2021329110A16339D298200D4',NULL,NULL),(26972,7,3,5,NULL,'797ECC19662DCBD5090A4481173F1D26','6E212DEF6A0124A3D9AD07F5E322F7AE','341CFEFE3D72ACA9A4407DC535DED66A',NULL,NULL);
/*!40000 ALTER TABLE `build_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hwid_penalties`
--

DROP TABLE IF EXISTS `hwid_penalties`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `hwid_penalties` (
  `hwid` bigint unsigned NOT NULL,
  `penalties` int NOT NULL DEFAULT '0',
  `last_reason` varchar(255) CHARACTER SET utf8mb3 NOT NULL,
  PRIMARY KEY (`hwid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hwid_penalties`
--

LOCK TABLES `hwid_penalties` WRITE;
/*!40000 ALTER TABLE `hwid_penalties` DISABLE KEYS */;
/*!40000 ALTER TABLE `hwid_penalties` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ip_banned`
--

DROP TABLE IF EXISTS `ip_banned`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ip_banned` (
  `ip` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '127.0.0.1',
  `bandate` bigint NOT NULL,
  `unbandate` bigint NOT NULL,
  `bannedby` varchar(50) CHARACTER SET utf8mb3 NOT NULL DEFAULT '[Console]',
  `banreason` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT 'no reason',
  PRIMARY KEY (`ip`,`bandate`) USING BTREE,
  KEY `ip` (`ip`) USING BTREE,
  KEY `bandate` (`bandate`) USING BTREE,
  KEY `unbandate` (`unbandate`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT COMMENT='Banned IPs';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ip_banned`
--

LOCK TABLES `ip_banned` WRITE;
/*!40000 ALTER TABLE `ip_banned` DISABLE KEYS */;
/*!40000 ALTER TABLE `ip_banned` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `logs`
--

DROP TABLE IF EXISTS `logs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `logs` (
  `time` int NOT NULL,
  `realm` int NOT NULL,
  `type` int NOT NULL,
  `level` int NOT NULL DEFAULT '0',
  `string` text CHARACTER SET latin1,
  KEY `time` (`time`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `logs`
--

LOCK TABLES `logs` WRITE;
/*!40000 ALTER TABLE `logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `logs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `online`
--

DROP TABLE IF EXISTS `online`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `online` (
  `realmID` int unsigned NOT NULL DEFAULT '0',
  `online` int unsigned NOT NULL DEFAULT '0',
  `diff` int unsigned NOT NULL DEFAULT '0',
  `uptime` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`realmID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `online`
--

LOCK TABLES `online` WRITE;
/*!40000 ALTER TABLE `online` DISABLE KEYS */;
/*!40000 ALTER TABLE `online` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `realmcharacters`
--

DROP TABLE IF EXISTS `realmcharacters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `realmcharacters` (
  `realmid` int unsigned NOT NULL DEFAULT '0',
  `acctid` int unsigned NOT NULL,
  `numchars` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`realmid`,`acctid`) USING BTREE,
  KEY `acctid` (`acctid`) USING BTREE,
  KEY `realmid` (`realmid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT COMMENT='Realm Character Tracker';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `realmcharacters`
--

LOCK TABLES `realmcharacters` WRITE;
/*!40000 ALTER TABLE `realmcharacters` DISABLE KEYS */;
/*!40000 ALTER TABLE `realmcharacters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `realmlist`
--

DROP TABLE IF EXISTS `realmlist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `realmlist` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `address` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT '127.0.0.1',
  `port` smallint unsigned NOT NULL DEFAULT '8085',
  `gamePort` int NOT NULL DEFAULT '8086',
  `portCount` mediumint unsigned NOT NULL DEFAULT '1',
  `icon` tinyint unsigned NOT NULL DEFAULT '0',
  `flag` tinyint unsigned NOT NULL DEFAULT '2',
  `timezone` tinyint unsigned NOT NULL DEFAULT '1',
  `allowedSecurityLevel` tinyint unsigned NOT NULL DEFAULT '0',
  `population` float unsigned NOT NULL DEFAULT '0',
  `gamebuild` int unsigned NOT NULL DEFAULT '26972',
  `Region` tinyint unsigned NOT NULL DEFAULT '2',
  `Battlegroup` tinyint unsigned NOT NULL DEFAULT '1',
  `localAddress` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT '127.0.0.1',
  `localSubnetMask` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT '255.255.255.0',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE KEY `idx_name` (`name`) USING BTREE,
  KEY `id` (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT COMMENT='Realm System';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `realmlist`
--

LOCK TABLES `realmlist` WRITE;
/*!40000 ALTER TABLE `realmlist` DISABLE KEYS */;
INSERT INTO `realmlist` VALUES (1,'LegionCore','127.0.0.1',8085,8086,1,0,2,1,0,0,26972,2,1,'127.0.0.1','255.255.255.0');
/*!40000 ALTER TABLE `realmlist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `store_categories`
--

DROP TABLE IF EXISTS `store_categories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `store_categories` (
  `id` int NOT NULL AUTO_INCREMENT,
  `pid` int unsigned NOT NULL,
  `type` smallint NOT NULL DEFAULT '0',
  `sort` int unsigned NOT NULL DEFAULT '0',
  `faction` tinyint unsigned NOT NULL DEFAULT '0',
  `expansion` tinyint unsigned NOT NULL DEFAULT '6',
  `enable` tinyint unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`) USING BTREE,
  KEY `enable` (`enable`) USING BTREE,
  KEY `id` (`id`) USING BTREE,
  KEY `sort` (`sort`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `store_categories`
--

LOCK TABLES `store_categories` WRITE;
/*!40000 ALTER TABLE `store_categories` DISABLE KEYS */;
/*!40000 ALTER TABLE `store_categories` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `store_category_locales`
--

DROP TABLE IF EXISTS `store_category_locales`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `store_category_locales` (
  `category` int NOT NULL DEFAULT '0',
  `name_us` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_gb` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_kr` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_fr` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_de` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_cn` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_tw` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_es` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_mx` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_ru` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_pt` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_br` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_it` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `name_ua` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_us` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_gb` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_kr` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_fr` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_de` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_cn` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_tw` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_es` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_mx` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_ru` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_pt` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_br` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_it` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `description_ua` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  PRIMARY KEY (`category`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `store_category_locales`
--

LOCK TABLES `store_category_locales` WRITE;
/*!40000 ALTER TABLE `store_category_locales` DISABLE KEYS */;
/*!40000 ALTER TABLE `store_category_locales` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `store_category_realms`
--

DROP TABLE IF EXISTS `store_category_realms`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `store_category_realms` (
  `category` int NOT NULL DEFAULT '0',
  `realm` int unsigned NOT NULL DEFAULT '0',
  `return` tinyint unsigned NOT NULL DEFAULT '0',
  `enable` tinyint unsigned NOT NULL DEFAULT '1',
  UNIQUE KEY `unique` (`category`,`realm`) USING BTREE,
  KEY `category` (`category`) USING BTREE,
  KEY `realm` (`realm`) USING BTREE,
  KEY `enable` (`enable`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `store_category_realms`
--

LOCK TABLES `store_category_realms` WRITE;
/*!40000 ALTER TABLE `store_category_realms` DISABLE KEYS */;
/*!40000 ALTER TABLE `store_category_realms` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `store_discounts`
--

DROP TABLE IF EXISTS `store_discounts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `store_discounts` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `realm` int unsigned NOT NULL DEFAULT '0',
  `category` int NOT NULL DEFAULT '0',
  `product` int NOT NULL DEFAULT '0',
  `start` timestamp NULL DEFAULT NULL,
  `end` timestamp NULL DEFAULT NULL,
  `rate` float(5,2) unsigned NOT NULL DEFAULT '0.00',
  `enable` tinyint unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `store_discounts`
--

LOCK TABLES `store_discounts` WRITE;
/*!40000 ALTER TABLE `store_discounts` DISABLE KEYS */;
/*!40000 ALTER TABLE `store_discounts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `store_level_prices`
--

DROP TABLE IF EXISTS `store_level_prices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `store_level_prices` (
  `type` tinyint unsigned NOT NULL DEFAULT '0',
  `realm` int unsigned NOT NULL DEFAULT '0',
  `level` smallint unsigned NOT NULL DEFAULT '0',
  `token` int unsigned NOT NULL DEFAULT '0',
  `karma` int unsigned NOT NULL DEFAULT '0',
  UNIQUE KEY `unique` (`type`,`realm`,`level`,`token`) USING BTREE,
  KEY `type` (`type`) USING BTREE,
  KEY `realm` (`realm`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `store_level_prices`
--

LOCK TABLES `store_level_prices` WRITE;
/*!40000 ALTER TABLE `store_level_prices` DISABLE KEYS */;
/*!40000 ALTER TABLE `store_level_prices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `store_product_locales`
--

DROP TABLE IF EXISTS `store_product_locales`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `store_product_locales` (
  `product` int NOT NULL DEFAULT '0',
  `type` smallint NOT NULL DEFAULT '0',
  `us` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `gb` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `kr` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `fr` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `de` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `cn` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `tw` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `es` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `mx` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `ru` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `pt` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `br` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `it` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `ua` varchar(128) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  PRIMARY KEY (`product`,`type`) USING BTREE,
  UNIQUE KEY `unique` (`product`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `store_product_locales`
--

LOCK TABLES `store_product_locales` WRITE;
/*!40000 ALTER TABLE `store_product_locales` DISABLE KEYS */;
/*!40000 ALTER TABLE `store_product_locales` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `store_product_realms`
--

DROP TABLE IF EXISTS `store_product_realms`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `store_product_realms` (
  `product` int NOT NULL DEFAULT '0',
  `realm` int unsigned NOT NULL DEFAULT '0',
  `token` int unsigned NOT NULL DEFAULT '0',
  `karma` int unsigned NOT NULL DEFAULT '0',
  `return` tinyint unsigned NOT NULL DEFAULT '0',
  `enable` tinyint unsigned NOT NULL DEFAULT '1',
  `dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  UNIQUE KEY `unique` (`realm`,`product`) USING BTREE,
  KEY `product` (`product`) USING BTREE,
  KEY `realm` (`realm`) USING BTREE,
  KEY `enable` (`enable`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `store_product_realms`
--

LOCK TABLES `store_product_realms` WRITE;
/*!40000 ALTER TABLE `store_product_realms` DISABLE KEYS */;
/*!40000 ALTER TABLE `store_product_realms` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `store_products`
--

DROP TABLE IF EXISTS `store_products`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `store_products` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `category` int NOT NULL DEFAULT '0',
  `item` int NOT NULL DEFAULT '0',
  `bonus` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `icon` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `quality` tinyint unsigned NOT NULL DEFAULT '0',
  `display` int unsigned NOT NULL DEFAULT '0',
  `slot` int unsigned NOT NULL DEFAULT '0',
  `type` int unsigned NOT NULL DEFAULT '0',
  `token` int unsigned NOT NULL DEFAULT '0',
  `karma` int unsigned NOT NULL DEFAULT '0',
  `enable` tinyint unsigned NOT NULL DEFAULT '1',
  `dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `faction` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE KEY `unique` (`category`,`item`,`bonus`) USING BTREE,
  KEY `id` (`id`) USING BTREE,
  KEY `category` (`category`) USING BTREE,
  KEY `enable` (`enable`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `store_products`
--

LOCK TABLES `store_products` WRITE;
/*!40000 ALTER TABLE `store_products` DISABLE KEYS */;
/*!40000 ALTER TABLE `store_products` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transfer_requests`
--

DROP TABLE IF EXISTS `transfer_requests`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transfer_requests` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `acid` int unsigned NOT NULL,
  `bacid` int unsigned NOT NULL DEFAULT '0',
  `user_name` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `email` varchar(64) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `guid` int unsigned DEFAULT NULL,
  `char_faction` tinyint unsigned DEFAULT NULL,
  `char_class` tinyint unsigned DEFAULT NULL,
  `char_set` int unsigned DEFAULT NULL,
  `realm` tinyint unsigned NOT NULL,
  `dump` mediumtext CHARACTER SET utf8mb3,
  `promo_code` varchar(32) CHARACTER SET utf8mb3 DEFAULT '',
  `client_expansion` tinyint unsigned DEFAULT NULL,
  `client_build` smallint unsigned DEFAULT NULL,
  `client_locale` varchar(4) CHARACTER SET utf8mb3 DEFAULT '',
  `site` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `realmlist` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `transfer_user_name` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `password` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `transfer_realm` varchar(32) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `char_name` varchar(12) CHARACTER SET utf8mb3 NOT NULL DEFAULT '',
  `dump_version` varchar(255) CHARACTER SET utf8mb3 DEFAULT '',
  `dt_create` timestamp NULL DEFAULT NULL,
  `dt_update` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `moderator` int unsigned DEFAULT NULL,
  `comment` varchar(255) CHARACTER SET utf8mb3 DEFAULT '',
  `cost` int unsigned NOT NULL DEFAULT '0',
  `type` enum('fee','free') CHARACTER SET utf8mb3 NOT NULL DEFAULT 'free',
  `test` tinyint unsigned NOT NULL DEFAULT '0',
  `status` enum('check','test','paid','cancel','4','2','0','reject','payment','verify','new') CHARACTER SET utf8mb3 NOT NULL DEFAULT 'new',
  `parser` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transfer_requests`
--

LOCK TABLES `transfer_requests` WRITE;
/*!40000 ALTER TABLE `transfer_requests` DISABLE KEYS */;
/*!40000 ALTER TABLE `transfer_requests` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transferts`
--

DROP TABLE IF EXISTS `transferts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transferts` (
  `id` int NOT NULL AUTO_INCREMENT,
  `account` int NOT NULL DEFAULT '0',
  `perso_guid` int NOT NULL DEFAULT '0',
  `from` int NOT NULL DEFAULT '0',
  `to` int NOT NULL DEFAULT '0',
  `toacc` int NOT NULL DEFAULT '0',
  `dump` longtext CHARACTER SET utf8mb3 NOT NULL,
  `nb_attempt` int NOT NULL DEFAULT '0',
  `state` int DEFAULT '0',
  `error` int DEFAULT '0',
  `revision` int DEFAULT '0',
  `transferId` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE,
  KEY `account` (`account`) USING BTREE,
  KEY `perso_guid` (`perso_guid`) USING BTREE,
  KEY `from` (`from`) USING BTREE,
  KEY `to` (`to`) USING BTREE,
  KEY `state` (`state`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transferts`
--

LOCK TABLES `transferts` WRITE;
/*!40000 ALTER TABLE `transferts` DISABLE KEYS */;
/*!40000 ALTER TABLE `transferts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transferts_logs`
--

DROP TABLE IF EXISTS `transferts_logs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transferts_logs` (
  `id` int DEFAULT NULL,
  `account` int DEFAULT '0',
  `perso_guid` int DEFAULT '0',
  `from` int DEFAULT '0',
  `to` int DEFAULT '0',
  `dump` longtext CHARACTER SET utf8mb3,
  `toacc` int NOT NULL DEFAULT '0',
  `newguid` int NOT NULL DEFAULT '0',
  `transferId` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transferts_logs`
--

LOCK TABLES `transferts_logs` WRITE;
/*!40000 ALTER TABLE `transferts_logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `transferts_logs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `updates`
--

DROP TABLE IF EXISTS `updates`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `updates` (
  `name` varchar(200) CHARACTER SET utf8mb3 NOT NULL COMMENT 'filename with extension of the update.',
  `hash` char(40) CHARACTER SET utf8mb3 DEFAULT '' COMMENT 'sha1 hash of the sql file.',
  `state` enum('RELEASED','ARCHIVED') CHARACTER SET utf8mb3 NOT NULL DEFAULT 'RELEASED' COMMENT 'defines if an update is released or archived.',
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'timestamp when the query was applied.',
  `speed` int unsigned NOT NULL DEFAULT '0' COMMENT 'time the query takes to apply in ms.',
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='List of all applied updates in this database.';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `updates`
--

LOCK TABLES `updates` WRITE;
/*!40000 ALTER TABLE `updates` DISABLE KEYS */;
INSERT INTO `updates` VALUES ('0001_merge_account_tables.sql','EA324472D26CF0F4F9D549399755B68367E0C6BB','ARCHIVED','2024-10-23 17:42:18',261),('0002_battlepay_cleanup.sql','6863CF4041258A421FA4E4FAB4D6B3325936BDAA','ARCHIVED','2024-10-23 17:42:18',227),('0003_battlepay_rework.sql','3CDD4C9CFDE4BBF0C84EC2443B2F10150E5E92DB','ARCHIVED','2024-10-23 17:42:18',171);
/*!40000 ALTER TABLE `updates` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `updates_include`
--

DROP TABLE IF EXISTS `updates_include`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `updates_include` (
  `path` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'directory to include. $ means relative to the source directory.',
  `state` enum('RELEASED','ARCHIVED') CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT 'RELEASED' COMMENT 'defines if the directory contains released or archived updates.',
  PRIMARY KEY (`path`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='List of directories where we want to include sql updates.';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `updates_include`
--

LOCK TABLES `updates_include` WRITE;
/*!40000 ALTER TABLE `updates_include` DISABLE KEYS */;
INSERT INTO `updates_include` VALUES ('$/sql/old/auth','ARCHIVED'),('$/sql/updates/auth','RELEASED');
/*!40000 ALTER TABLE `updates_include` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `uptime`
--

DROP TABLE IF EXISTS `uptime`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `uptime` (
  `realmid` int unsigned NOT NULL,
  `starttime` bigint unsigned NOT NULL DEFAULT '0',
  `startstring` varchar(255) CHARACTER SET utf8mb3 DEFAULT NULL,
  `uptime` bigint unsigned NOT NULL DEFAULT '0',
  `maxplayers` smallint unsigned NOT NULL DEFAULT '0',
  `revision` varchar(255) CHARACTER SET utf8mb3 NOT NULL DEFAULT 'LegionCore',
  PRIMARY KEY (`realmid`,`starttime`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci ROW_FORMAT=COMPACT COMMENT='Uptime system';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `uptime`
--

LOCK TABLES `uptime` WRITE;
/*!40000 ALTER TABLE `uptime` DISABLE KEYS */;
/*!40000 ALTER TABLE `uptime` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `version`
--

DROP TABLE IF EXISTS `version`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `version` (
  `core_version` varchar(120) CHARACTER SET utf8mb3 DEFAULT NULL COMMENT 'Core revision dumped at startup.',
  `core_revision` varchar(120) CHARACTER SET utf8mb3 DEFAULT NULL,
  `db_version` varchar(120) CHARACTER SET utf8mb3 DEFAULT NULL COMMENT 'Version of auth DB.'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Version Notes';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `version`
--

LOCK TABLES `version` WRITE;
/*!40000 ALTER TABLE `version` DISABLE KEYS */;
INSERT INTO `version` VALUES ('LegionCore 2020-04-03 (Win64, Release)','','LegionCore Auth Database 2024-10-23');
/*!40000 ALTER TABLE `version` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-10-23 12:45:22
