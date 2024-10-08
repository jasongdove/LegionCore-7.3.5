/*
 * Copyright (C) 2008-20XX JadeCore <http://www.pandashan.com>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TERRACE_OF_ENDLESS_SPRING_H_
#define TERRACE_OF_ENDLESS_SPRING_H_

#define DataHeader "TES"

#include "SpellScript.h"
#include "Map.h"
#include "Creature.h"
#include "CreatureAIImpl.h"

enum eData
{
    DATA_PROTECTORS,
    DATA_TSULONG,
    DATA_LEI_SHI,
    DATA_SHA_OF_FEAR,
    DATA_MAX_BOSS_DATA
};

enum eSpells
{
    SPELL_RITUAL_OF_PURIFICATION = 126848
};

enum eActions
{
    ACTION_START_TSULONG_WAYPOINT = 1,
    ACTION_INTRO_FINISHED = 2
};

enum eCreatures
{
    // Protectors of the Endless
    NPC_ANCIENT_ASANI = 60586,
    NPC_ANCIENT_REGAIL = 60585,
    NPC_PROTECTOR_KAOLAN = 60583,
    NPC_DEFILED_GROUND = 60906,
    NPC_COALESCED_CORRUPTION = 60886,
    NPC_MINION_OF_FEAR_CONTROLLER = 60957,
    NPC_MINION_OF_FEAR = 60885,

    // Tsulong
    NPC_TSULONG = 62442,

    // Lei Shi
    NPC_LEI_SHI = 62983,
    NPC_ANIMATED_PROTECTOR = 62995,
    NPC_LEI_SHI_HIDDEN = 63099,

    // Sha of Fear
    NPC_SHA_OF_FEAR = 60999,
    NPC_PURE_LIGHT_TERRACE = 60788,
    NPC_TERROR_SPAWN = 61034,

    // Thrashs
    NPC_APPARITION_OF_FEAR = 64368,
    NPC_APPARITION_OF_TERROR = 66100,
    NPC_NIGHT_TERRORS = 64390,
    NPC_NIGHT_TERROR_SUMMON = 64393
};

enum eGameObjects
{
    GOB_WALL_OF_COUNCILS_VORTEX = 214854,
    GOB_COUNCILS_VORTEX = 214853,

    GOB_WALL_OF_LEI_SHI = 214852,
    GOB_LEI_SHIS_VORTEX = 214851,
    GOB_LEI_SHI_CHEST_NORMAL = 213076,
    GOB_LEI_SHI_CHEST_HEROIC = 213075
};

enum ePhases
{
};

enum eWeapons
{
};

enum eEvents
{
};

enum eTypes
{
    INTRO_DONE
};

enum eTimers
{
    TIMER_TSULONG_SPAWN = 10000,
};

#endif // TERRACE_OF_ENDLESS_SPRING_H_
