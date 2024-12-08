/*
 * Copyright (C) 2011 TrintiyCore <http://www.trinitycore.org/>
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

#ifndef TRINITY_DB2STORES_H
#define TRINITY_DB2STORES_H

#include "DB2Store.h"
#include "DB2Structure.h"
#include "SharedDefines.h"
#include "Hash.h"

#include <boost/regex_fwd.hpp>

TC_GAME_API extern DB2Storage<AchievementEntry>                         sAchievementStore;
TC_GAME_API extern DB2Storage<AdventureMapPOIEntry>                     sAdventureMapPOIStore;
TC_GAME_API extern DB2Storage<AdventureJournalEntry>                    sAdventureJournalStore;
TC_GAME_API extern DB2Storage<AnimKitEntry>                             sAnimKitStore;
TC_GAME_API extern DB2Storage<AreaTableEntry>                           sAreaTableStore;
TC_GAME_API extern DB2Storage<AreaTriggerEntry>                         sAreaTriggerStore;
TC_GAME_API extern DB2Storage<ArmorLocationEntry>                       sArmorLocationStore;
TC_GAME_API extern DB2Storage<ArtifactAppearanceEntry>                  sArtifactAppearanceStore;
TC_GAME_API extern DB2Storage<ArtifactAppearanceSetEntry>               sArtifactAppearanceSetStore;
TC_GAME_API extern DB2Storage<ArtifactCategoryEntry>                    sArtifactCategoryStore;
TC_GAME_API extern DB2Storage<ArtifactEntry>                            sArtifactStore;
TC_GAME_API extern DB2Storage<ArtifactPowerEntry>                       sArtifactPowerStore;
TC_GAME_API extern DB2Storage<ArtifactPowerLinkEntry>                   sArtifactPowerLinkStore;
TC_GAME_API extern DB2Storage<ArtifactPowerPickerEntry>                 sArtifactPowerPickerStore;
TC_GAME_API extern DB2Storage<ArtifactPowerRankEntry>                   sArtifactPowerRankStore;
TC_GAME_API extern DB2Storage<ArtifactQuestXPEntry>                     sArtifactQuestXPStore;
TC_GAME_API extern DB2Storage<ArtifactUnlockEntry>                      sArtifactUnlockStore;
TC_GAME_API extern DB2Storage<AuctionHouseEntry>                        sAuctionHouseStore;
TC_GAME_API extern DB2Storage<BankBagSlotPricesEntry>                   sBankBagSlotPricesStore;
TC_GAME_API extern DB2Storage<BannedAddonsEntry>                        sBannedAddOnsStore;
TC_GAME_API extern DB2Storage<BarberShopStyleEntry>                     sBarberShopStyleStore;
TC_GAME_API extern DB2Storage<BattlemasterListEntry>                    sBattlemasterListStore;
TC_GAME_API extern DB2Storage<BattlePetAbilityEffectEntry>              sBattlePetAbilityEffectStore;
TC_GAME_API extern DB2Storage<BattlePetAbilityEntry>                    sBattlePetAbilityStore;
TC_GAME_API extern DB2Storage<BattlePetAbilityStateEntry>               sBattlePetAbilityStateStore;
TC_GAME_API extern DB2Storage<BattlePetAbilityTurnEntry>                sBattlePetAbilityTurnStore;
TC_GAME_API extern DB2Storage<BattlePetBreedQualityEntry>               sBattlePetBreedQualityStore;
TC_GAME_API extern DB2Storage<BattlePetBreedStateEntry>                 sBattlePetBreedStateStore;
TC_GAME_API extern DB2Storage<BattlePetEffectPropertiesEntry>           sBattlePetEffectPropertiesStore;
TC_GAME_API extern DB2Storage<BattlePetSpeciesEntry>                    sBattlePetSpeciesStore;
TC_GAME_API extern DB2Storage<BattlePetSpeciesStateEntry>               sBattlePetSpeciesStateStore;
TC_GAME_API extern DB2Storage<BattlePetSpeciesXAbilityEntry>            sBattlePetSpeciesXAbilityStore;
TC_GAME_API extern DB2Storage<BattlePetStateEntry>                      sBattlePetStateStore;
TC_GAME_API extern DB2Storage<BroadcastTextEntry>                       sBroadcastTextStore;
TC_GAME_API extern DB2Storage<CharShipmentContainerEntry>               sCharShipmentContainerStore;
TC_GAME_API extern DB2Storage<CharShipmentEntry>                        sCharShipmentStore;
TC_GAME_API extern DB2Storage<CharStartOutfitEntry>                     sCharStartOutfitStore;
TC_GAME_API extern DB2Storage<CharTitlesEntry>                          sCharTitlesStore;
TC_GAME_API extern DB2Storage<ChatChannelsEntry>                        sChatChannelsStore;
TC_GAME_API extern DB2Storage<ChrClassesEntry>                          sChrClassesStore;
TC_GAME_API extern DB2Storage<ChrClassesXPowerTypesEntry>               sChrClassesXPowerTypesStore;
TC_GAME_API extern DB2Storage<ChrRacesEntry>                            sChrRacesStore;
TC_GAME_API extern DB2Storage<ChrSpecializationEntry>                   sChrSpecializationStore;
TC_GAME_API extern DB2Storage<ConversationLineEntry>                    sConversationLineStore;
TC_GAME_API extern DB2Storage<CreatureDisplayInfoEntry>                 sCreatureDisplayInfoStore;
TC_GAME_API extern DB2Storage<CreatureDisplayInfoExtraEntry>            sCreatureDisplayInfoExtraStore;
TC_GAME_API extern DB2Storage<CreatureFamilyEntry>                      sCreatureFamilyStore;
TC_GAME_API extern DB2Storage<CreatureModelDataEntry>                   sCreatureModelDataStore;
TC_GAME_API extern DB2Storage<CreatureTypeEntry>                        sCreatureTypeStore;
TC_GAME_API extern DB2Storage<CriteriaEntry>                            sCriteriaStore;
TC_GAME_API extern DB2Storage<CriteriaTreeEntry>                        sCriteriaTreeStore;
TC_GAME_API extern DB2Storage<CurrencyTypesEntry>                       sCurrencyTypesStore;
TC_GAME_API extern DB2Storage<CurveEntry>                               sCurveStore;
TC_GAME_API extern DB2Storage<CurvePointEntry>                          sCurvePointStore;
TC_GAME_API extern DB2Storage<DestructibleModelDataEntry>               sDestructibleModelDataStore;
TC_GAME_API extern DB2Storage<DifficultyEntry>                          sDifficultyStore;
TC_GAME_API extern DB2Storage<DungeonEncounterEntry>                    sDungeonEncounterStore;
TC_GAME_API extern DB2Storage<DurabilityCostsEntry>                     sDurabilityCostsStore;
TC_GAME_API extern DB2Storage<DurabilityQualityEntry>                   sDurabilityQualityStore;
TC_GAME_API extern DB2Storage<EmotesEntry>                              sEmotesStore;
TC_GAME_API extern DB2Storage<EmotesTextEntry>                          sEmotesTextStore;
TC_GAME_API extern DB2Storage<FactionEntry>                             sFactionStore;
TC_GAME_API extern DB2Storage<FactionTemplateEntry>                     sFactionTemplateStore;
TC_GAME_API extern DB2Storage<GameObjectDisplayInfoEntry>               sGameObjectDisplayInfoStore;
TC_GAME_API extern DB2Storage<GameObjectsEntry>                         sGameObjectsStore;
TC_GAME_API extern DB2Storage<GarrAbilityEffectEntry>                   sGarrAbilityEffectStore;
TC_GAME_API extern DB2Storage<GarrAbilityEntry>                         sGarrAbilityStore;
TC_GAME_API extern DB2Storage<GarrBuildingEntry>                        sGarrBuildingStore;
TC_GAME_API extern DB2Storage<GarrBuildingPlotInstEntry>                sGarrBuildingPlotInstStore;
TC_GAME_API extern DB2Storage<GarrClassSpecEntry>                       sGarrClassSpecStore;
TC_GAME_API extern DB2Storage<GarrEncounterEntry>                       sGarrEncounterStore;
TC_GAME_API extern DB2Storage<GarrEncounterSetXEncounterEntry>          sGarrEncounterSetXEncounterStore;
TC_GAME_API extern DB2Storage<GarrEncounterXMechanicEntry>              sGarrEncounterXMechanicStore;
TC_GAME_API extern DB2Storage<GarrFollowerEntry>                        sGarrFollowerStore;
TC_GAME_API extern DB2Storage<GarrFollowerTypeEntry>                    sGarrFollowerTypeStore;
TC_GAME_API extern DB2Storage<GarrFollowerLevelXPEntry>                 sGarrFollowerLevelXPStore;
TC_GAME_API extern DB2Storage<GarrFollowerQualityEntry>                 sGarrFollowerQualityStore;
TC_GAME_API extern DB2Storage<GarrFollowerXAbilityEntry>                sGarrFollowerXAbilityStore;
TC_GAME_API extern DB2Storage<GarrItemLevelUpgradeDataEntry>            sGarrItemLevelUpgradeDataStore;
TC_GAME_API extern DB2Storage<GarrMechanicEntry>                        sGarrMechanicStore;
TC_GAME_API extern DB2Storage<GarrMechanicSetXMechanicEntry>            sGarrMechanicSetXMechanicStore;
TC_GAME_API extern DB2Storage<GarrMechanicTypeEntry>                    sGarrMechanicTypeStore;
TC_GAME_API extern DB2Storage<GarrMissionEntry>                         sGarrMissionStore;
TC_GAME_API extern DB2Storage<GarrMissionXEncounterEntry>               sGarrMissionXEncounterStore;
TC_GAME_API extern DB2Storage<GarrPlotBuildingEntry>                    sGarrPlotBuildingStore;
TC_GAME_API extern DB2Storage<GarrPlotEntry>                            sGarrPlotStore;
TC_GAME_API extern DB2Storage<GarrPlotInstanceEntry>                    sGarrPlotInstanceStore;
TC_GAME_API extern DB2Storage<GarrSiteLevelEntry>                       sGarrSiteLevelStore;
TC_GAME_API extern DB2Storage<GarrSiteLevelPlotInstEntry>               sGarrSiteLevelPlotInstStore;
TC_GAME_API extern DB2Storage<GarrTalentEntry>                          sGarrTalentStore;
TC_GAME_API extern DB2Storage<GarrTalentTreeEntry>                      sGarrTalentTreeStore;
TC_GAME_API extern DB2Storage<GemPropertiesEntry>                       sGemPropertiesStore;
TC_GAME_API extern DB2Storage<GlyphPropertiesEntry>                     sGlyphPropertiesStore;
TC_GAME_API extern DB2Storage<GroupFinderActivityEntry>                 sGroupFinderActivityStore;
TC_GAME_API extern DB2Storage<GroupFinderActivityGrpEntry>              sGroupFinderActivityGrpStore;
TC_GAME_API extern DB2Storage<GroupFinderCategoryEntry>                 sGroupFinderCategoryStore;
TC_GAME_API extern DB2Storage<GuildPerkSpellsEntry>                     sGuildPerkSpellsStore;
TC_GAME_API extern DB2Storage<HeirloomEntry>                            sHeirloomStore;
TC_GAME_API extern DB2Storage<HolidayNamesEntry>                        sHolidayNamesStore;
TC_GAME_API extern DB2Storage<HolidaysEntry>                            sHolidaysStore;
TC_GAME_API extern DB2Storage<ImportPriceArmorEntry>                    sImportPriceArmorStore;
TC_GAME_API extern DB2Storage<ImportPriceQualityEntry>                  sImportPriceQualityStore;
TC_GAME_API extern DB2Storage<ImportPriceShieldEntry>                   sImportPriceShieldStore;
TC_GAME_API extern DB2Storage<ImportPriceWeaponEntry>                   sImportPriceWeaponStore;
TC_GAME_API extern DB2Storage<ItemArmorQualityEntry>                    sItemArmorQualityStore;
TC_GAME_API extern DB2Storage<ItemArmorShieldEntry>                     sItemArmorShieldStore;
TC_GAME_API extern DB2Storage<ItemArmorTotalEntry>                      sItemArmorTotalStore;
TC_GAME_API extern DB2Storage<ItemChildEquipmentEntry>                  sItemChildEquipmentStore;
TC_GAME_API extern DB2Storage<ItemCurrencyCostEntry>                    sItemCurrencyCostStore;
TC_GAME_API extern DB2Storage<ItemDamageAmmoEntry>                      sItemDamageAmmoStore;
TC_GAME_API extern DB2Storage<ItemDamageOneHandCasterEntry>             sItemDamageOneHandCasterStore;
TC_GAME_API extern DB2Storage<ItemDamageOneHandEntry>                   sItemDamageOneHandStore;
TC_GAME_API extern DB2Storage<ItemDamageTwoHandCasterEntry>             sItemDamageTwoHandCasterStore;
TC_GAME_API extern DB2Storage<ItemDamageTwoHandEntry>                   sItemDamageTwoHandStore;
TC_GAME_API extern DB2Storage<ItemDisenchantLootEntry>                  sItemDisenchantLootStore;
TC_GAME_API extern DB2Storage<ItemEffectEntry>                          sItemEffectStore;
TC_GAME_API extern DB2Storage<ItemEntry>                                sItemStore;
TC_GAME_API extern DB2Storage<ItemExtendedCostEntry>                    sItemExtendedCostStore;
TC_GAME_API extern DB2Storage<ItemLimitCategoryEntry>                   sItemLimitCategoryStore;
TC_GAME_API extern DB2Storage<ItemModifiedAppearanceEntry>              sItemModifiedAppearanceStore;
TC_GAME_API extern DB2Storage<ItemPriceBaseEntry>                       sItemPriceBaseStore;
TC_GAME_API extern DB2Storage<ItemRandomPropertiesEntry>                sItemRandomPropertiesStore;
TC_GAME_API extern DB2Storage<ItemRandomSuffixEntry>                    sItemRandomSuffixStore;
TC_GAME_API extern DB2Storage<ItemSetEntry>                             sItemSetStore;
TC_GAME_API extern DB2Storage<ItemSparseEntry>                          sItemSparseStore;
TC_GAME_API extern DB2Storage<ItemSpecEntry>                            sItemSpecStore;
TC_GAME_API extern DB2Storage<ItemSpecOverrideEntry>                    sItemSpecOverrideStore;
TC_GAME_API extern DB2Storage<ItemUpgradeEntry>                         sItemUpgradeStore;
TC_GAME_API extern DB2Storage<JournalEncounterCreatureEntry>            sJournalEncounterCreatureStore;
TC_GAME_API extern DB2Storage<JournalEncounterEntry>                    sJournalEncounterStore;
TC_GAME_API extern DB2Storage<JournalEncounterItemEntry>                sJournalEncounterItemStore;
TC_GAME_API extern DB2Storage<JournalInstanceEntry>                     sJournalInstanceStore;
TC_GAME_API extern DB2Storage<KeychainEntry>                            sKeyChainStore;
TC_GAME_API extern DB2Storage<LFGDungeonsEntry>                         sLfgDungeonsStore;
TC_GAME_API extern DB2Storage<LiquidTypeEntry>                          sLiquidTypeStore;
TC_GAME_API extern DB2Storage<LockEntry>                                sLockStore;
TC_GAME_API extern DB2Storage<MailTemplateEntry>                        sMailTemplateStore;
TC_GAME_API extern DB2Storage<ManagedWorldStateBuffEntry>               sManagedWorldStateBuffStore;
TC_GAME_API extern DB2Storage<ManagedWorldStateEntry>                   sManagedWorldStateStore;
TC_GAME_API extern DB2Storage<ManagedWorldStateInputEntry>              sManagedWorldStateInputStore;
TC_GAME_API extern DB2Storage<MapChallengeModeEntry>                    sMapChallengeModeStore;
TC_GAME_API extern DB2Storage<MapEntry>                                 sMapStore;
TC_GAME_API extern DB2Storage<ModifierTreeEntry>                        sModifierTreeStore;
TC_GAME_API extern DB2Storage<MountCapabilityEntry>                     sMountCapabilityStore;
TC_GAME_API extern DB2Storage<MountEntry>                               sMountStore;
TC_GAME_API extern DB2Storage<MovieEntry>                               sMovieStore;
TC_GAME_API extern DB2Storage<OverrideSpellDataEntry>                   sOverrideSpellDataStore;
TC_GAME_API extern DB2Storage<ParagonReputationEntry>                   sParagonReputationStore;
TC_GAME_API extern DB2Storage<PhaseEntry>                               sPhaseStore;
TC_GAME_API extern DB2Storage<PlayerConditionEntry>                     sPlayerConditionStore;
TC_GAME_API extern DB2Storage<PowerDisplayEntry>                        sPowerDisplayStore;
TC_GAME_API extern DB2Storage<PowerTypeEntry>                           sPowerTypeStore;
TC_GAME_API extern DB2Storage<PVPItemEntry>                             sPvpItemStore;
TC_GAME_API extern DB2Storage<PvpRewardEntry>                           sPvpRewardStore;
TC_GAME_API extern DB2Storage<PvpScalingEffectEntry>                    sPvpScalingEffectStore;
TC_GAME_API extern DB2Storage<PvpScalingEffectTypeEntry>                sPvpScalingEffectTypeStore;
TC_GAME_API extern DB2Storage<PvpTalentEntry>                           sPvpTalentStore;
TC_GAME_API extern DB2Storage<QuestFactionRewardEntry>                  sQuestFactionRewardStore;
TC_GAME_API extern DB2Storage<QuestLineEntry>                           sQuestLineStore;
TC_GAME_API extern DB2Storage<QuestLineXQuestEntry>                     sQuestLineXQuestStore;
TC_GAME_API extern DB2Storage<QuestMoneyRewardEntry>                    sQuestMoneyRewardStore;
TC_GAME_API extern DB2Storage<QuestObjectiveEntry>                      sQuestObjectiveStore;
TC_GAME_API extern DB2Storage<QuestSortEntry>                           sQuestSortStore;
TC_GAME_API extern DB2Storage<QuestV2CliTaskEntry>                      sQuestV2CliTaskStore;
TC_GAME_API extern DB2Storage<QuestV2Entry>                             sQuestV2Store;
TC_GAME_API extern DB2Storage<QuestXPEntry>                             sQuestXPStore;
TC_GAME_API extern DB2Storage<RandPropPointsEntry>                      sRandPropPointsStore;
TC_GAME_API extern DB2Storage<RelicTalentEntry>                         sRelicTalentStore;
TC_GAME_API extern DB2Storage<ResearchBranchEntry>                      sResearchBranchStore;
TC_GAME_API extern DB2Storage<ResearchProjectEntry>                     sResearchProjectStore;
TC_GAME_API extern DB2Storage<RewardPackEntry>                          sRewardPackStore;
TC_GAME_API extern DB2Storage<RewardPackXCurrencyTypeEntry>             sRewardPackXCurrencyTypeStore;
TC_GAME_API extern DB2Storage<RewardPackXItemEntry>                     sRewardPackXItemStore;
TC_GAME_API extern DB2Storage<RulesetItemUpgradeEntry>                  sRulesetItemUpgradeStore;
TC_GAME_API extern DB2Storage<SandboxScalingEntry>                      sSandboxScalingStore;
TC_GAME_API extern DB2Storage<ScalingStatDistributionEntry>             sScalingStatDistributionStore;
TC_GAME_API extern DB2Storage<ScenarioEntry>                            sScenarioStore;
TC_GAME_API extern DB2Storage<ScenarioStepEntry>                        sScenarioStepStore;
TC_GAME_API extern DB2Storage<SkillLineAbilityEntry>                    sSkillLineAbilityStore;
TC_GAME_API extern DB2Storage<SkillLineEntry>                           sSkillLineStore;
TC_GAME_API extern DB2Storage<SkillRaceClassInfoEntry>                  sSkillRaceClassInfoStore;
TC_GAME_API extern DB2Storage<SpecializationSpellsEntry>                sSpecializationSpellsStore;
TC_GAME_API extern DB2Storage<SpellAuraOptionsEntry>                    sSpellAuraOptionsStore;
TC_GAME_API extern DB2Storage<SpellAuraRestrictionsEntry>               sSpellAuraRestrictionsStore;
TC_GAME_API extern DB2Storage<SpellCastingRequirementsEntry>            sSpellCastingRequirementsStore;
TC_GAME_API extern DB2Storage<SpellCastTimesEntry>                      sSpellCastTimesStore;
TC_GAME_API extern DB2Storage<SpellCategoriesEntry>                     sSpellCategoriesStore;
TC_GAME_API extern DB2Storage<SpellCategoryEntry>                       sSpellCategoryStore;
TC_GAME_API extern DB2Storage<SpellClassOptionsEntry>                   sSpellClassOptionsStore;
TC_GAME_API extern DB2Storage<SpellCooldownsEntry>                      sSpellCooldownsStore;
TC_GAME_API extern DB2Storage<SpellDurationEntry>                       sSpellDurationStore;
TC_GAME_API extern DB2Storage<SpellEntry>                               sSpellStore;
TC_GAME_API extern DB2Storage<SpellEquippedItemsEntry>                  sSpellEquippedItemsStore;
TC_GAME_API extern DB2Storage<SpellFocusObjectEntry>                    sSpellFocusObjectStore;
TC_GAME_API extern DB2Storage<SpellInterruptsEntry>                     sSpellInterruptsStore;
TC_GAME_API extern DB2Storage<SpellItemEnchantmentConditionEntry>       sSpellItemEnchantmentConditionStore;
TC_GAME_API extern DB2Storage<SpellItemEnchantmentEntry>                sSpellItemEnchantmentStore;
TC_GAME_API extern DB2Storage<SpellLearnSpellEntry>                     sSpellLearnSpellStore;
TC_GAME_API extern DB2Storage<SpellLevelsEntry>                         sSpellLevelsStore;
TC_GAME_API extern DB2Storage<SpellMiscEntry>                           sSpellMiscStore;
TC_GAME_API extern DB2Storage<SpellPowerEntry>                          sSpellPowerStore;
TC_GAME_API extern DB2Storage<SpellProcsPerMinuteEntry>                 sSpellProcsPerMinuteStore;
TC_GAME_API extern DB2Storage<SpellProcsPerMinuteModEntry>              sSpellProcsPerMinuteModStore;
TC_GAME_API extern DB2Storage<SpellRadiusEntry>                         sSpellRadiusStore;
TC_GAME_API extern DB2Storage<SpellRangeEntry>                          sSpellRangeStore;
TC_GAME_API extern DB2Storage<SpellReagentsCurrencyEntry>               sSpellReagentsCurrencyStore;
TC_GAME_API extern DB2Storage<SpellReagentsEntry>                       sSpellReagentsStore;
TC_GAME_API extern DB2Storage<SpellScalingEntry>                        sSpellScalingStore;
TC_GAME_API extern DB2Storage<SpellShapeshiftEntry>                     sSpellShapeshiftStore;
TC_GAME_API extern DB2Storage<SpellShapeshiftFormEntry>                 sSpellShapeshiftFormStore;
TC_GAME_API extern DB2Storage<SpellTargetRestrictionsEntry>             sSpellTargetRestrictionsStore;
TC_GAME_API extern DB2Storage<SpellTotemsEntry>                         sSpellTotemsStore;
TC_GAME_API extern DB2Storage<SpellVisualEntry>                         sSpellVisualStore;
TC_GAME_API extern DB2Storage<SpellXSpellVisualEntry>                   sSpellXSpellVisualStore;
TC_GAME_API extern DB2Storage<SummonPropertiesEntry>                    sSummonPropertiesStore;
TC_GAME_API extern DB2Storage<TalentEntry>                              sTalentStore;
TC_GAME_API extern DB2Storage<TaxiNodesEntry>                           sTaxiNodesStore;
TC_GAME_API extern DB2Storage<TaxiPathEntry>                            sTaxiPathStore;
TC_GAME_API extern DB2Storage<TransmogHolidayEntry>                     sTransmogHolidayStore;
TC_GAME_API extern DB2Storage<TransmogSetEntry>                         sTransmogSetStore;
TC_GAME_API extern DB2Storage<TransmogSetGroupEntry>                    sTransmogSetGroupStore;
TC_GAME_API extern DB2Storage<TransmogSetItemEntry>                     sTransmogSetItemStore;
TC_GAME_API extern DB2Storage<TransportAnimationEntry>                  sTransportAnimationStore;
TC_GAME_API extern DB2Storage<TransportRotationEntry>                   sTransportRotationStore;
TC_GAME_API extern DB2Storage<UnitPowerBarEntry>                        sUnitPowerBarStore;
TC_GAME_API extern DB2Storage<VehicleEntry>                             sVehicleStore;
TC_GAME_API extern DB2Storage<VehicleSeatEntry>                         sVehicleSeatStore;
TC_GAME_API extern DB2Storage<VignetteEntry>                            sVignetteStore;
TC_GAME_API extern DB2Storage<WorldEffectEntry>                         sWorldEffectStore;
TC_GAME_API extern DB2Storage<WorldMapAreaEntry>                        sWorldMapAreaStore;
TC_GAME_API extern DB2Storage<WorldMapOverlayEntry>                     sWorldMapOverlayStore;
TC_GAME_API extern DB2Storage<WorldSafeLocsEntry>                       sWorldSafeLocsStore;
TC_GAME_API extern DB2Storage<WorldStateExpressionEntry>                sWorldStateExpressionStore;
TC_GAME_API extern DB2Storage<WorldStateUIEntry>                        sWorldStateUIStore;
TC_GAME_API extern DB2Storage<FriendshipRepReactionEntry>               sFriendshipRepReactionStore;
TC_GAME_API extern DB2Storage<FriendshipReputationEntry>                sFriendshipReputationStore;
TC_GAME_API extern DB2Storage<GameObjectArtKitEntry>                    sGameObjectArtKitStore;
TC_GAME_API extern DB2Storage<GuildColorBackgroundEntry>                sGuildColorBackgroundStore;
TC_GAME_API extern DB2Storage<GuildColorBorderEntry>                    sGuildColorBorderStore;
TC_GAME_API extern DB2Storage<GuildColorEmblemEntry>                    sGuildColorEmblemStore;

extern TaxiMask                                             sTaxiNodesMask;
extern std::vector<uint8>                                   sTaxiNodesMaskV;
extern TaxiMask                                             sOldContinentsNodesMask;
extern TaxiMask                                             sHordeTaxiNodesMask;
extern TaxiMask                                             sAllianceTaxiNodesMask;
extern TaxiPathSetBySource                                  sTaxiPathSetBySource;
extern TaxiPathNodesByPath                                  sTaxiPathNodesByPath;

struct ResearchPOIPoint
{
    ResearchPOIPoint();
    ResearchPOIPoint(int32 _x, int32 _y);

    int32 x;
    int32 y;
};

struct DigSitePosition
{
    DigSitePosition();
    DigSitePosition(float _x, float _y);

    float x;
    float y;
};

typedef std::vector<ResearchPOIPoint> ResearchPOIPointVector;
typedef std::vector<DigSitePosition> DigSitePositionVector;

struct ResearchSiteData
{
    ResearchSiteData();

    ResearchSiteEntry const* entry;
    uint32 find_id; // is a GO entry
    uint16 zone;
    uint16 branch_id;
    uint8 level;
    ResearchPOIPointVector points;
    DigSitePositionVector digSites;
};

struct SpellEffect
{
    SpellEffect();
    SpellEffectEntry const* effects[MAX_SPELL_EFFECTS];
};

struct WMOAreaTableTripple
{
    WMOAreaTableTripple(int32 r, int32 a, int32 g);

    bool operator <(const WMOAreaTableTripple& b) const;

    // ordered by entropy; that way memcmp will have a minimal medium runtime
    int32 groupId;
    int32 rootId;
    int32 adtId;
};

static uint32 legionPvpItem[8][2]
{
    // Season 0
    { 0, 0 },
    // Season 1
    { 13226, 13227 },
    // Season 2
    { 13287, 13288 },
    // Season 3
    { 13295, 13296 },
    // Season 4
    { 13297, 13298 },
    // Season 5
    { 13299, 13300 },
    // Season 6 not need
    { 13311, 13313 },
    // Season 7 not need
    { 13312, 13314 },
};

template<typename T>
class DB2HotfixGenerator;

#define DEFINE_DB2_SET_COMPARATOR(structure) \
    struct structure ## Comparator \
    { \
        bool operator()(structure const* left, structure const* right) const { return Compare(left, right); } \
        static bool Compare(structure const* left, structure const* right); \
    };

#define PET_SPEC_OVERRIDE_CLASS_INDEX MAX_CLASSES

class TC_GAME_API DB2Manager
{
    template<typename T>
    friend class DB2HotfixGenerator;

    uint32 _maxHotfixId = 0;

public:
    void InsertNewHotfix(uint32 tableHash, uint32 recordId);

    DEFINE_DB2_SET_COMPARATOR(MountTypeXCapabilityEntry)

    typedef std::vector<ItemBonusEntry const*> ItemBonusList;
    typedef std::unordered_map<uint32, std::unordered_map<uint32, MapDifficultyEntry const*>> MapDifficultyContainer;
    typedef std::set<MountTypeXCapabilityEntry const*, MountTypeXCapabilityEntryComparator> MountTypeXCapabilitySet;
    typedef std::vector<MountXDisplayEntry const*> MountXDisplayContainer;
    typedef std::map<uint32 /*word length*/, std::vector<std::string>> LanguageWordsContainer;
    typedef std::set<uint32> PetFamilySpellsSet;
    typedef std::unordered_map<uint32, PetFamilySpellsSet > PetFamilySpellsContainer;
    typedef std::vector<uint32> SimpleFactionsList;
    typedef std::map<uint32, SimpleFactionsList> FactionTeamContainer;
    typedef std::set<GarrAbilityEffectEntry const* /*effect*/> GarrEffectContainer;
    typedef std::unordered_map<uint32 /*AbilityID*/, GarrEffectContainer> GarrAbilityEffectContainer;
    typedef std::multimap<uint32 /*ContainerID*/, CharShipmentEntry const*> ShipmentConteinerMap;
    typedef std::pair<ShipmentConteinerMap::const_iterator, ShipmentConteinerMap::const_iterator> ShipmentConteinerMapBounds;
    typedef std::map<uint16/*optionIdx*/, GarrTalentEntry const*> GarrTalentOptionMap;
    typedef std::map<uint16/*lineIdx*/, GarrTalentOptionMap> GarrTalentLineMap;
    typedef std::map<uint32/*class*/, GarrTalentLineMap> GarrTalentClassMap;
    typedef std::vector<ItemSetSpellEntry const*> ItemSetSpells;
    typedef std::unordered_map<uint32, ItemSetSpells> ItemSetSpellsContainer;
    typedef std::set<ResearchProjectEntry const*> ResearchProjectContainer;
    typedef std::map<uint32 /*site_id*/, ResearchSiteData> ResearchSiteDataMap;
    typedef std::unordered_map<uint32 /*frame*/, TransportAnimationEntry const*> TransportAnimationEntryMap;
    typedef std::unordered_map<uint32, TransportAnimationEntryMap> TransportAnimationsByEntryContainer;
    typedef std::set<uint32> SpellCategorySet;
    typedef std::unordered_map<uint32, SpellCategorySet> SpellCategoryContainer;
    typedef std::vector<TalentEntry const*> TalentsByPositionContainer[MAX_CLASSES][MAX_TALENT_TIERS][MAX_TALENT_COLUMNS];
    typedef std::vector<GarrMissionEntry const*> GarrMissionList;
    typedef std::map<uint8/*garrType*/, GarrMissionList> GarrMissionsMap;
    typedef std::unordered_map<uint32 /*ArtifactID*/, ArtifactUnlockEntry const*> ArtifactToUnlockContainer;
    typedef std::set<uint32> XData;
    typedef std::unordered_map<uint32, XData> XContainer;
    typedef std::unordered_map<uint32 /*FactionID*/, ParagonReputationEntry const*> ParagonReputationContainer;
    typedef std::vector<std::vector<SkillLineAbilityEntry const*>> SkillLineAbilityContainer;

    static DB2Manager& Instance();

    uint32 LoadStores(std::string const& dataPath, uint32 defaultLocale);
    void InitDB2CustomStores();
    static DB2StorageBase const* GetStorage(uint32 type);
    void LoadingExtraHotfixData();

    void LoadHotfixData();
    static std::map<uint64, int32> const& GetHotfixData();

    std::vector<uint32> GetAreasForGroup(uint32 areaGroupId);
    std::vector<uint32> GetGroupsForArea(uint32 areaId);
    static bool IsInArea(uint32 objectAreaId, uint32 areaId);
    std::list<uint32> GetGameObjectsList();
    uint32 GetRulesetItemUpgrade(uint32 itemId) const;
    float GetCurveValueAt(uint32 curveId, float x) const;
    uint32 GetItemDisplayId(uint32 itemId, uint32 appearanceModId) const;
    uint32 GetItemDIconFileDataId(uint32 itemId, uint32 appearanceModId = 0) const;
    std::vector<ItemLimitCategoryConditionEntry const*> const* GetItemLimitCategoryConditions(uint32 categoryId) const;
    ItemModifiedAppearanceEntry const* GetItemModifiedAppearance(uint32 itemId, uint32 appearanceModId) const;
    ItemModifiedAppearanceEntry const* GetDefaultItemModifiedAppearance(uint32 itemId) const;
    uint32 GetTransmogId(uint32 itemId, uint8 context = 0) const;
    std::vector<uint32> GetAllTransmogsByItemId(uint32 itemId) const;
    ItemBonusList const* GetItemBonusList(uint32 bonusListId) const;
    uint32 GetItemBonusListForItemLevelDelta(int16 delta) const;
    LanguageWordsContainer const* GetLanguageWordMap(uint32 landID);
    std::vector<std::string> const* GetLanguageWordsBySize(uint32 landID, uint32 size);
    std::vector<QuestPackageItemEntry const*> const* GetQuestPackageItems(uint32 questPackageID) const;
    std::vector<QuestPackageItemEntry const*> const* GetQuestPackageItemsFallback(uint32 questPackageID) const;
    MountEntry const* GetMount(uint32 spellId) const;
    static MountEntry const* GetMountById(uint32 id);
    MountTypeXCapabilitySet const* GetMountCapabilities(uint32 mountType) const;
    std::vector<uint32> GetItemBonusTree(uint32 itemId, uint32 itemBonusTreeMod, uint32& itemLevel) const;
    std::set<uint32> const* GetItemsByBonusTree(uint32 itemBonusTreeMod) const;
    std::set<ItemBonusTreeNodeEntry const*> const* GetItemBonusSet(uint32 itemBonusTree) const;
    HeirloomEntry const* GetHeirloomByItemId(uint32 itemId) const;
    bool IsToyItem(uint32 toy) const;
    uint32 GetXPForNextFollowerLevel(uint32 level, uint8 followerTypeID);
    uint32 GetXPForNextFollowerQuality(uint32 quality, uint8 followerTypeID);
    uint8 GetNextFollowerQuality(uint32 quality, uint8 followerTypeID);
    static char const* GetBroadcastTextValue(BroadcastTextEntry const* broadcastText, LocaleConstant locale = DEFAULT_LOCALE, uint8 gender = GENDER_MALE, bool forceGender = false);
    AchievementEntry const* GetsAchievementByTreeList(uint32 criteriaTree);
    std::array<std::vector<uint32>, 2> GetItemLoadOutItemsByClassID(uint32 classID, uint8 type = 0);
    std::vector<uint32> GetLowestIdItemLoadOutItemsBy(uint32 classID, uint8 type);
    std::vector<CriteriaTreeEntry const*> const* GetCriteriaTreeList(uint32 parent);
    std::vector<ModifierTreeEntry const*> const* GetModifierTreeList(uint32 parent);
    std::string GetNameGenEntry(uint8 race, uint8 gender) const;
    ResponseCodes ValidateName(std::wstring const& name, LocaleConstant locale) const;
    static uint32 GetQuestUniqueBitFlag(uint32 questID);
    ResearchSiteEntry const* GetResearchSiteEntryById(uint32 id);
    void DeterminaAlternateMapPosition(uint32 mapId, float x, float y, float z, uint32* newMapId = nullptr, DBCPosition2D* newPos = nullptr);
    static bool IsTotemCategoryCompatiableWith(uint32 itemTotemCategoryId, uint32 requiredTotemCategoryId);
    SkillRaceClassInfoEntry const* GetSkillRaceClassInfo(uint32 skill, uint8 race, uint8 class_);
    std::vector<SpecializationSpellsEntry const*> const* GetSpecializationSpells(uint32 specId);
    std::vector<SpellProcsPerMinuteModEntry const*> GetSpellProcsPerMinuteMods(uint32 spellprocsPerMinuteID) const;
    SpellTargetRestrictionsEntry const* GetSpellTargetRestrioctions(uint32 spellid, uint16 difficulty);
    uint32 GetLearnSpell(uint32 trigerSpell);
    uint32 GetSpellByTrigger(uint32 trigerSpell);
    SpellEffectEntry const* GetSpellEffectEntry(uint32 spellId, uint32 effect, uint8 difficulty);
    std::set<uint32> const* GetSpellCategory(uint32 category);
    std::vector<ItemSpecOverrideEntry const*> const* GetItemSpecOverrides(uint32 itemId) const;
    uint8 GetMaxPrestige() const;
    static PVPDifficultyEntry const* GetBattlegroundBracketByLevel(uint32 mapID, uint32 level);
    static PVPDifficultyEntry const* GetBattlegroundBracketById(uint32 mapID, uint8 id);
    ChrSpecializationEntry const* GetChrSpecializationByIndex(uint8 classID, uint32 ID);
    ChrSpecializationEntry const* GetDefaultChrSpecializationForClass(uint32 class_) const;
    PetFamilySpellsSet const* GetPetFamilySpells(uint32 family);
    uint32 GetPowerIndexByClass(Powers power, uint32 classId) const;
    AreaTableEntry const* FindAreaEntry(uint32 area);
    uint32 GetParentZoneOrSelf(uint32 zone);
    static char const* GetPetName(uint32 petfamily, LocaleConstant localeConstant);
    MapDifficultyEntry const* GetDownscaledMapDifficultyData(uint32 mapId, Difficulty &difficulty);
    MapDifficultyEntry const* GetDefaultMapDifficulty(uint32 mapID);
    DungeonEncounterEntry const* GetDungeonEncounterByDisplayID(uint32 displayID);
    MapDifficultyEntry const* GetMapDifficultyData(uint32 mapId, Difficulty difficulty);
    MapDifficultyContainer GetAllMapsDifficultyes();
    uint32 GetPlayerConditionForMapDifficulty(uint32 difficultyID);
    uint32 GetSpellMisc(uint32 spellID);
    std::vector<QuestLineXQuestEntry const*> const* GetQuestsByQuestLine(uint32 lineID) const;
    bool HasCharacterFacialHairStyle(uint8 race, uint8 gender, uint8 variationId) const;
    bool HasCharSections(uint8 race, uint8 gender, CharBaseSectionVariation variation) const;
    CharSectionsEntry const* GetCharSectionEntry(uint8 race, uint8 gender, CharBaseSectionVariation variation, uint8 variationIndex, uint8 color) const;
    SimpleFactionsList const* GetFactionTeamList(uint32 faction);
    ParagonReputationEntry const* GetFactionParagon(uint32 factionID);
    ParagonReputationEntry const* GetQuestParagon(uint32 questID);
    WMOAreaTableEntry const* GetWMOAreaTableEntryByTripple(int32 rootid, int32 adtid, int32 groupid);
    static uint32 GetLiquidFlags(uint32 liquidType);
    static uint32 GetDefaultMapLight(uint32 mapID);
    uint32 GetRequiredHonorLevelForPvpTalent(PvpTalentEntry const* talentInfo) const;
    PvpTalentEntry const* GetPvpTalentBySpellID(uint32 spellID);
    std::vector<ArtifactAppearanceSetEntry const*> const* GetArtifactAppearance(uint32 ArtifactID) const;
    std::vector<ArtifactAppearanceEntry const*> const* GetArtifactAppearanceBySet(uint32 AppearanceSetID) const;
    std::unordered_set<uint32> const* GetArtifactPowerLinks(uint32 artifactPowerId) const;
    std::vector<ArtifactPowerEntry const*> GetArtifactPowers(uint8 artifactId) const;
    ArtifactPowerRankEntry const* GetArtifactPowerRank(uint32 artifactPowerId, uint8 rank) const;
    ItemChildEquipmentEntry const* GetItemChildEquipment(uint32 itemId) const;
    bool IsChildItem(uint32 itemId) const;
    ItemClassEntry const* GetItemClassByOldEnum(uint32 itemClass) const;
    bool HasItemCurrencyCost(uint32 itemId) const;
    std::vector<TransmogSetItemEntry const*> const* GetTransmogSetItems(uint32 transmogSetId) const;
    std::vector<TransmogSetEntry const*> const* GetTransmogSetsForItemModifiedAppearance(uint32 itemModifiedAppearanceId) const;
    PowerTypeEntry const* GetPowerType(uint8 PowerTypeEnum);
    static float GetCurrencyPrecision(uint32 currencyId);
    WorldMapAreaEntry const* GetWorldMapArea(uint16 ZoneID);
    std::vector<uint16> const* GetWorldMapZone(uint16 MapID);
    GarrEffectContainer const* GetGarrEffect(uint32 AbilityID) const;
    ArtifactUnlockEntry const* GetArtifactUnlock(uint32 ArtifactID) const;
    uint32 GetVirtualMapForMapAndZone(uint32 mapid, uint32 zoneId);
    void Zone2MapCoordinates(float &x, float &y, uint32 zone);
    void Map2ZoneCoordinates(float &x, float &y, uint32 zone);
    std::vector<uint32> const* GetGlyphBindableSpells(uint32 glyphPropertiesId) const;
    std::vector<uint32> const* GetGlyphRequiredSpecs(uint32 glyphPropertiesId) const;
    static bool HasBattlePetSpeciesFlag(uint16 species, uint16 flag);
    MapChallengeModeEntry const* GetChallengeModeByMapID(uint32 mapID);
    std::vector<uint32> GetChallngeMaps();
    std::vector<double> GetChallngesWeight();
    double GetChallngeWeight(uint32 mapID);
    std::vector<PvpTalentEntry const*> GetPvpTalentByPosition(uint8 playerClass, uint8 row, uint8 column);
    uint32 GetHonorLevelRewardPack(uint16 honorLevel, uint8 prestigeLevel);
    RewardPackXItemEntry const* GetRewardPackXItem(uint32 rewardPackID);
    RewardPackXCurrencyTypeEntry const* GetRewardPackXCurrency(uint32 rewardPackID);
    MountXDisplayContainer const* GetMountDisplays(uint32 mountId) const;
    float GetPvpScalingValueByEffectType(uint32 type, uint32 specID);
    std::vector<uint32> GetLootItemsForInstanceByMapID(uint32 mapID);
    ShipmentConteinerMapBounds GetShipmentConteinerBounds(uint32 conteinerID) const;
    GarrTalentLineMap const* GetGarrTalentLine(uint16 __class);
    GarrTalentOptionMap const* GetGarrTalentOptionMap(uint16 __class, uint16 __line);
    XData const* getXMechanic(uint32 X) const;
    XData const* getXEncounter(uint32 X) const;
    std::set<uint32> GetPhasesForGroup(uint32 group) const;
    SkillLineAbilityEntry const* GetSkillBySpell(uint32 SpellID) const;
    BattlePetSpeciesEntry const* GetSpeciesBySpell(uint32 SpellID) const;
    BattlePetSpeciesEntry const* GetSpeciesByCreatureID(uint32 CreatureID) const;
    LFGDungeonsEntry const* GetLFGDungeonsByMapDIff(int16 MapID, uint8 DifficultyID) const;
    uint32 LFGRoleRequirementCondition(uint32 lfgDungeonsId, uint8 roleType);
    uint32 GetScalingByLevel(uint8 MinLevel, uint16 MaxLevel) const;

    uint32 GetHostileSpellVisualId(uint32 spellVisualId);

    ItemSetSpellsContainer _itemSetSpells;
    ResearchProjectContainer _researchProjectContainer;
    ResearchSiteDataMap _researchSiteDataMap;
    TransportAnimationsByEntryContainer _transportAnimationsByEntry;
    SpellCategoryContainer _spellCategory;
    TalentsByPositionContainer _talentByPos;
    ShipmentConteinerMap _charShipmentConteiner;
    GarrMissionsMap _garrMissionsMap;
    SkillLineAbilityContainer _skillLineAbilityContainer;
};

#define sDB2Manager DB2Manager::Instance()

#endif