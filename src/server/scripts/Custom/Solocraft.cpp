
/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <map>
#include "Config.h"
#include "DatabaseEnv.h"
#include "ScriptMgr.h"
#include "Unit.h"
#include "ObjectAccessor.h"
#include "LFGMgr.h"
#include "Player.h"
#include "Pet.h"
#include "Map.h"
#include "Group.h"
#include "InstanceScript.h"
#include "Chat.h"
#include "Log.h"
#include "PlayerDefines.h"
#include <math.h>
#include <unordered_map>

enum SolocraftTrinityStrings
{
    SOLOCRAFT_TRINITYSTRING_ACTIVE                       = 40000,    // |cff4CFF00SoloCraft system|r active.
    SOLOCRAFT_TRINITYSTRING_STATUS                       = 40001,    // |cffFF0000[SoloCraft]|r |cffFF8000 %s entered %s - Difficulty Offset: %0.2f. Spellpower Bonus: %i. Class Balance Weight: %i. XP Gain: |cffFF0000%s XP Balancing:%s |cff4CFF00%s
    SOLOCRAFT_TRINITYSTRING_ERR_LEVEL_TOO_HIGH           = 40002,    // |cff4CFF00[SoloCraft]|r |cffFF0000 %s entered %s - |cffFF0000You have not been buffed.|r |cffFF8000Your level is higher than the max level (%i) threshold for this dungeon.
    SOLOCRAFT_TRINITYSTRING_ERR_GROUP_ALREADY_BUFFED     = 40003,    // |cffFF0000[SoloCraft]|r |cffFF8000 %s entered %s - |cffFF0000BE ADVISED - You have been debuffed by offset: %0.2f with a Class Balance Weight: %i. |cffFF8000A group member already inside has the dungeon's full buff offset. No Spellpower buff will be applied to spell casters. ALL group members must exit the dungeon and re-enter to receive a balanced offset.
    SOLOCRAFT_TRINITYSTRING_CLEAR_BUFFS                  = 40004,    // |cffFF0000[SoloCraft]|r |cffFF8000 %s exited to %s - Reverting Difficulty Offset: %0.2f. Spellpower Bonus Removed: %i
    SOLOCRAFT_TRINITYSTRING_ENABLED                      = 40005,    // Enabled
    SOLOCRAFT_TRINITYSTRING_DISABLED                     = 40006,    // Disabled
};

class SolocraftConfig
{
    public:

        SolocraftConfig()
        {
            loadConfig();
        }

        static SolocraftConfig &getInstance() {
            static SolocraftConfig instance;
            return instance;
        }

