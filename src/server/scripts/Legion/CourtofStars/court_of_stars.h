/*
    Dungeon : Court of Stars 110
*/

#ifndef COURT_OF_STARS_H_
#define COURT_OF_STARS_H_

#define DataHeader "COS"

enum eData
{
    DATA_CAPTAIN_GERDO          = 0,
    DATA_TALIXAE                = 1,
    DATA_MELANDRUS              = 2,
    DATA_MELANDRUS_EVENT        = 3,  // для дверей и корректности
    MAX_ENCOUNTER,

    DATA_BEACON_ACTIVATE
};

enum eCreatures
{
    //Patrol Captain Gerdo
    NPC_PATROL_CAPTAIN_GERDO    = 104215,
    NPC_GERDO_TRIG_FRONT        = 104384,
    NPC_GERDO_TRIG_BACK         = 104400,
    NPC_GERDO_ARCANE_BEACON     = 104245,

    //Talixae adds
    NPC_JAZSHARIU               = 104273,
    NPC_BAALGAR_THE_WATCHFUL    = 104274,
    NPC_IMACUTYA                = 104275,
    NPC_FELBOUND_ENFORCER       = 104278,
    NPC_INFERNAL_IMP            = 112668,

    //Melandrus adds
    NPC_IMAGE_MELANDRUS         = 105754,
    NPC_ENVELOPING_WINDS        = 112687,

    NPC_MELANDRUS               = 104218,
};

enum eGameObjects
{
    GO_GERDO_DOOR               = 251849,
    GO_MELANDRUS_DOOR_1         = 251847,
    GO_MELANDRUS_DOOR_2         = 251848,
};

#endif