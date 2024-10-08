#ifndef AntorusH_
#define AntorusH_

#define DataHeader "ATBT"

enum eData
{
    DATA_WORLDBREAKER       = 0,
    DATA_FELHOUNDS,
    DATA_ANTORAN,
    
    DATA_HASABEL,
    DATA_EONAR,
    DATA_IMONAR,
    
    DATA_KINGAROTH,
    DATA_VARIMATHRAS,
    DATA_COVEN,
    
    DATA_AGGRAMAR,
    DATA_ARGUS,

    MAX_ENCOUNTER,

    DATA_COSMETIC_TORMENT
};

enum eCreatures
{
    NPC_DREADWING                   = 125487,
    NPC_LIGHTFORGED_WIREFRAME       = 125476,
    NPC_LIGHTFORGED_WIREFRAME_1     = 127256,
    NPC_LIGHT_CENTURION             = 125478,
    NPC_LIGHT_COMANDIR              = 125480,
    NPC_LIGHT_PRIEST                = 124778,

    NPC_EXARH_TURALION              = 125512, 
    NPC_TELEPORT_OF_LIGHTFORGED_1   = 130137,

    NPC_BATTLE_SHIP                 = 125771,

    NPC_RUN_NPC_1                   = 127221,
    NPC_RUN_NPC_2                   = 126444,

    NPC_FEL_PORTAL_1                = 127050,
    NPC_FEL_PORTAL_2                = 126527,

    NPC_IMAGE_OF_EONAR              = 128352,
    NPC_IMONAR_INTRO                = 125692,

    NPC_IMPLOSIONS                  = 125603,
    NPC_PRIESTESS_OF_DELIRIUM       = 128060,
    NPC_AZARA                       = 122467,
    NPC_WIND_STALKER                = 123719,

//! BOSSES

    //Garothi Worldbreaker
    NPC_WORLDBREAKER                = 122450,
    NPC_ANNIHILATOR_OF_KINGAROTH    = 123398,
    NPC_WORLDBREAKER_DECIMATOR      = 122773,
    NPC_WORLDBREAKER_ANNIHILATOR    = 122778,
    NPC_WB_ANNIHILATION_TRIGGER     = 122818,
    NPC_WB_ANNIHILATION_TRIGGER_2   = 124330,
    NPC_SURGING_FEL_TRIGGER         = 124167, //Heroic+
    NPC_SURGING_FEL_TRIGGER_MOVER   = 128429, //Heroic+

    //Felhounds of Sargeras
    NPC_SHATUG                      = 122135,
    NPC_FHARG                       = 122477,
    NPC_MOLTEN_TOUCH                = 122507,

    //Antoran High Command
    NPC_CENTER_STALKER              = 122637, //Event Manager
    NPC_ADMIRAL_SVIRAX              = 122367,
    NPC_CHIEF_ENGINEER_ISHKAR       = 122369,
    NPC_GENERAL_ERODUS              = 122333,
    NPC_ADMIRAL_POD                 = 122554,
    NPC_ENGINEER_POD                = 123020,
    NPC_GENERAL_POD                 = 123013,
    NPC_ADMIRAL_SVIRAX_IN_POD       = 130184,
    NPC_ENGINEER_ISHKAR_IN_POD      = 130185,
    NPC_GENERAL_ERODUS_IN_POD       = 130186,
    NPC_SCOUT_SHIP                  = 122944,
    NPC_ENTROPIC_MINE               = 122992,
    NPC_FANATICAL_PYROMANCER        = 122890,
    NPC_FELBLADE_SHOCKTROOPER       = 122718,
    NPC_LEGION_CRUISER              = 122739,
    NPC_FELSHIELD_EMITTER           = 122867,
    NPC_DISRUPTOR_BEACON            = 122884,
    NPC_SCREAMING_SHRIKE            = 128069, //Mythic
    NPC_HOLOGRAM_STALKER            = 127741, //Visual Room trigger

