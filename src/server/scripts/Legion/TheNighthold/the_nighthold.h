#ifndef ThiNightholdH_
#define ThiNightholdH_

#define DataHeader "NH"

enum eData
{
    DATA_SKORPYRON          = 0,
    DATA_ANOMALY            = 1,
    DATA_TRILLIAX           = 2,

    DATA_ALURIEL            = 3,
    DATA_ETRAEUS            = 4,
    DATA_TELARN             = 5,

    DATA_KROSUS             = 6,
    DATA_TICHONDRIUS        = 7,
    DATA_ELISANDE           = 8,

    DATA_GULDAN             = 9,

    MAX_ENCOUNTER,

    DATA_SKORPYRON_PATH,
    DATA_ANOMALY_SPEED,
    DATA_ANOMALY_OVERWHELMING,
    DATA_TRILLIAX_INTRO,
    DATA_TRILLIAX_IMPRINT_DOOR,

    DATA_STAR_AUGUR_ETRAEUS_PHASE,
    DATA_STAR_AUGUR_ETRAEUS_GRAVITY_PULL_COUNTER,

    DATA_KROSUS_PLATFORM1,
    DATA_KROSUS_PLATFORM2,
    DATA_KROSUS_PLATFORM3,
    DATA_KROSUS_PLATFORM4,
    DATA_IMAGE_OF_KADGHAR,
    DATA_KROSUS_INTRO_TRASH,
    DATA_CHAOS_MAGE_BELORN,
    DATA_SUMMONER_XIV,
    DATA_FELWEAVER_PHARAMERE,

    DATA_TELARN_CALL_OF_NIGHT,
};

enum eCreatures
{
    //General
    NPC_TALYSRA                     = 110791,
    NPC_TALYSRA_ADDS                = 113608,
    NPC_TALYSRA_ADDS_1              = 113605,
    NPC_KHADGAR                     = 110792,

    //Scorpyron
    NPC_SKORPYRON                   = 102263,
    NPC_CRYSTALLINE_SCORPID         = 103217,
    NPC_VOLATILE_SCORPID            = 103224,
    NPC_ACIDMAW_SCORPID             = 103225,
    NPC_CRYSTALLINE_SHARD           = 103209,
    NPC_VOLATILE_SHARD              = 108132,
    NPC_ACIDIC_SHARD                = 108131,
    NPC_ARCANE_TETHER               = 103682,

    //Anomaly
    NPC_CHRONOMATIC_ANOMALY         = 104415,
    NPC_FRAGMENTED_TIME             = 114671,
    NPC_SURAMAR_TRIG                = 108786,
    NPC_THE_NIGHTWELL               = 104738,
    NPC_WANING_TIME_PARTICLE        = 104676,
    NPC_TEMPORAL_RIFT               = 106878,

    //Trilliax
    NPC_TRILLIAX                    = 104288,
    NPC_TRILLIAX_COPY_CLEANER       = 108303, //Mythic
    NPC_TRILLIAX_COPY_MANIAC        = 108144, //Mythic
    NPC_SLUDGERAX                   = 112255,
    NPC_PUTRID_SLUDGE               = 112251,
    NPC_SUCCULENT_FEAST             = 104561,
    NPC_TOXIC_SLICE                 = 104547,
    NPC_SCRUBBER                    = 104596,

    //Spellblade Aluriel
    NPC_SPELLBLADE_ALURIEL          = 104881,
    NPC_SPELLBLADE_ALURIEL_IMAG     = 107980,
    NPC_MARK_OF_FROST               = 107694, //Trigger
    NPC_ICY_ENCHANTMENT             = 107237,
    NPC_SEARING_BRAND               = 107584, //Trigger
    NPC_FIERY_ENCHANTMENT           = 107285,
    NPC_ARCANE_ORB                  = 107510,
    NPC_ARCANE_ENCHANTMENT          = 107287,
    NPC_ICE_SHARDS                  = 107592, //Heroic+
    NPC_FROST_VISUAL_1              = 108545, //Trigger. Heroic+
    NPC_FROST_VISUAL_2              = 108546, //Trigger. Heroic+
    NPC_FROST_VISUAL_3              = 108547, //Trigger. Heroic+
    NPC_FROST_VISUAL_4              = 108548, //Trigger. Heroic+
    NPC_FEL_SOUL                    = 115905, //Mythic