        void loadConfig()
        {
            SoloCraftEnable = sConfigMgr->GetBoolDefault("Solocraft.Enable", 0);
            SoloCraftAnnounceModule = sConfigMgr->GetBoolDefault("Solocraft.Announce", 1);
            SoloCraftDebuffEnable = sConfigMgr->GetBoolDefault("SoloCraft.Debuff.Enable", 1);
            SoloCraftSpellMult = sConfigMgr->GetFloatDefault("SoloCraft.Spellpower.Mult", 2.5);
            SoloCraftStatsMult = sConfigMgr->GetFloatDefault("SoloCraft.Stats.Mult", 50.0);

            classes =
            {
                {1, sConfigMgr->GetIntDefault("SoloCraft.Warrior", 100) },
                {2, sConfigMgr->GetIntDefault("SoloCraft.Paladin", 100) },
                {3, sConfigMgr->GetIntDefault("SoloCraft.Hunter", 100) },
                {4, sConfigMgr->GetIntDefault("SoloCraft.Rogue", 100) },
                {5, sConfigMgr->GetIntDefault("SoloCraft.Priest", 100) },
                {6, sConfigMgr->GetIntDefault("SoloCraft.Death.Knight", 100) },
                {7, sConfigMgr->GetIntDefault("SoloCraft.Shaman", 100) },
                {8, sConfigMgr->GetIntDefault("SoloCraft.Mage", 100) },
                {9, sConfigMgr->GetIntDefault("SoloCraft.Warlock", 100) },
                {10, sConfigMgr->GetIntDefault("SoloCraft.Monk", 100) },
                {11, sConfigMgr->GetIntDefault("SoloCraft.Druid", 100) },
                {12, sConfigMgr->GetIntDefault("SoloCraft.Demon.Hunter", 100) },
            };

            SolocraftXPEnabled = sConfigMgr->GetBoolDefault("Solocraft.XP.Enabled", 1);
            SolocraftXPBalancingEnabled = sConfigMgr->GetBoolDefault("Solocraft.XP.Balancing.Enabled", 1);
            SolocraftLevelDiff = sConfigMgr->GetIntDefault("Solocraft.Max.Level.Diff", 10);
            SolocraftDungeonLevel = sConfigMgr->GetIntDefault("Solocraft.Dungeon.Level", 90);

            // Dungeon difficulty
            D5 = sConfigMgr->GetFloatDefault("Solocraft.Dungeon", 5.0);
            D10 = sConfigMgr->GetFloatDefault("Solocraft.Heroic", 10.0);
            D25 = sConfigMgr->GetFloatDefault("Solocraft.Raid25", 25.0);
            D40 = sConfigMgr->GetFloatDefault("Solocraft.Raid40", 40.0);

            diff_Multiplier =
            {
                /// VANILLA
                {34, sConfigMgr->GetFloatDefault("Solocraft.Stockades", 5.0) },
                {43, sConfigMgr->GetFloatDefault("Solocraft.WailingCaverns", 5.0) },
                {47, sConfigMgr->GetFloatDefault("Solocraft.RazorfenKraul", 5.0) },
                {48, sConfigMgr->GetFloatDefault("Solocraft.BlackfathomDeeps", 5.0) },
                {70, sConfigMgr->GetFloatDefault("Solocraft.Uldaman", 5.0) },
                {90, sConfigMgr->GetFloatDefault("Solocraft.Gnomeregan", 5.0) },
                {109, sConfigMgr->GetFloatDefault("Solocraft.SunkenTemple", 5.0) },
                {129, sConfigMgr->GetFloatDefault("Solocraft.RazorfenDowns", 5.0) },
                {209, sConfigMgr->GetFloatDefault("Solocraft.ZulFarrak", 5.0) },
                {229, sConfigMgr->GetFloatDefault("Solocraft.BlackRockSpire", 10.0) },
                {230, sConfigMgr->GetFloatDefault("Solocraft.BlackrockDepths", 5.0) },
                {249, sConfigMgr->GetFloatDefault("Solocraft.OnyxiaLair", 40.0) },
                {329, sConfigMgr->GetFloatDefault("Solocraft.Stratholme", 5.0) },
                {349, sConfigMgr->GetFloatDefault("Solocraft.Mauradon", 5.0) },
                {389, sConfigMgr->GetFloatDefault("Solocraft.RagefireChasm", 5.0) },
                {409, sConfigMgr->GetFloatDefault("Solocraft.MoltenCore", 40.0) },
                {429, sConfigMgr->GetFloatDefault("Solocraft.DireMaul", 5.0) },
                {469, sConfigMgr->GetFloatDefault("Solocraft.BlackwingLair", 40.0) },
                {509, sConfigMgr->GetFloatDefault("Solocraft.RuinsOfAhnQiraj", 20.0) },
                {531, sConfigMgr->GetFloatDefault("Solocraft.TempleOfAhnQiraj", 40.0) },
                /// BURNING CRUSADE
                {269, sConfigMgr->GetFloatDefault("Solocraft.TheBlackMorass", 5.0) },
                {532, sConfigMgr->GetFloatDefault("Solocraft.Karazahn", 10.0) },
                {534, sConfigMgr->GetFloatDefault("Solocraft.TheBattleForMountHyjal", 25.0) },
                {540, sConfigMgr->GetFloatDefault("Solocraft.TheShatteredHalls", 5.0) },
                {542, sConfigMgr->GetFloatDefault("Solocraft.TheBloodFurnace", 5.0) },
                {543, sConfigMgr->GetFloatDefault("Solocraft.HellfireRampart", 5.0) },
                {544, sConfigMgr->GetFloatDefault("Solocraft.MagtheridonsLair", 25.0) },
                {545, sConfigMgr->GetFloatDefault("Solocraft.TheSteamVault", 5.0) },
                {546, sConfigMgr->GetFloatDefault("Solocraft.TheUnderbog", 5.0) },
                {547, sConfigMgr->GetFloatDefault("Solocraft.TheSlavePens", 5.0) },
                {548, sConfigMgr->GetFloatDefault("Solocraft.SerpentshrineCavern", 25.0) },
                {550, sConfigMgr->GetFloatDefault("Solocraft.TheEye", 25.0) },
                {552, sConfigMgr->GetFloatDefault("Solocraft.TheArcatraz", 5.0) },
                {553, sConfigMgr->GetFloatDefault("Solocraft.TheBotanica", 5.0) },
                {554, sConfigMgr->GetFloatDefault("Solocraft.TheMechanar", 5.0) },
                {555, sConfigMgr->GetFloatDefault("Solocraft.ShadowLabyrinth", 5.0) },
                {556, sConfigMgr->GetFloatDefault("Solocraft.SethekkHalls", 5.0) },
                {557, sConfigMgr->GetFloatDefault("Solocraft.ManaTombs", 5.0) },
                {558, sConfigMgr->GetFloatDefault("Solocraft.AuchenaiCrypts", 5.0) },
                {560, sConfigMgr->GetFloatDefault("Solocraft.OldHillsbradFoothills", 5.0) },
                {564, sConfigMgr->GetFloatDefault("Solocraft.BlackTemple", 25.0) },
                {565, sConfigMgr->GetFloatDefault("Solocraft.GruulsLair", 25.0) },
                {580, sConfigMgr->GetFloatDefault("Solocraft.SunwellPlateau", 25.0) },
                {585, sConfigMgr->GetFloatDefault("Solocraft.MagistersTerrace", 5.0) },
                /// WRATH OF THE LICH KING
                {533, sConfigMgr->GetFloatDefault("Solocraft.Naxxramas", 10.0) },
                {574, sConfigMgr->GetFloatDefault("Solocraft.UtgardeKeep", 5.0) },
                {575, sConfigMgr->GetFloatDefault("Solocraft.UtgardePinnacle", 5.0) },
                {578, sConfigMgr->GetFloatDefault("Solocraft.Oculus", 5.0) },
                {595, sConfigMgr->GetFloatDefault("Solocraft.TheCullingOfStratholme", 5.0) },
                {599, sConfigMgr->GetFloatDefault("Solocraft.HallsOfStone", 5.0) },
                {600, sConfigMgr->GetFloatDefault("Solocraft.DrakTharonKeep", 5.0) },
                {601, sConfigMgr->GetFloatDefault("Solocraft.AzjolNerub", 5.0) },
                {602, sConfigMgr->GetFloatDefault("Solocraft.HallsOfLighting", 5.0) },
                {603, sConfigMgr->GetFloatDefault("Solocraft.Ulduar", 10.0) },
                {604, sConfigMgr->GetFloatDefault("Solocraft.GunDrak", 5.0) },
                {608, sConfigMgr->GetFloatDefault("Solocraft.VioletHold", 5.0) },
                {615, sConfigMgr->GetFloatDefault("Solocraft.TheObsidianSanctum", 10.0) },
                {616, sConfigMgr->GetFloatDefault("Solocraft.TheEyeOfEternity", 10.0) },
                {619, sConfigMgr->GetFloatDefault("Solocraft.AhnkahetTheOldKingdom", 5.0) },
                {631, sConfigMgr->GetFloatDefault("Solocraft.IcecrownCitadel", 10.0) },
                {632, sConfigMgr->GetFloatDefault("Solocraft.TheForgeOfSouls", 5.0) },
                {649, sConfigMgr->GetFloatDefault("Solocraft.TrialOfTheCrusader", 10.0) },
                {650, sConfigMgr->GetFloatDefault("Solocraft.TrialOfTheChampion", 5.0) },
                {658, sConfigMgr->GetFloatDefault("Solocraft.PitOfSaron", 5.0) },
                {668, sConfigMgr->GetFloatDefault("Solocraft.HallsOfReflection", 5.0) },
                {724, sConfigMgr->GetFloatDefault("Solocraft.TheRubySanctum", 10.0) },
                /// CATACLYSM
                {33, sConfigMgr->GetFloatDefault("Solocraft.ShadowfangKeep", 5.0) }, // ShadowfangKeep
                {36, sConfigMgr->GetFloatDefault("Solocraft.DeadMines", 5.0) }, // DeadMines
                {645, sConfigMgr->GetFloatDefault("Solocraft.BlackrockCaverns", 5.0) }, // BlackrockCaverns
                {643, sConfigMgr->GetFloatDefault("Solocraft.ThroneOfTheTides", 5.0) }, // Трон Приливов
                {657, sConfigMgr->GetFloatDefault("Solocraft.TheVortexPinnacle", 5.0) }, // Вершина Смерча
                {725, sConfigMgr->GetFloatDefault("Solocraft.TheStonecore", 5.0) }, // Каменные Недра
                {755, sConfigMgr->GetFloatDefault("Solocraft.LostCityOfTheTol'vir", 5.0) }, // Затерянный город Тол'вир
                {644, sConfigMgr->GetFloatDefault("Solocraft.HallsOfOrigination", 5.0) }, // Чертоги Созидания
                {670, sConfigMgr->GetFloatDefault("Solocraft.GrimBatol", 5.0) }, // Грим Батол
                {669, sConfigMgr->GetFloatDefault("Solocraft.BlackwingDescent", 10.0) }, // Твердыня Крыла Тьмы
                {671, sConfigMgr->GetFloatDefault("Solocraft.TheBastionOfTwilight", 10.0) }, // Сумеречный бастион
                {754, sConfigMgr->GetFloatDefault("Solocraft.ThroneOfTheFourWinds", 10.0) }, // Трон Четырех Ветров
                {757, sConfigMgr->GetFloatDefault("Solocraft.BaradinHold", 10.0) }, // Крепость Барадин
                {720, sConfigMgr->GetFloatDefault("Solocraft.Firelands", 10.0) }, // Огненные Просторы
                {967, sConfigMgr->GetFloatDefault("Solocraft.DragonSoul", 10.0) }, // Душа Дракона
                {859, sConfigMgr->GetFloatDefault("Solocraft.Zul'gurub", 5.0) }, // Зул'Гуруб
                {568, sConfigMgr->GetFloatDefault("Solocraft.ZulAman", 5.0) }, // Зул'Аман
                {576, sConfigMgr->GetFloatDefault("Solocraft.Nexus", 5.0) }, // Нексус
                /// MISTS OF PANDARIA
                {959, sConfigMgr->GetFloatDefault("Solocraft.ShadoPanMonastery", 5.0) }, // Монастырь Шадо-Пан
                {1007, sConfigMgr->GetFloatDefault("Solocraft.Scholomance", 5.0) }, // Некроситет
                {1004, sConfigMgr->GetFloatDefault("Solocraft.ScarletMonastery", 5.0) }, // Монастырь Алого ордена
                {994, sConfigMgr->GetFloatDefault("Solocraft.Mogu'shanPalace", 5.0) }, // Дворец Могу'шан
                {1008, sConfigMgr->GetFloatDefault("Solocraft.Mogu'shanVaults", 10.0) }, // Подземелья Могу'шан
                {1136, sConfigMgr->GetFloatDefault("Solocraft.SiegeOfOrgrimmar", 10.0) }, // Осада Оргриммара
                {1098, sConfigMgr->GetFloatDefault("Solocraft.ThroneOfThunder", 10.0) }, // Престол Гроз
                {1009, sConfigMgr->GetFloatDefault("Solocraft.HeartOfFear", 10.0) }, // Сердце Страха
                {996, sConfigMgr->GetFloatDefault("Solocraft.TerraceOfEndlessSpring", 10.0) }, // Терраса Вечной Весны
                {1001, sConfigMgr->GetFloatDefault("Solocraft.ScarletHalls", 5.0) }, // Залы Алого ордена
                {962, sConfigMgr->GetFloatDefault("Solocraft.GateOfTheSettingSun", 5.0) }, // Врата Заходящего Солнца
                {1011, sConfigMgr->GetFloatDefault("Solocraft.SiegeOfNiuzaoTemple", 5.0) }, // Осада храма Нюцзао
                {960, sConfigMgr->GetFloatDefault("Solocraft.TempleOfTheJadeSerpent", 5.0) }, // Храм Нефритовой Змеи
                {961, sConfigMgr->GetFloatDefault("Solocraft.StormstoutBrewery", 5.0) }, // Хмелеварня Буйных Портеров
                /// WARLORDS OF DRAENOR
                { 821, sConfigMgr->GetFloatDefault("Solocraft.IronDocks", 5.0) }, // WoD
                { 820, sConfigMgr->GetFloatDefault("Solocraft.Auchindoun", 5.0) }, // WoD
                { 779, sConfigMgr->GetFloatDefault("Solocraft.Skyreach", 5.0) }, // WoD
                { 987, sConfigMgr->GetFloatDefault("Solocraft.HellfireCitadel", 25.0) }, // WoD
                { 895, sConfigMgr->GetFloatDefault("Solocraft.Highmaul", 25.0) }, // WoD
                { 822, sConfigMgr->GetFloatDefault("Solocraft.GrimrailDepot", 5.0) }, // WoD
                { 898, sConfigMgr->GetFloatDefault("Solocraft.BlackrockFoundry", 25.0) }, // WoD
                { 783, sConfigMgr->GetFloatDefault("Solocraft.ShadowmoonBurialGrounds", 5.0) }, // WoD
                { 824, sConfigMgr->GetFloatDefault("Solocraft.TheEverbloom", 5.0) }, // 
                ///LEGION
                { 1201, sConfigMgr->GetFloatDefault("Solocraft.DarkheartThicket", 5.0) }, // 
                { 1206, sConfigMgr->GetFloatDefault("Solocraft.Neltharion'sLair", 5.0) }, // 
                { 1208, sConfigMgr->GetFloatDefault("Solocraft.VioletHoldLegion", 5.0) }, // 
                { 1174, sConfigMgr->GetFloatDefault("Solocraft.EyeofAzshara", 5.0) }, // 
                { 330, sConfigMgr->GetFloatDefault("Solocraft.UpperBlackrockSpire", 5.0) }, // 
                { 1640, sConfigMgr->GetFloatDefault("Solocraft.AntorustheBurningThrone", 25.0) }, // 
                { 1525, sConfigMgr->GetFloatDefault("Solocraft.TombOfSargeras", 25.0) }, // 
                { 1437, sConfigMgr->GetFloatDefault("Solocraft.TrialOfValor", 25.0) }, // 
                { 1351, sConfigMgr->GetFloatDefault("Solocraft.TheNighthold", 25.0) }, // 
                { 1348, sConfigMgr->GetFloatDefault("Solocraft.TheEmeraldNightmare", 25.0) }, // 
                { 1204, sConfigMgr->GetFloatDefault("Solocraft.BlackRookHold", 5.0) }, // 
                { 1043, sConfigMgr->GetFloatDefault("Solocraft.VaultOftheWardens", 5.0) }, // 
                { 1191, sConfigMgr->GetFloatDefault("Solocraft.MawOfSouls", 5.0) }, // 
                { 1193, sConfigMgr->GetFloatDefault("Solocraft.HallsOfValor", 5.0) }, //
            };
            // diff_Multiplier_Heroics
            diff_Multiplier_Heroics =
            {
                /// BURNING CRUSADE
                {269, sConfigMgr->GetFloatDefault("Solocraft.TheBlackMorassH", 5.0) },
                {540, sConfigMgr->GetFloatDefault("Solocraft.TheShatteredHallsH", 5.0) },
                {542, sConfigMgr->GetFloatDefault("Solocraft.TheBloodFurnaceH", 5.0) },
                {543, sConfigMgr->GetFloatDefault("Solocraft.HellfireRampartH", 5.0) },
                {545, sConfigMgr->GetFloatDefault("Solocraft.TheSteamVaultH", 5.0) },
                {546, sConfigMgr->GetFloatDefault("Solocraft.TheUnderbogH", 5.0) },
                {547, sConfigMgr->GetFloatDefault("Solocraft.TheSlavePensH", 5.0) },
                {552, sConfigMgr->GetFloatDefault("Solocraft.TheArcatrazH", 5.0) },
                {553, sConfigMgr->GetFloatDefault("Solocraft.TheBotanicaH", 5.0) },
                {554, sConfigMgr->GetFloatDefault("Solocraft.TheMechanarH", 5.0) },
                {555, sConfigMgr->GetFloatDefault("Solocraft.ShadowLabyrinthH", 5.0) },
                {556, sConfigMgr->GetFloatDefault("Solocraft.SethekkHallsH", 5.0) },
                {557, sConfigMgr->GetFloatDefault("Solocraft.ManaTombsH", 5.0) },
                {558, sConfigMgr->GetFloatDefault("Solocraft.AuchenaiCryptsH", 5.0) },
                {560, sConfigMgr->GetFloatDefault("Solocraft.OldHillsbradFoothillsH", 5.0) },
                {585, sConfigMgr->GetFloatDefault("Solocraft.MagistersTerraceH", 5.0) },
                /// WRATH OF THE LICH KING
                {533, sConfigMgr->GetFloatDefault("Solocraft.NaxxramasH", 25.0) },
                {574, sConfigMgr->GetFloatDefault("Solocraft.UtgardeKeepH", 5.0) },
                {575, sConfigMgr->GetFloatDefault("Solocraft.UtgardePinnacleH", 5.0) },
                {578, sConfigMgr->GetFloatDefault("Solocraft.OculusH", 5.0) },
                {595, sConfigMgr->GetFloatDefault("Solocraft.TheCullingOfStratholmeH", 5.0) },
                {599, sConfigMgr->GetFloatDefault("Solocraft.HallsOfStoneH", 5.0) },
                {600, sConfigMgr->GetFloatDefault("Solocraft.DrakTharonKeepH", 5.0) },
                {601, sConfigMgr->GetFloatDefault("Solocraft.AzjolNerubH", 5.0) },
                {602, sConfigMgr->GetFloatDefault("Solocraft.HallsOfLightingH", 5.0) },
                {603, sConfigMgr->GetFloatDefault("Solocraft.UlduarH", 25.0) },
                {604, sConfigMgr->GetFloatDefault("Solocraft.GunDrakH", 5.0) },
                {608, sConfigMgr->GetFloatDefault("Solocraft.VioletHoldH", 5.0) },
                {615, sConfigMgr->GetFloatDefault("Solocraft.TheObsidianSanctumH", 25.0) },
                {616, sConfigMgr->GetFloatDefault("Solocraft.TheEyeOfEternityH", 25.0) },
                {619, sConfigMgr->GetFloatDefault("Solocraft.AhnkahetTheOldKingdomH", 5.0) },
                {631, sConfigMgr->GetFloatDefault("Solocraft.IcecrownCitadelH", 25.0) },
                {632, sConfigMgr->GetFloatDefault("Solocraft.TheForgeOfSoulsH", 5.0) },
                {649, sConfigMgr->GetFloatDefault("Solocraft.TrialOfTheCrusaderH", 25.0) },
                {650, sConfigMgr->GetFloatDefault("Solocraft.TrialOfTheChampionH", 5.0) },
                {658, sConfigMgr->GetFloatDefault("Solocraft.PitOfSaronH", 5.0) },
                {668, sConfigMgr->GetFloatDefault("Solocraft.HallsOfReflectionH", 5.0) },
                {724, sConfigMgr->GetFloatDefault("Solocraft.TheRubySanctumH", 25.0) },
                /// CATACLYSM
                {33, sConfigMgr->GetFloatDefault("Solocraft.ShadowfangKeepH", 5.0) },
                {36, sConfigMgr->GetFloatDefault("Solocraft.DeadMinesH", 5.0) },
                {645, sConfigMgr->GetFloatDefault("Solocraft.BlackrockCavernsH", 5.0) },
                {643, sConfigMgr->GetFloatDefault("Solocraft.ThroneOfTheTidesH", 5.0) },
                {657, sConfigMgr->GetFloatDefault("Solocraft.TheVortexPinnacleH", 5.0) },
                {725, sConfigMgr->GetFloatDefault("Solocraft.TheStonecoreH", 5.0) },
                {755, sConfigMgr->GetFloatDefault("Solocraft.LostCityOfTheTol'virH", 5.0) },
                {644, sConfigMgr->GetFloatDefault("Solocraft.HallsOfOriginationH", 5.0) },
                {670, sConfigMgr->GetFloatDefault("Solocraft.GrimBatolH", 5.0) },
                {669, sConfigMgr->GetFloatDefault("Solocraft.BlackwingDescentH", 25.0) },
                {671, sConfigMgr->GetFloatDefault("Solocraft.TheBastionOfTwilightH", 25.0) },
                {754, sConfigMgr->GetFloatDefault("Solocraft.ThroneOfTheFourWindsH", 25.0) },
                {757, sConfigMgr->GetFloatDefault("Solocraft.BaradinHoldH", 25.0) },
                {720, sConfigMgr->GetFloatDefault("Solocraft.FirelandsH", 25.0) },
                {967, sConfigMgr->GetFloatDefault("Solocraft.DragonSoulH", 25.0) },
                {938, sConfigMgr->GetFloatDefault("Solocraft.EndTimeH", 5.0) },
                {939, sConfigMgr->GetFloatDefault("Solocraft.WellOfEternityH", 5.0) },
                {940, sConfigMgr->GetFloatDefault("Solocraft.HourOfTwilightH", 5.0) },
                {859, sConfigMgr->GetFloatDefault("Solocraft.Zul'gurubH", 5.0) },
                {568, sConfigMgr->GetFloatDefault("Solocraft.ZulAmanH", 5.0) },
                {576, sConfigMgr->GetFloatDefault("Solocraft.NexusH", 5.0) },
                /// MISTS OF PANDARIA
                {959, sConfigMgr->GetFloatDefault("Solocraft.ShadoPanMonasteryH", 5.0) },
                {1007, sConfigMgr->GetFloatDefault("Solocraft.ScholomanceH", 5.0) },
                {1004, sConfigMgr->GetFloatDefault("Solocraft.ScarletMonasteryH", 5.0) },
                {994, sConfigMgr->GetFloatDefault("Solocraft.Mogu'shanPalaceH", 5.0) },
                {1008, sConfigMgr->GetFloatDefault("Solocraft.Mogu'shanVaultsH", 25.0) },
                {1136, sConfigMgr->GetFloatDefault("Solocraft.SiegeOfOrgrimmarH", 25.0) },
                {1098, sConfigMgr->GetFloatDefault("Solocraft.ThroneOfThunderH", 25.0) },
                {1009, sConfigMgr->GetFloatDefault("Solocraft.HeartOfFearH", 25.0) },
                {996, sConfigMgr->GetFloatDefault("Solocraft.TerraceOfEndlessSpringH", 25.0) },
                {1001, sConfigMgr->GetFloatDefault("Solocraft.ScarletHallsH", 5.0) },
                {962, sConfigMgr->GetFloatDefault("Solocraft.GateOfTheSettingSunH", 5.0) },
                {1011, sConfigMgr->GetFloatDefault("Solocraft.SiegeOfNiuzaoTempleH", 5.0) },
                {960, sConfigMgr->GetFloatDefault("Solocraft.TempleOfTheJadeSerpentH", 5.0) },
                {961, sConfigMgr->GetFloatDefault("Solocraft.StormstoutBreweryH", 5.0) },
                /// WARLORDS OF DRAENOR
                { 821, sConfigMgr->GetFloatDefault("Solocraft.IronDocksH", 5.0) }, // WoD
                { 820, sConfigMgr->GetFloatDefault("Solocraft.AuchindounH", 5.0) }, // WoD
                { 779, sConfigMgr->GetFloatDefault("Solocraft.SkyreachH", 5.0) }, // WoD
                { 987, sConfigMgr->GetFloatDefault("Solocraft.HellfireCitadelH", 25.0) }, // WoD
                { 895, sConfigMgr->GetFloatDefault("Solocraft.HighmaulH", 25.0) }, // WoD
                { 822, sConfigMgr->GetFloatDefault("Solocraft.GrimrailDepotH", 5.0) }, // WoD
                { 898, sConfigMgr->GetFloatDefault("Solocraft.BlackrockFoundryH", 25.0) }, // WoD
                { 783, sConfigMgr->GetFloatDefault("Solocraft.ShadowmoonBurialGroundsH", 5.0) }, // WoD
                { 824, sConfigMgr->GetFloatDefault("Solocraft.TheEverbloomH", 5.0) }, // 
                ///LEGION
                { 1201, sConfigMgr->GetFloatDefault("Solocraft.DarkheartThicketH", 5.0) }, // 
                { 1206, sConfigMgr->GetFloatDefault("Solocraft.Neltharion'sLairH", 5.0) }, // 
                { 1174, sConfigMgr->GetFloatDefault("Solocraft.EyeofAzsharaH", 5.0) }, // 
                { 330, sConfigMgr->GetFloatDefault("Solocraft.UpperBlackrockSpireH", 5.0) }, // 
                { 1208, sConfigMgr->GetFloatDefault("Solocraft.VioletHoldLegionH", 5.0) }, // 
                { 1640, sConfigMgr->GetFloatDefault("Solocraft.AntorustheBurningThroneH", 25.0) }, // 
                { 1525, sConfigMgr->GetFloatDefault("Solocraft.TombOfSargerasH", 25.0) }, // 
                { 1437, sConfigMgr->GetFloatDefault("Solocraft.TrialOfValorH", 25.0) }, // 
                { 1351, sConfigMgr->GetFloatDefault("Solocraft.TheNightholdH", 25.0) }, // 
                { 1348, sConfigMgr->GetFloatDefault("Solocraft.TheEmeraldNightmareH", 25.0) }, // 
                { 1204, sConfigMgr->GetFloatDefault("Solocraft.BlackRookHoldH", 5.0) }, // 
                { 1043, sConfigMgr->GetFloatDefault("Solocraft.VaultOftheWardensH", 5.0) }, // 
                { 1191, sConfigMgr->GetFloatDefault("Solocraft.MawOfSoulsH", 5.0) }, // 
                { 1193, sConfigMgr->GetFloatDefault("Solocraft.HallsOfValorH", 5.0) }, //                
            };

            D649H10 = sConfigMgr->GetFloatDefault("Solocraft.ArgentTournamentRaidH10", 10.0);  // Trial of the Crusader 10 Heroic
            D649H25 = sConfigMgr->GetFloatDefault("Solocraft.ArgentTournamentRaidH25", 25.0);  // Trial of the Crusader 25 Heroic

        }


