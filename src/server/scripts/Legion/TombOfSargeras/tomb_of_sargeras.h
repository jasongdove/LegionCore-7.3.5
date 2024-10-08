#ifndef TombOsSargeasH_
#define TombOsSargeasH_

#define DataHeader "TOS"

enum eData
{
    DATA_GOROTH                     = 0,
    DATA_HARJATAN                   = 1,
    DATA_MISTRESS_SASSZINE          = 2,

    DATA_DEMONIC_INQUISITION        = 3,
    DATA_THE_DESOLATE_HOST          = 4,
    DATA_SISTERS_OF_THEMOON         = 5,

    DATA_MAIDEN_OF_VIGILANCE        = 6,
    DATA_FALLEN_AVATAR              = 7,
    DATA_KILJAEDEN                  = 8,

    MAX_ENCOUNTER
};

enum eCreatures
{
    NPC_BREACH_IN_WINDOW            = 121605,

    NPC_KHADGAR                     = 119726,
    NPC_VELEN                       = 119728,
    NPC_ILLIDAN                     = 119729,
    NPC_MAEIV                       = 119730,
    NPC_DURGAN                      = 119777,

    NPC_EGIDA                       = 121630,
    NPC_HAMMER_1                    = 121494,
    NPC_HAMMER_2                    = 121111,
    NPC_ELUNES_1                    = 121495, 
    NPC_ELUNES_2                    = 121110,
    NPC_GOLGANETH_1                 = 121496,
    NPC_GOLGANETH_2                 = 121105,

    NPC_EGVIN                       = 119723,

    NPC_ATRIGAN_MISC                = 120996, //Not boss
    NPC_SASSZINE_NPC_OUTRO          = 121190,
    NPC_SASSZINE_MISC               = 121184,
    NPC_LUNAR_ARCHER                = 120721,
    NPC_GUARDIAN_SENTRY             = 120777,
    NPC_TORMENTED_SOUL              = 117957,
    NPC_FRAGMENT_SOUL               = 121138,

    NPC_KILDJEDAN_AVATARA           = 120867,

//! BOSSES

    //Goroth
    NPC_GOROTH                      = 115844,
    NPC_EMBER_STALKER               = 115892,
    NPC_INFERNAL_SPIKE              = 116976,
    NPC_LAVA_STALKER                = 117931, //Heroic+
    NPC_BRIMSTONE_INFERNAL          = 119950,

    //Harajatan
    NPC_HARJATAN                    = 116407,
    NPC_EGGS                        = 120545,
    NPC_ELDER                       = 121071,
    NPC_TADPOLE_1                   = 120574,
    NPC_TADPOLE_2                   = 121156,
    NPC_TADPOLE_3                   = 121155,
    NPC_EVENT_1                     = 121011,
    NPC_EVENT_2                     = 117123,

    //Mistress Sassz'ine
    NPC_SASSZINE                    = 115767,
    NPC_ABYSS_STALKER               = 115795,
    NPC_TORNADO_TRIGGER             = 118286,
    NPC_ELECTRIFYING_JELLYFISH      = 115896,
    NPC_RAZORJAW_WAVERUNNER         = 115902,
    NPC_SARUKEL_TRIGGER             = 116843,
    NPC_OSSUNET_TRIGGER             = 116881,
    NPC_PIRANHADO_TRIGGER           = 116841,
    NPC_DELICIOUS_BUFFERFISH        = 119791, //Mythic
    NPC_TIDESTONE_GOLGANNETH        = 121105, //Spawn after death boss

    //Demonic Inquisitor
    NPC_ATRIGAN                     = 116689,
    NPC_BELAK                       = 116691,

    NPC_ESSENCE_LIGHT               = 118640,
    NPC_ESSENCE_FEL                 = 118643,
    NPC_REMANENCE_LIGHT             = 119825,
    NPC_REMANENCE_FEL               = 119826,

    //Sisters of the Moon
    NPC_MOON_STALKER                = 118182,
    NPC_HUNTRESS_KASPARIAN          = 118523,
    NPC_PRIESTESS_LUNASPYRE         = 118518,
    NPC_CAPTAIN_YATHAE              = 118374,
    NPC_MOONTALON                   = 119205,
    NPC_GLAIVE_TARGET               = 119054,
    NPC_SISTERS_ACH_ADD             = 121498,