    //Portal Keeper Hasabel
    NPC_HASABEL                     = 122104,
    NPC_GATEWAY_XOROTH_ENTER        = 122494, //Fire portals
    NPC_GATEWAY_XOROTH_EXIT         = 122533,
    NPC_GATEWAY_RANCORA_ENTER       = 122543, //Fel portals
    NPC_GATEWAY_RANCORA_EXIT        = 122555,
    NPC_GATEWAY_NATHREZA_ENTER      = 122558, //Shadow portals
    NPC_GATEWAY_NATHREZA_EXIT       = 122559,
    NPC_VULCANAR                    = 122211, //Fire Mini-boss
    NPC_LADY_DACIDION               = 122212, //Fel Mini-boss
    NPC_LORD_EILGAR                 = 122213, //Shadow Mini-boss
    NPC_TRIG_COLLAPSING_WORLD       = 122425,
    NPC_TRIG_FELCRUSH_PORTAL        = 122438,
    NPC_TRIG_TRANSPORT_PORTAL       = 122761,
    NPC_BLAZING_IMP                 = 122783,
    NPC_HUNGERING_STALKER           = 123223,
    NPC_FELTOUCHED_SKITTERER        = 123702,
    NPC_TRIG_PORTAL_AT              = 128293,
    //Fire platform
    NPC_TRIG_PORTAL_XOROTH          = 122586,
    NPC_TRIG_FLAMES_OF_XOROTH       = 122628,
    NPC_EVERBURNING_FLAMES          = 122733,
    NPC_EVERBURNING_FLAMES_PLR      = 123003,
    //Fel platform
    NPC_TRIG_PORTAL_RANCORA         = 122587,
    NPC_TRIG_ACID_OF_RANCORA        = 122647,
    NPC_FELSILK_WEB                 = 122897,
    //Shadow platform
    NPC_TRIG_PORTAL_NATHREZA        = 122588,
    NPC_TRIG_SHADOWS_OF_NATHREZA    = 122953,
    NPC_TRIG_ETERNAL_DARKNESS       = 122966,

    //Eonar the Life-Binder
    NPC_EONAR_EVENT                 = 122500, //Encounter Starter
    NPC_THE_PARAXIS                 = 124445,
    NPC_THE_PARAXIS_2               = 125364, //Spawn after complete encounter
    NPC_JUMP_PAD                    = 124962,
    NPC_JUMP_DEST                   = 124963,
    NPC_LEGION_SHIP_SMALL           = 124298,
    NPC_LEGION_SHIP_BIG             = 124288,
    NPC_INVASION_POINT              = 130000, //Vignette trigger
    NPC_FEL_INFUSED_DESTRUCTOR      = 123760,
    NPC_FEL_CHARGED_OBFUSCATOR      = 124207,
    NPC_FEL_POWERED_PURIFIER        = 123726, //Heroic+
    NPC_FEL_LORD                    = 123452,
    NPC_FELGUARD                    = 123451,
    NPC_FEL_HOUND                   = 123191,
    NPC_VOLANT_KERAPTERON           = 124227,
    NPC_DEMONIC_PORTAL              = 124424, //Kerapteron start pos
    NPC_SPEAR_OF_DOOM               = 125319,
    NPC_PARAXIS_INQUISITOR          = 125429, //Mythic
    NPC_CRYSTAL_TARGETED            = 125917,
    NPC_CRYSTAL_BURNING             = 125918,
    NPC_CRYSTAL_ARCANE_SINGULARITY  = 125919,
    NPC_CRYSTAL_FOUL_STEPS          = 125920,

    //Imonar the Soulhunter
    NPC_IMONAR                      = 124158,
    NPC_IMONAR_CONFLAGRATION        = 124550,
    NPC_IMONAR_TRAPS                = 124686,
    NPC_BOMBING_RUN                 = 124704, //Small Ship
    NPC_ARTILLERY_STRIKE            = 124889, //Big Ship
    NPC_PULSE_GRENADE               = 124928,
    NPC_SHRAPNEL_BLAST              = 124776,

    //Kingaroth
    NPC_KINGAROTH                   = 122578,
    NPC_DETONATION_CHARGE           = 122585,
    NPC_RUINER                      = 124230,
    NPC_INCINERATOR_STALKER         = 124879,
    NPC_INFERNAL_TOWER_1            = 122634,
    NPC_INFERNAL_TOWER_2            = 122740,
    NPC_INFERNAL_TOWER_3            = 122885,
    NPC_GAROTHI_ANNIHILATOR         = 123906,
    NPC_GAROTHI_DECIMATOR           = 123921,
    NPC_GAROTHI_DEMOLISHER          = 123929,
    NPC_APOCALYPSE_BLAST_STALKER    = 125462,
    NPC_ANNIHILATION_TRIGGER        = 124160,
    NPC_EMPOWERED_RUINER_STALKER    = 125646,

    //Varimathras
    NPC_VARIMATHRAS                 = 122366,
    NPC_SHADOW_OF_VARIMATHRAS       = 122590, //Alone in the Darkness
    NPC_SHADOW_OF_VARIMATHRAS_2     = 122643, //Shadow Hunter
    NPC_COSMETIC_TORMENT            = 68553,

    //Coven of Shivarra
    NPC_THE_COVEN_OF_SHIVARRA       = 128311, //Event Manager
    NPC_ASARA                       = 122467,
    NPC_NOURA                       = 122468,
    NPC_DIIMA                       = 122469,
    NPC_THURAYA                     = 125436, //Mythic
    NPC_TORMENT_OF_NORGANNON        = 123503,
    NPC_TORMENT_OF_GOLGANNETH       = 124164,
    NPC_TORMENT_OF_KHAZGOROTH       = 124166,
    NPC_TORMENT_OF_AMANTHUL         = 125837,
    NPC_WHIRLING_SABER              = 123348,
    NPC_SHADOW_BLADE                = 123086,
    NPC_COSMIC_GLARE                = 126320,