    public:
        bool SoloCraftEnable = false;
        bool SoloCraftAnnounceModule = true;
        bool SoloCraftDebuffEnable = true;
        bool SolocraftXPBalancingEnabled = true;
        bool SolocraftXPEnabled = true;
        bool SolocraftNoXPFlag = false;

        float SoloCraftSpellMult = 1.0;
        float SoloCraftStatsMult = 100.0;
        float SoloCraftXPMod = 1.0;

        uint32 SolocraftLevelDiff = 1;
        uint32 SolocraftDungeonLevel = 1;

        std::unordered_map<uint32, float> diff_Multiplier;
        std::unordered_map<uint32, float> diff_Multiplier_Heroics;
        std::unordered_map<uint8, uint32> classes;

        float D5 = 1.0;
        float D10 = 1.0;
        float D25 = 1.0;
        float D40 = 1.0;
        float D649H10 = 1.0;
        float D649H25 = 1.0;
};

class solocraft_system_announce : public PlayerScript
{
    public:
        solocraft_system_announce() : PlayerScript("solocraft_system_announce")
        {
            solocraftConfig = SolocraftConfig::getInstance();
        }

        void OnLogin(Player* player) override
        {
            if (solocraftConfig.SoloCraftEnable && solocraftConfig.SoloCraftAnnounceModule)
            {
                ChatHandler(player->GetSession()).SendSysMessage(SOLOCRAFT_TRINITYSTRING_ACTIVE);
            }
        }

