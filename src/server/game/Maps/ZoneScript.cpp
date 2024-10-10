#include "ZoneScript.h"
#include "Creature.h"

uint32 ZoneScript::GetCreatureEntry(uint32, CreatureData const* data)
{
    return data->id;
}
