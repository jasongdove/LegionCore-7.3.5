/*
    Dungeon : Maw of Souls 100-110
*/

#ifndef MAW_OF_SOULS_H_
#define MAW_OF_SOULS_H_

#define DataHeader "MOS"

enum eData
{
    DATA_YMIRON         = 0,
    DATA_HARBARON       = 1,
    DATA_SKJAL          = 2,
    DATA_HELYA          = 3,
    MAX_ENCOUNTER,

    DATA_YMIRON_GORN,
    DATA_SHIP,
    DATA_SAVE_PLAYER_GUID
};

enum eCreatures
{
    //Ymiron
    NPC_YMIRON                  = 96756,
    NPC_BIRD                    = 97163,
    NPC_SEACURSED_SLAVER        = 97043,
    NPC_SHIELDMAIDEN            = 102104,
    NPC_RUNECARVER              = 102375,
    NPC_RUNECARVER_IN_CAGE      = 102894,
    NPC_RUNECARVER_INTRO        = 114712,
    NPC_RISEN_WARRIOR           = 98246,

    //Harbaron
    NPC_HARBARON                = 96754,
    NPC_SOUL_FRAGMENT           = 98761,
    NPC_COSMIC_SCYTHE           = 98989,
    NPC_COSMIC_SCYTHE_2         = 100839,

    NPC_SKJAL                   = 99307,
    NPC_HELARJAR_CHAMPION       = 97097,
    NPC_SEACURSED_SWIFTBLADE    = 98919,
    NPC_HELARJAR_MISTCALLER     = 99033,
    NPC_SEACURSED_MISTMENDER    = 97365,
    NPC_SEACURSED_SOULKEEPER    = 97200,

    //Helya
    NPC_HELYA                   = 96759,
    NPC_DESTRUCTOR_TENTACLE     = 99803,  //Veh Passenger         - 99801
    NPC_GRASPING_TENTACLE_1     = 99800,  //Veh Passenger Right_1 - 98363
    NPC_GRASPING_TENTACLE_2     = 100361, //Veh Passenger Left_1  - 100362
    NPC_GRASPING_TENTACLE_3     = 100359, //Veh Passenger Left_2  - 100360
    NPC_GRASPING_TENTACLE_4     = 100353, //Veh Passenger Right_2 - 100354
    NPC_SWIRLING_POOL_VEH       = 97099,  //Veh Passenger - создает АТ и суммонит тентаклю.
    NPC_PIERCING_TENTACLE       = 100188, //Появляется, бьет 197112 и ломает пол, исчезает.
    NPC_SWIRLING_POOL_TRIG      = 102306, //Плюеется из отверстий водой
};

enum eGameObjects
{
    GO_YMIRON_GORN              = 247041,
    GO_HARBARON_DOOR            = 246947,
    GO_HARBARON_DOOR_2          = 246888,
    GO_SKJAL_INVIS_DOOR         = 246435,
    GO_SKJAL_DOOR_1             = 265477,
    GO_SKJAL_DOOR_2             = 265476,

    GO_SHIP                     = 246919,
    GO_HELYA_CHEST              = 246036,

    GO_SWIRLING_POOL_1          = 246834,
    GO_SWIRLING_POOL_2          = 246835,
    GO_SWIRLING_POOL_3          = 246836,
    GO_SWIRLING_POOL_4          = 246837,
    GO_SWIRLING_POOL_5          = 246838,
    GO_SWIRLING_POOL_6          = 246839,
    GO_SWIRLING_POOL_7          = 246840,
    GO_SWIRLING_POOL_8          = 246841,
    GO_SWIRLING_POOL_9          = 246842,
    GO_SWIRLING_POOL_10         = 246843,
    GO_SWIRLING_POOL_11         = 246844,
};

enum eStateShip
{
    STATE_DESTROY               = 0,
    STATE_REBUILDING            = 1,
};

#endif