    //Krosus
    NPC_KROSUS                      = 101002,
    NPC_IMGAGE_OF_KADGNAR           = 110677,
    NPC_CHAOS_MAGE_BELORN           = 111225,
    NPC_SUMMONER_XIV                = 111226,
    NPC_FELWEAVER_PHARAMERE         = 111227,

    //High Botanist Tel'arn
    NPC_TELARN                      = 104528,
    NPC_SOLARIST_TELARN             = 109038,
    NPC_ARCANIST_TELARN             = 109040,
    NPC_NATURALIST_TELARN           = 109041,
    NPC_CONTROLLED_CHAOS_STALKER    = 109792,
    NPC_PARASITIC_LASHER            = 109075,
    NPC_SOLAR_COLLAPSE_STALKER      = 109583,
    NPC_TOXIC_SPORE                 = 110125,
    NPC_PLASMA_SPHERE               = 109804,
    NPC_CHAOS_SPHERE                = 111993,
    NPC_BOTANIST_HEALTH_CONTROLLER  = 109164,
    NPC_IMAGE_ARCANIST_TELARN       = 110341,
    NPC_DUSKWATCH_WEAVER            = 112973,
    NPC_TELARN_GENERIC_TRIGGER      = 68553,  //SLG Generic MoP (Large AOI)

    //Star Augur Etraeus
    NPC_STAR_AUGUR_ETRAEUS          = 103758,
    NPC_CORONAL_EJECTION            = 103790,
    NPC_ICE_CRYSTAL                 = 109003,
    NPC_EYE_OF_THE_VOID             = 109082,
    NPC_EYE_OF_THE_VOID_PASSENGER   = 109088,
    NPC_REMNANT_OF_THE_VOID         = 109151,

    //Tichondrius
    NPC_TICHONDRIUS                 = 103685,
    NPC_TAINTED_BLOOD               = 108934,
    NPC_FEL_SPIRE                   = 108625,
    NPC_COMBAT_STALKER              = 104271,
    NPC_CARRION_NIGHTMARE           = 108739,
    NPC_PHANTASMAL_BLOODFANG        = 104326,
    NPC_FELSWORN_SPELLGUARD         = 108591,
    NPC_SIGHTLESS_WATCHER           = 108593,

    //Elisande <Grand Magistrix>
    NPC_ELISANDE                    = 106643,
    NPC_ELISANDE_COPY_1             = 105297, //Unk
    NPC_ELISANDE_COPY_2             = 106330, //Unk
    NPC_ECHO_OF_ELISANDE_RING       = 105364, //ARCANETIC_RING
    NPC_ECHO_OF_ELISANDE_SINGULAR   = 105622, //SPANNING_SINGULARITY
    NPC_ECHO_OF_ELISANDE_BEAM       = 105624, //DELPHURIC_BEAM
    NPC_ECHO_OF_ELISANDE_ORB_TRIG   = 105958, //EPOCHERIC_ORB - Trigger
    NPC_ECHO_OF_ELISANDE_ORB_VIS    = 106680, //EPOCHERIC_ORB - Echo Visual
    NPC_ARCANETIC_RING              = 105315,
    NPC_ARCANETIC_RING_2            = 105367,
    NPC_ARCANETIC_RING_3            = 105370,
    NPC_RECURSIVE_ELEMENTAL         = 105299,
    NPC_EXPEDIENT_ELEMENTAL         = 105301,
    NPC_EPOCHERIC_ORB_TRIGGER       = 107754,