    //The Desolate Host
    NPC_SWIRLING_SOULS_TRIG         = 120988, //Event Manager
    NPC_DESOLATE_HOST               = 119072, //!Real world
    NPC_ENGINE_OF_SOULS             = 118460,
    NPC_REANIMATED_TEMPLAR          = 118715,
    NPC_REANIMATED_TEMPLAR_MIRROR   = 119938, //Mythic
    NPC_GHASTLY_BONEWARDEN          = 118728,
    NPC_GHASTLY_BONEWARDEN_MIRROR   = 119939, //Mythic
    NPC_TORMENTED_CRIES_TRIG        = 118924,
    NPC_SOUL_QUEEN_DEJAHNA          = 118462, //!Spirit world
    NPC_FALLEN_PRIESTESS            = 118729,
    NPC_FALLEN_PRIESTESS_MIRROR     = 119940, //Mythic
    NPC_SOUL_RESIDUE                = 118730,
    NPC_SOUL_RESIDUE_MIRROR         = 119941, //Mythic
    NPC_SPIRITUAL_FONT              = 118701, //!Other
    NPC_SPIRITUAL_BARRIER_TRIG      = 118727,
    NPC_TEARS_OF_ELUNE              = 121110, //Spawn After Dies Boss

    //Avatara
    NPC_FALLEN_AVATAR               = 116939,
    NPC_CORRUPTED_BLADE             = 119158,
    NPC_PILONES                     = 117279,
    NPC_AVATARA_MAIDEN              = 117264,
    NPC_BLACK_WINDS                 = 121294,
    NPC_TOUCH_OF_SARGERAS           = 120838,

    //Maiden of Vigilance
    NPC_MAIDEN_OF_VIGILANCE         = 118289,

    //Kil'jaeden <The Deceiver>
    NPC_KILJAEDEN                   = 117269,
    NPC_ARMAGEDDON_STALKER          = 120839,
    NPC_ERUPTING_REFLECTION         = 119206,
    NPC_WAILING_REFLECTION          = 119107, //Mythic
    NPC_HOPELESS_REFLECTION         = 119663, //Mythic
    NPC_SHADOWSOUL                  = 121193,
    NPC_STAGE4_ILLIDAN_STORMRAGE    = 121227,
    NPC_DEMONIC_OBELISK             = 120270,
    NPC_NETHER_RIFT                 = 120390,
    NPC_FLAMING_ORB                 = 120082, //Heroic+
};

enum eGameObjects
{
    GO_INTRODESTROY_1               = 269839,
    GO_INTRODESTROY_2               = 269838,
    GO_INTRODESTROY_3               = 269842,

    GO_GOROTH_GATES                 = 272802,
    GO_GOROTH_INFERNAL_SPIKE        = 266938, //LOS_BLOCKER

    GO_SASSZINE_DOOR                = 269976,
    GO_INQUISITION_DOOR             = 268579,
    GO_INQUISITION_DOOR_INTRO       = 268580,
    GO_SISTERS_MOON_DOOR            = 269045,

    GO_HAMMER_THRONE                = 269780,
    GO_ELUNES_THRONE                = 269779,
    GO_GOLGANETH_THRONE             = 269782,

    GO_MAIDEN_DOOR                  = 269988,
    GO_ELEVATOR                     = 268574,

    GO_AVATARA_FLOOR                = 267934,
    GO_AVATARA_DOOR                 = 269262,

    GO_DESOLATE_HOST_DOOR_1         = 268749,
    GO_DESOLATE_HOST_DOOR_2         = 269781,

    GO_KILJAEDEN_BRIDGE_1           = 271126,
    GO_KILJAEDEN_BRIDGE_2           = 271127,
    GO_KILJAEDEN_CHEST              = 271099,
};

enum eSpells
{
    SPELL_INTRO_TELEPORT            = 241303,
};

#define ToSScriptName "instance_tomb_of_sargeras"

#endif