        void OnLogout(Player* player) override
        {
//            QueryResult result = CharacterDatabase.PQuery("SELECT `GUID` FROM `custom_solocraft_character_stats` WHERE GUID = %u", player->GetGUID().GetCounter());
//            if (result)
//            {
//                CharacterDatabase.PExecute("DELETE FROM custom_solocraft_character_stats WHERE GUID = %u", player->GetGUID().GetCounter());
//            }
        }

        void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
        {
            if (solocraftConfig.SolocraftXPBalancingEnabled)
            {
                Map* map = player->GetMap();
                if (map && map->IsDungeon())
                {
                    // Ensure that the players always get the same XP, even when entering the dungeon alone
                    auto maxPlayerCount= map->ToInstanceMap()->GetMaxPlayers();
                    auto currentPlayerCount = GetNumInGroup(player);
                    amount = uint32(amount * solocraftConfig.SoloCraftXPMod * ((float) currentPlayerCount / maxPlayerCount));
                }
            }
        }

        static int GetNumInGroup(Player* player)
        {
            int numInGroup = 1;
            Group* group = player->GetGroup();

            if (group)
            {
                Group::MemberSlotList const& groupMembers = group->GetMemberSlots();
                numInGroup = groupMembers.size();
            }
            return numInGroup;
        }

