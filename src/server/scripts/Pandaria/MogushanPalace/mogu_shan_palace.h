/*===============
================*/

#ifndef MOGUSHAN_PALACE_H_
#define MOGUSHAN_PALACE_H_

#define DataHeader "MSP"

enum eData
{
    DATA_TRIAL_OF_THE_KING      = 0,
    DATA_GEKKAN                 = 1,
    DATA_XIN_THE_WEAPONMASTER   = 2,

    DATA_GEKKAN_ADDS            = 3
};

enum eSpells
{
    //Kuai the brute
    SPELL_COMBAT_SOUND_LOOP         = 126252,
    SPELL_SHOCKWAVE                 = 119922,
    SPELL_PICK_SHOCKWAVE_TARGET     = 120499,
    SPELL_SHOCKWAVE_2               = 119929,
    SPELL_SHOCKWAVE_3               = 119930,
    SPELL_SHOCKWAVE_4               = 119931,
    SPELL_SHOCKWAVE_5               = 119932,
    SPELL_SHOCKWAVE_6               = 119933,
    SPELL_GUARDIAN_TAUNT            = 85667,
    //Ming the cunning
    SPELL_LIGHTNING_BOLT            = 123654,
    SPELL_WHIRLING_DERVISH          = 119981,
    SPELL_MAGNETIC_FIELD            = 120100,
    SPELL_MAGNETIC_FIELD_2          = 120101,
    SPELL_MAGNETIC_FIELD_3          = 120099,
    //Haiyan the unstoppable
    SPELL_TRAUMATIC_BLOW            = 123655,
    SPELL_CONFLAGRATE               = 120160,
    SPELL_CONFLAGRATE_2             = 120167,
    SPELL_CONFLAGRATE_3             = 120161,
    SPELL_CONFLAGRATE_4             = 120201,
    SPELL_METEOR                    = 120195,
    SPELL_METEOR_2                  = 120194,
    SPELL_METEOR_3                  = 120196,
    //Xin trigger
    SPELL_PING                      = 120510,
    SPELL_MOGU_JUMP                 = 120444,
    SPELL_THROW_DAMAGE              = 119311,
    SPELL_THROW_AURA                = 119315,
    SPELL_AXE_TOURBILOL             = 119373,
    //Gurthan scrapper, harthak adept and kargesh grunt
    SPELL_GRUNT_AURA                = 121746,
    //Whirling dervish trigger
    SPELL_WIRHLING_DERVISH_2        = 119982,
    SPELL_WHIRLING_DERVISH_3        = 119994,
    SPELL_THROW                     = 120087,
    SPELL_THROW_2                   = 120035,
    
    //Achiev: Quarrelsome Quilen Quintet
    SPELL_ACHIEV_JADE_QUILEN        = 124352,
    
    //Achiev: Glintrok N' Roll
    SPELL_GLINTROK_SCOUT_WARNING    = 119076,
    SPELL_SAUROK_ACHIEV_AURA        = 118994,
    
    //Achiev: What Does This Button Do?
    SPELL_SECRET_DEFENSE_MECHANISM  = 124527,
    SPELL_TURN_OFF_BLADES           = 124531,
    
    //Achiev: Polyformic Acid Science
    SPELL_ACHIEVEMENT_CHECK         = 124356
};

enum eCreatures
{
    //Boss
    CREATURE_KUAI_THE_BRUTE                 = 61442,
    CREATURE_MING_THE_CUNNING               = 61444,
    CREATURE_HAIYAN_THE_UNSTOPPABLE         = 61445,
    CREATURE_XIN_THE_WEAPONMASTER_TRIGGER   = 61884,
    CREATURE_XIN_THE_WEAPONMASTER           = 61398,
    //Trash
    CREATURE_GURTHAN_SCRAPPER               = 61447,
    CREATURE_HARTHAK_ADEPT                  = 61449,
    CREATURE_KARGESH_GRUNT                  = 61450,
    //Trigger
    CREATURE_WHIRLING_DERVISH               = 61626,

    CREATURE_GEKKAN                         = 61243,
    CREATURE_GLINTROK_IRONHIDE              = 61337,
    CREATURE_GLINTROK_SKULKER               = 61338,
    CREATURE_GLINTROK_ORACLE                = 61339,
    CREATURE_GLINTROK_HEXXER                = 61340,

    //XIN THE WEAPONMASTER
    CREATURE_ANIMATED_STAFF                 = 61433,
    CREATURE_ANIMATED_AXE                   = 61451,
    CREATURE_LAUNCH_SWORD                   = 63808,
    
    //Achiev: Quarrelsome Quilen Quintet
    CREATURE_JADE_QUILEN                    = 63091
};

enum eTypes
{
    TYPE_MING_ATTACK,
    TYPE_KUAI_ATTACK,
    TYPE_HAIYAN_ATTACK,
    TYPE_ALL_ATTACK,

    TYPE_MING_RETIRED,
    TYPE_KUAI_RETIRED,
    TYPE_HAIYAN_RETIRED,

    TYPE_WIPE_FIRST_BOSS,

    TYPE_MING_INTRO,
    TYPE_OUTRO_01,
    TYPE_OUTRO_02,
    TYPE_OUTRO_03,
    TYPE_OUTRO_04,
    TYPE_OUTRO_05,

    TYPE_GET_ENTOURAGE_0, //14
    TYPE_GET_ENTOURAGE_1, //15
    TYPE_GET_ENTOURAGE_2, //16
    TYPE_GET_ENTOURAGE_3, //17
    
    TYPE_ACTIVATE_ANIMATED_STAFF, //18
    TYPE_ACTIVATE_ANIMATED_AXE, //19
    TYPE_ACTIVATE_SWORD, //20
    
    TYPE_JADECOUNT, //21
    TYPE_GEMCOUNT //22
};

enum eGameObjects
{
    GO_DOOR_BEFORE_TRIAL    = 213594,
    GO_TRIAL_CHEST          = 214520,
    GO_TRIAL_CHEST2         = 214521,
    GO_DOOR_AFTER_TRIAL     = 213593,
    GO_DOOR_BEFORE_KING     = 213596,
    GO_SECRET_DOOR          = 213810
};

const Position otherPos[4] = 
{
    {   -4222.63f, -2613.71f, 16.48f, 6.2f     },
    {   -4326.13f, -2519.60f, -28.39f, 3.18f   },
    {   -4653.52f, -2655.62f, 26.10f, 3.06f    },
    {   -4612.78f, -2571.62f, 26.10f, 0.04f    }
};

#endif
