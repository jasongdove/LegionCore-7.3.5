/*
* Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef CREATURE_DATA_H
#define CREATURE_DATA_H

#include "Define.h"

enum class CreatureGroundMovementType : uint8
{
    None,
    Run,
    Hover,

    Max
};

enum class CreatureFlightMovementType : uint8
{
    None,
    DisableGravity,
    CanFly,

    Max
};

enum class CreatureRandomMovementType : uint8
{
    Walk,
    CanRun,
    AlwaysRun,

    Max
};

struct TC_GAME_API CreatureMovementData
{
    CreatureMovementData();
    CreatureGroundMovementType Ground;
    CreatureFlightMovementType Flight;
    bool Swim;
    bool Rooted;
    CreatureRandomMovementType Random;
    uint32 InteractionPauseTimer;

    bool IsGroundAllowed() const { return Ground != CreatureGroundMovementType::None; }
    bool IsSwimAllowed() const { return Swim; }
    bool IsFlightAllowed() const { return Flight != CreatureFlightMovementType::None; }
    bool IsRooted() const { return Rooted; }
    bool IsGravityDisabled() const { return Flight == CreatureFlightMovementType::DisableGravity; }
    bool CanFly() const { return Flight == CreatureFlightMovementType::CanFly; }
    bool IsHoverEnabled() const { return Ground == CreatureGroundMovementType::Hover; }

    CreatureRandomMovementType GetRandom() const { return Random; }

    uint32 GetInteractionPauseTimer() const { return InteractionPauseTimer; }

    std::string ToString() const;
};

#endif