    protected:
        SolocraftConfig solocraftConfig;
};

class solocraft_system_player_instance_handler : public PlayerScript
{
public:
    solocraft_system_player_instance_handler() : PlayerScript("solocraft_system_player_instance_handler")
    {
        solocraftConfig = SolocraftConfig::getInstance();
    }

    void OnMapChanged(Player* player) override
    {
        if (solocraftConfig.SoloCraftEnable)
        {
            Map* map = player->GetMap();
            float difficulty = CalculateDifficulty(map, player);
            int dunLevel = CalculateDungeonLevel(map, player);
            int numInGroup = GetNumInGroup(player);
            uint32 classBalance = GetClassBalance(player);
            TC_LOG_DEBUG("solocraft", "solocraft player guid = %u, difficulty=%f, dunLevel=%d, numInGroup=%d, classBalance=%lu", player->GetGUID().GetCounter(), difficulty, dunLevel, numInGroup, classBalance);
            ApplyBuffs(player, map, difficulty, dunLevel, numInGroup, classBalance);
        }
    }

private:
    std::map<uint32, float> _unitDifficulty;
protected:
    SolocraftConfig solocraftConfig;
    bool noXPGainFlag = false; // if noXPGainFlag before solocraft setting

    float CalculateDifficulty(Map* map, Player* /*player*/)
    {
        if (map)
        {
            if (map->Is25ManRaid())
            {
                if (map->IsHeroic() && map->GetId() == 649)
                {
                    return solocraftConfig.D649H25;
                }
                else if (solocraftConfig.diff_Multiplier_Heroics.find(map->GetId()) == solocraftConfig.diff_Multiplier_Heroics.end())
                {
                    return solocraftConfig.D25;
                }
                else
                    return solocraftConfig.diff_Multiplier_Heroics[map->GetId()];
            }

            if (map->IsHeroic())
            {
                if (map->GetId() == 649)
                {
                    return solocraftConfig.D649H10;
                }
                else if (solocraftConfig.diff_Multiplier_Heroics.find(map->GetId()) == solocraftConfig.diff_Multiplier_Heroics.end())
                {
                    return solocraftConfig.D10;
                }
                else
                    return solocraftConfig.diff_Multiplier_Heroics[map->GetId()];
            }

            if (solocraftConfig.diff_Multiplier.find(map->GetId()) == solocraftConfig.diff_Multiplier.end())
            {
                if (map->IsDungeon())
                {
                    return solocraftConfig.D5;
                }
                else if (map->IsRaid())
                {
                    return solocraftConfig.D40;
                }
            }
            else
                return solocraftConfig.diff_Multiplier[map->GetId()];
        }
        return 0;
    }