    //Guldan
    NPC_GULDAN                      = 104154,
    NPC_HELLFIRE                    = 104396,
    NPC_BOUNDS_OF_FEL               = 104252,   
    NPC_EYE_OF_GULDAN               = 105630,
    NPC_EMPOWERED_EYE_OF_GULDAN     = 106545,
    NPC_VISUAL_SELECT               = 114440,
    NPC_KURAZMAL                    = 104537,
    NPC_VETRIZ                      = 104536,
    NPC_DZORIKS                     = 104534,
    NPC_KHADGAR_PHASE_3             = 106522,
    NPC_KHADGAR_FIGURE              = 116153,
    NPC_KHADGAR_FIGURE_1            = 116156,
    NPC_CRYSTALL_OF_ILLIDAN         = 114437,
    NPC_BLACK_SOUL                  = 110688,
    NPC_AZAGRIM                     = 105295,
    NPC_BELTERIS                    = 107232,
    NPC_DALVENGIR                   = 107233,
    
    NPC_DEMON_WITHIN                = 111022, // mini boss
    NPC_SHADOW_DEMON                = 111047,
    NPC_SHADOW_SOUL                 = 107229,
    NPC_PART_OF_AZZINOTH            = 111070,
    NPC_DEMONIC_ESSENCE             = 111222,
    NPC_NIGHT_SPHERE                = 111054,
    NPC_DEMON_VEHICLE               = 111251,
};

enum eGameObjects
{
    GO_SCORPYRON_DOOR_1             = 252105,
    GO_SCORPYRON_DOOR_2             = 252103,
    GO_ANOMALY_DOOR_1               = 252349,
    GO_ANOMALY_DOOR_2               = 252348,
    GO_TRILLIAX_DOOR_1              = 250243,
    GO_TRILLIAX_DOOR_2              = 251397,
    GO_TRILLIAX_DOOR_3              = 250241,
    GO_TRILLIAX_DOOR_4              = 250242,
    GO_STAR_AUGUR_ETRAEUS_DOOR      = 248932, // 252435

    GO_ANOMALY_PRE                  = 251519,
    
    GO_ALURIEL_DOOR_PORTAL          = 254240,

    GO_KROSUS_PLATFORM1             = 247972,
    GO_KROSUS_PLATFORM2             = 247971,
    GO_KROSUS_PLATFORM3             = 247973,
    GO_KROSUS_PLATFORM4             = 247970,
    GO_KROSUS_CHEST                 = 248513,

    GO_BOTANIST_LEFT_DOOR           = 251833,
    GO_BOTANIST_RIGHT_DOOR          = 251832,
    
    GO_EYE_OF_AMANTUL               = 252318,
    GO_ROOM                         = 253462,
    
    GO_STATUE_1                     = 252319,
    GO_STATUE_2                     = 251988,
    GO_STATUE_3                     = 252320,
    GO_STATUE_4                     = 252321,

    //Tichondrius
    GO_TICHONDRIUS_DOOR_1           = 253178,
    GO_TICHONDRIUS_DOOR_2           = 251687,
    GO_TICHONDRIUS_DOOR_3           = 253924,
    GO_TICHONDRIUS_DOOR_4           = 253923,
    GO_TICHONDRIUS_DOOR_5           = 251686,

    //Elisande
    GO_ELISANDE_DOOR_1              = 251612,
    GO_ELISANDE_DOOR_2              = 252315,
    GO_ELISANDE_DOOR_3              = 252316,

    //Guldan
    GO_GULDAN_CHEST                 = 266483,
};

enum eAction // actions move for talysra
{
    ACTION_MOVE_FIRST_POINT     = 0,
    ACTION_MOVE_FIRST_BOSS,
    ACTION_MOVE_AFTER_FIRST_BOSS,
    ACTION_OPEN_DOOR_SECOND,
    ACTION_MOVE_AFTER_SECOND,
    ACTION_MOVE_AFTER_THIRD,
    ACTION_MOVE_TO_FOURTH
};

#define NightholdScriptName "instance_the_nightnold"

#endif
