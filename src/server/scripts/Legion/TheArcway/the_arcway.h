/*
    Dungeon : The Arcway 100-110
*/

#ifndef THE_ARCWAY_H_
#define THE_ARCWAY_H_

#define DataHeader "AW"

enum eData
{
    DATA_IVANYR         = 0,
    DATA_CORSTILAX      = 1,
    DATA_XAKAL          = 2,
    DATA_NALTIRA        = 3,
    DATA_VANDROS        = 4,
    MAX_ENCOUNTER,

    DATA_RAND_TELEPORT,
};

enum eCreatures
{
    //Ivanyr
    NPC_NIGHT_CRYSTAL           = 98734,

    //Corstilax
    NPC_SUPPRESSION_PROTOCOL    = 99628,
    NPC_QUARANTINE              = 99560,
    NPC_PIPE_STALKER            = 99446,
    NPC_DESTABLIZED_ORB         = 110863,

    //Xakal
    NPC_FISSURE                 = 100342,
    NPC_DREAD_FELBAT            = 100393,

    //Naltira
    NPC_ENCHANTED_BROODLING_I   = 105876, //Intro
    NPC_VICIOUS_MANAFANG_I      = 98759,  //Intro
    NPC_VICIOUS_MANAFANG        = 110966,

    //Vandros
    NPC_ADVISOR_VANDROS         = 98208, //102849
    NPC_TIMELESS_WRAITH         = 103130,
};

enum eGameObjects
{
    GO_CORSTILAX_DOOR_1         = 245968,
    GO_CORSTILAX_DOOR_2         = 246024,
    GO_XAKAL_FISSURE            = 245606,

    GO_DOOR_A                   = 250272,
    GO_DOOR_B                   = 250278,
    GO_DOOR_D                   = 250273,
    GO_DOOR_G                   = 250275,
    GO_DOOR_K                   = 250276,
    GO_DOOR_8                   = 250634,
    GO_DOOR_9                   = 250635,
    GO_DOOR_3                   = 250636,
    GO_DOOR_4                   = 250637,
    
    
};

#endif