    int CalculateDungeonLevel(Map* map, Player* player)
    {
        if (auto lfgDungeonData = sLFGMgr->GetLFGDungeon(map->GetId(), map->GetDifficultyID(), player->GetTeam()))
        {
            auto playerLevel = player->getLevel();

            if (playerLevel < lfgDungeonData->minlevel)
                return lfgDungeonData->minlevel;

            if (playerLevel > lfgDungeonData->maxlevel)
                return lfgDungeonData->maxlevel;

            return playerLevel;
        }

        return solocraftConfig.SolocraftDungeonLevel;
    }

    int GetNumInGroup(Player* player)
    {
        int numInGroup = 1;
        Group* group = player->GetGroup();

        if (group)
        {
            Group::MemberSlotList const& groupMembers = group->GetMemberSlots();
            numInGroup = groupMembers.size();
        }
        return numInGroup;
    }

    uint32 GetClassBalance(Player* player)
    {
        uint32 classBalance = 100;

        if (solocraftConfig.classes.find(player->getClass()) == solocraftConfig.classes.end())
        {
            return classBalance;
        }
        else if (solocraftConfig.classes[player->getClass()] <= 100)
        {
            return solocraftConfig.classes[player->getClass()];
        }
        else
            return classBalance;
    }

    void ApplyBuffs(Player* player, Map* map, float difficulty, int dunLevel, int numInGroup, int classBalance)
    {
        if (difficulty > 0)
        {

            int SpellPowerBonus = 0;

            if (player->HasFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN))
            {
                noXPGainFlag = true;
            }

            if (player->getLevel() <= dunLevel + solocraftConfig.SolocraftLevelDiff)
            {
                float GroupDifficulty = GetGroupDifficulty(player);

                if (GroupDifficulty >= difficulty && solocraftConfig.SoloCraftDebuffEnable)
                {
                    difficulty = (-abs(difficulty)) + ((((float)classBalance / 100) * difficulty) / numInGroup);
                    difficulty = roundf(difficulty * 100) / 100;

                    if (!player->HasFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN) && solocraftConfig.SolocraftXPBalancingEnabled)
                    {
                        player->SetFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);
                    }
                }

