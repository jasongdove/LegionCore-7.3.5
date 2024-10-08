/*
    Dungeon : Dark Heart Thicket 100-110
*/

#ifndef DARKHEART_THICKET_H_
#define DARKHEART_THICKET_H_

#define DataHeader "DHT"

enum eData
{
    DATA_GLAIDALIS         = 0,
    DATA_OAKHEART          = 1,
    DATA_DRESARON          = 2,
    DATA_XAVIUS            = 3,
    MAX_ENCOUNTER,
};

enum eCreatures
{
    //Xavius summons
    NPC_NIGHTMARE_BINDINGS               = 101329, //Malfurion cage
    NPC_MALFURION_STORMRAGE              = 100652,

    //Pre-event Glaydalis
    NPC_DRUIDIC_PRESERVER                = 100403,
    //dresaron
    NPC_DRESARON                         = 99200,

    //Dresaron summons
    NPC_CORRUPTED_DRAGON_EGG             = 101072,
    NPC_HATESPAWN_WHELPLING              = 101074,
    //Dresaron achieve npc
    NPC_HATESPAWN_ABOMINATION            = 111008,
    NPC_EMERALD_EGG                      = 541898, //custom id but the same npc
};

enum eGameObjects
{
    GO_GLAIDALIS_FIRE_DOOR               = 246910,
    GO_GLAIDALIS_INVIS_DOOR              = 246905,
    GO_DRESARON_FIRE_DOOR                = 247039,
    GO_OAKHEART_DOOR                     = 246939,

    //Mythic cache
    GO_XAVIUS_CHALLENGER_CACHE           = 252668,
    GO_XAVIUS_SUPERIOR_CHALLENGER_CACHE  = 252669,
    GO_XAVIUS_PEERLESS_CHALLENGER_CACHE  = 252670,
};

#endif