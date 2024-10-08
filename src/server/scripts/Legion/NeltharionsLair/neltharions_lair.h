/*
    Dungeon : Neltharions Lair 100-110
*/

#ifndef NELTHARIONS_LAIR_H_
#define NELTHARIONS_LAIR_H_

#define DataHeader "NL"

enum eData
{
    DATA_ROKMORA      = 0,
    DATA_ULAROGG      = 1,
    DATA_NARAXAS      = 2,
    DATA_DARGRUL      = 3,
    MAX_ENCOUNTER,
};

enum eCreatures
{
    //Rokmora
    NPC_ROKMORA                 = 91003,
    NPC_ULAROGG_INTRO           = 105300,
    NPC_NAVARROGG_INTRO         = 100700,
    NPC_BLIGHTSHARD_SKITTER     = 97720,
    NPC_RAZOR_SHARDS_STALKER    = 105811,

    //Ularogg Cragshaper
    NPC_ULAROGG_CRAGSHAPER      = 91004,
    NPC_MIGHTSTONE_BREAKER      = 90997,
    NPC_BLIGHTSHARD_SHAPER      = 90998,
    NPC_ROCKBOUND_PELTER        = 91008,
    NPC_BELLOWING_IDOL          = 98081,
    NPC_BELLOWING_IDOL_2        = 100818,

    //Naraxas
    NPC_WORMSPEAKER_DEVOUT      = 101075,
    NPC_ANGRY_CROWD             = 109137,

    //Dargul
    NPC_MOLTEN_CHARSKIN         = 101476,
    NPC_CRYSTAL_WALL_STALKER    = 101593,
};

enum eGameObjects
{
    GO_ROKMORA_DOOR             = 248871,
    GO_ULAROGG_DOOR             = 248765,
    GO_ULAROGG_DOOR_2           = 248763,
    GO_NARAXAS_DOOR             = 248764,
    GO_NARAXAS_EXIT_DOOR_1      = 248833,
    GO_NARAXAS_EXIT_DOOR_2      = 248851,

    GO_CRYSTAL_WALL_COLLISION   = 246251,

    GO_NARAXAS_CHEST            = 251482,
};

#endif