    //Aggramar
    NPC_AGGRAMAR                    = 121975,
    NPC_EMBER_OF_TAESHALACH         = 122532,
    NPC_FLAME_OF_TAESHALACH         = 121985,

    //Argus
    NPC_ARGUS                       = 124828,
    NPC_ARGUS_GOLGANNETH            = 126268,
    NPC_ARGUS_KHAZGOROTH            = 125886,
    NPC_ARGUS_EONAR                 = 126267,
    NPC_ARGUS_AMANTHUL              = 125885,
    NPC_ARGUS_AGGRAMAR              = 125893,
    NPC_ARGUS_NORGANNON             = 126266,
    NPC_SOULBLIGHT_ORB              = 125008,
    NPC_EDGE_OF_OBLITERATION        = 126828,
    NPC_CONSTELLAR_DESIGNATE        = 127192,
    NPC_GIFT_OF_THE_LIFEBINDER      = 129386,
    NPC_HUNGERING_SOUL              = 129635,
    NPC_REORIGINATION_MODULE        = 127809,
    NPC_APOCALYPSIS_MODULE          = 130179, //Mythic
    NPC_MOTE_OF_TITANIC_POWER       = 129722,
    NPC_CHAINS_OF_SARGERAS          = 130202, //Mythic
    NPC_EDGE_OF_ANNIHILATION        = 130842, //Mythic
};

enum eGameObjects
{
    GO_STONE                        = 278488,
    GO_INVISIBLE_WALL               = 277365,
    GO_ELEVATOR                     = 278815,
    GO_PORTAL_TO_ELUNARIES          = 277474,

    GO_ARCANE_BARRIER               = 249386,
    GO_ARCANE_BARRIER_VISUAL        = 273911,

    GO_COMMAND_DOOR                 = 277660,

    GO_HASABEL_DOOR                 = 277521,

    GO_EONAR_PARAXIS_SHIP           = 272683,
    GO_EONAR_DOOR                   = 273688,
    GO_EONAR_CACHE                  = 276503,
    GO_EONAR_PARAXIS_DOOR_1         = 272759,
    GO_EONAR_PARAXIS_DOOR_2         = 273016,
    GO_EONAR_PARAXIS_DOOR_3         = 273017,

    GO_KINGAROTH_DOOR               = 277531,
    GO_KINGAROTH_TRAP_LEFT_1        = 276288,
    GO_KINGAROTH_TRAP_LEFT_2        = 276294,
    GO_KINGAROTH_TRAP_RIGHT_1       = 276292,
    GO_KINGAROTH_TRAP_RIGHT_2       = 276289,
    GO_KINGAROTH_TRAP_BACK_1        = 276290,
    GO_KINGAROTH_TRAP_BACK_2        = 276293,

    GO_VARIMATHRAS_DOOR_1           = 277179,
    GO_VARIMATHRAS_DOOR_2           = 277180,
    GO_VARIMATHRAS_TORMENT_1        = 272716,
    GO_VARIMATHRAS_TORMENT_2        = 272717,
    GO_VARIMATHRAS_TORMENT_3        = 272718,
    GO_VARIMATHRAS_TORMENT_4        = 272719,
    GO_VARIMATHRAS_TORMENT_5        = 272720,
    GO_VARIMATHRAS_TORMENT_6        = 272721,
    GO_VARIMATHRAS_TORMENT_7        = 272722,
    GO_VARIMATHRAS_TORMENT_8        = 272723,

    GO_COVEN_DOOR_1                 = 272868,
    GO_COVEN_DOOR_2                 = 277476,

    GO_AGGRAMAR_DOOR                = 273686,
    GO_AGGRAMAR_BRIDGE              = 277477,

    GO_ARGUS_CHEST                  = 277355,
};

enum eSpells
{
    SPELL_INTRO_FIELD_OF_FIRE           = 249100,
    SPELL_SPAWN                         = 247963,
    SPELL_LIGHT_SHIELD                  = 248515,

    SPELL_BLESSING_LIFEBINDER_VISUAL    = 254097,
    SPELL_SURGE_OF_LIFE_OVERRIDE        = 245764,
    SPELL_SURGE_OF_LIFE_OVERRIDE_2      = 254506,

    //Varimathras Cosmetic
    SPELL_TORMENT_FLAME_VISUAL          = 243969,
    SPELL_TORMENT_FROST_VISUAL          = 243970,
    SPELL_TORMENT_FEL_VISUAL            = 243971,
    SPELL_TORMENT_SHADOW_VISUAL         = 243972,
};

#endif