                //QueryResult result = CharacterDatabase.PQuery("SELECT `guid`, `Difficulty`, `GroupSize`, `SpellPower`, `Stats` FROM `custom_solocraft_character_stats` WHERE `guid` = %lu", player->GetGUID().GetCounter());

                for (int32 i = STAT_STRENGTH; i < MAX_STATS; ++i)
                {
//                    if (result)
//                    {
//                        player->HandleStatModifier(UnitMods(UNIT_MOD_STAT_START + i), TOTAL_VALUE, (*result)[1].GetFloat() * (*result)[4].GetFloat(), false);
//                    }

                    player->HandleStatModifier(UnitMods(UNIT_MOD_STAT_START + i), TOTAL_VALUE, difficulty * solocraftConfig.SoloCraftStatsMult, true);
                }

                player->SetFullHealth();
                player->CastSpell(player, 6962, true);

                if (player->getPowerType() == POWER_MANA || player->getClass() == 11)
                {
                    player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));

//                    if (result)
//                    {
//                        player->ApplySpellPowerBonus((*result)[3].GetUInt32() * (*result)[4].GetFloat(), false);
//                    }

                    if (difficulty > 0)
                    {
                        SpellPowerBonus = static_cast<int>((player->getLevel() * solocraftConfig.SoloCraftSpellMult) * difficulty);
                        player->ApplySpellPowerBonus(SpellPowerBonus, true);
                    }
                }

                if (!solocraftConfig.SolocraftXPEnabled)
                {
                    if (!player->HasFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN))
                    {
                        player->SetFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);
                    }
                }

                if (difficulty > 0)
                {

                    const char* solocraft_enabled = player->GetSession()->GetTrinityString(SOLOCRAFT_TRINITYSTRING_ENABLED);
                    const char* solocraft_disabled = player->GetSession()->GetTrinityString(SOLOCRAFT_TRINITYSTRING_DISABLED);
                    ChatHandler(player->GetSession()).PSendSysMessage(player->GetSession()->GetTrinityString(SOLOCRAFT_TRINITYSTRING_STATUS), player->GetName(), map->GetMapName(), difficulty, SpellPowerBonus, classBalance, solocraftConfig.SolocraftXPEnabled?solocraft_enabled:solocraft_disabled, solocraftConfig.SolocraftXPBalancingEnabled?solocraft_enabled:solocraft_disabled);
                    //|cffFF0000[SoloCraft]|r |cffFF8000 %s entered %s - Difficulty Offset: %0.2f. Spellpower Bonus: %i. Class Balance Weight: %i. XP Gain: |cffFF0000%s XP Balancing:%s |cff4CFF00%s

                }
                else
                {
                    ChatHandler(player->GetSession()).PSendSysMessage(player->GetSession()->GetTrinityString(SOLOCRAFT_TRINITYSTRING_ERR_GROUP_ALREADY_BUFFED), player->GetName(), map->GetMapName(), difficulty, classBalance);
                    // |cffFF0000[SoloCraft]|r |cffFF8000 %s entered %s - |cffFF0000BE ADVISED - You have been debuffed by offset: %0.2f with a Class Balance Weight: %i. |cffFF8000A group member already inside has the dungeon's full buff offset. No Spellpower buff will be applied to spell casters. ALL group members must exit the dungeon and re-enter to receive a balanced offset.
                }

                //CharacterDatabase.PExecute("REPLACE INTO `custom_solocraft_character_stats` (`guid`, `Difficulty`, `GroupSize`, `SpellPower`, `Stats`) VALUES (%lu, %f, %u, %i, %f)", player->GetGUID().GetCounter(), difficulty, numInGroup, SpellPowerBonus, solocraftConfig.SoloCraftStatsMult);
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage(player->GetSession()->GetTrinityString(SOLOCRAFT_TRINITYSTRING_ERR_LEVEL_TOO_HIGH), player->GetName(), map->GetMapName(), dunLevel + solocraftConfig.SolocraftLevelDiff);
                ClearBuffs(player, map);
            }
        }
        else
        {
            ClearBuffs(player, map);
        }
    }

    float GetGroupDifficulty(Player* player)
    {
        float GroupDifficulty = 0.0;
        Group* group = player->GetGroup();

        if (group)
        {
            Group::MemberSlotList const& groupMembers = group->GetMemberSlots();

            for (Group::member_citerator itr = groupMembers.begin(); itr != groupMembers.end(); ++itr)
            {
                if (itr->Guid != player->GetGUID())
                {
                    //QueryResult result = CharacterDatabase.PQuery("SELECT `guid`, `Difficulty`, `GroupSize` FROM `custom_solocraft_character_stats` WHERE `guid` = %lu", itr->Guid);

//                    if (result)
//                    {
//                        if ((*result)[1].GetFloat() > 0)
//                        {
//                            GroupDifficulty = GroupDifficulty + (*result)[1].GetFloat();
//                        }
//                    }
                }
            }
        }

        return GroupDifficulty;
    }

    void ClearBuffs(Player* player, Map* map)
    {
//        QueryResult result = CharacterDatabase.PQuery("SELECT `guid`, `Difficulty`, `GroupSize`, `SpellPower`, `Stats` FROM `custom_solocraft_character_stats` WHERE `guid` = %lu", player->GetGUID().GetCounter());
//
//        if (result)
//        {
//            float difficulty = (*result)[1].GetFloat();
//            int SpellPowerBonus = (*result)[3].GetUInt32();
//            float StatsMultPct = (*result)[4].GetFloat();
//
//            ChatHandler(player->GetSession()).PSendSysMessage(player->GetSession()->GetTrinityString(SOLOCRAFT_TRINITYSTRING_CLEAR_BUFFS), player->GetName().c_str(), map->GetMapName(), difficulty, SpellPowerBonus);
//
//            for (int32 i = STAT_STRENGTH; i < MAX_STATS; ++i)
//            {
//                player->HandleStatModifier(UnitMods(UNIT_MOD_STAT_START + i), TOTAL_VALUE, difficulty * StatsMultPct, false);
//            }
//
//            if (player->getPowerType() == POWER_MANA && difficulty > 0)
//            {
//                player->ApplySpellPowerBonus(SpellPowerBonus, false);
//            }
//
//            if (player->HasFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN) && !noXPGainFlag && !solocraftConfig.SolocraftNoXPFlag)
//            {
//                player->RemoveFlag(PLAYER_FIELD_PLAYER_FLAGS, PLAYER_FLAGS_NO_XP_GAIN);
//            }
//
//            CharacterDatabase.PExecute("DELETE FROM `custom_solocraft_character_stats` WHERE `guid` = %lu", player->GetGUID().GetCounter());
//        }
    }
};

void AddSC_solocraft()
{
    new solocraft_system_announce();
    new solocraft_system_player_instance_handler();
}