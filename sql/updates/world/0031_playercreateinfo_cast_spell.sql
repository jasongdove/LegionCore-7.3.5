RENAME TABLE `playercreateinfo_spell` TO `playercreateinfo_spell_custom`;

--
-- Table structure for table `playercreateinfo_cast_spell`
--

DROP TABLE IF EXISTS `playercreateinfo_cast_spell`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `playercreateinfo_cast_spell` (
  `raceMask` bigint unsigned NOT NULL,
  `classMask` int unsigned NOT NULL DEFAULT '0',
  `createMode` tinyint NOT NULL DEFAULT '0',
  `spell` int unsigned NOT NULL DEFAULT '0',
  `note` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`raceMask`,`classMask`,`createMode`,`spell`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

insert into playercreateinfo_cast_spell (raceMask, classMask, spell, note) values
(1, 4, 79597, 'Human - Hunter - Young Wolf'),
(2, 4, 79598, 'Orc - Hunter - Young Boar'),
(4, 4, 79593, 'Dwarf - Hunter - Young Bear'),
(8, 4, 79602, 'Night Elf - Hunter - Young Cat'),
(16, 4, 79600, 'Undead - Hunter - Young Widow'),
(32, 4, 79603, 'Tauren - Hunter - Young Tallstrider'),
(128, 4, 79599, 'Troll - Hunter - Young Raptor'),
(256, 4, 79595, 'Goblin - Hunter - Young Crab'),
(512, 4, 79594, 'Blood Elf - Hunter - Young Dragonhawk'),
(1024, 4, 79601, 'Draenei - Hunter - Young Moth'),
(2097152, 4, 79596, 'Worgen - Hunter - Young Mastiff'),
(16, 925, 73523, 'Undead - Rigor Mortis'),
(8388608, 0, 107027, 'Pandaren - See Quest Invis 20'),
(8388608, 1, 108059, 'Pandaren - Warrior - Remove weapon'),
(8388608, 4, 108061, 'Pandaren - Hunter - Remove weapon'),
(8388608, 8, 108058, 'Pandaren - Rogue - Remove weapon'),
(8388608, 16, 108057, 'Pandaren - Priest - Remove weapon'),
(8388608, 64, 108056, 'Pandaren - Shaman - Remove weapon'),
(8388608, 128, 108055, 'Pandaren - Mage - Remove weapon'),
(8388608, 512, 108060, 'Pandaren - Monk - Remove weapon'),
(64, 4, 153724, 'Gnome - Hunter - Mechanical Bunny'),
(64, 1, 80653, 'Warrior - Gnome - Irradiated Aura'),
(64, 8, 80653, 'Rogue - Gnome - Irradiated Aura'),
(64, 16, 80653, 'Priest - Gnome - Irradiated Aura'),
(64, 128, 80653, 'Mage - Gnome - Irradiated Aura'),
(64, 256, 80653, 'Warlock - Gnome - Irradiated Aura'),
(64, 512, 80653, 'Monk - Gnome - Irradiated Aura'),
(64, 4, 80653, 'Hunter - Gnome - Irradiated Aura'),
(128, 2015, 71033, 'Troll - Calm of the Novice');
