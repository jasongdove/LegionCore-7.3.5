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

#include "ConfusedMovementGenerator.h"
#include "Creature.h"
#include "MapManager.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "Player.h"
#include "Unit.h"
#include "VMapFactory.h"

template <class T>
ConfusedMovementGenerator<T>::~ConfusedMovementGenerator()
{
    delete _path;
}

template<class T>
void ConfusedMovementGenerator<T>::DoInitialize(T& owner)
{
    if (!owner.IsAlive())
        return;

    owner.AddUnitState(UNIT_STATE_CONFUSED);
    owner.SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    owner.StopMoving();

    _timer.Reset(0);
    _reference = owner.GetPosition();
}

template<class T>
void ConfusedMovementGenerator<T>::DoReset(T& owner)
{
    DoInitialize(owner);
}

template<class T>
bool ConfusedMovementGenerator<T>::DoUpdate(T& owner, uint32 diff)
{
    if (!owner.IsAlive())
        return false;

    if (owner.HasUnitState(UNIT_STATE_NOT_MOVE) || owner.IsMovementPreventedByCasting())
    {
        _interrupt = true;
        owner.StopMoving();
        return true;
    }
    else
        _interrupt = false;

    // waiting for next move
    _timer.Update(diff);
    if (!_interrupt && _timer.Passed() && owner.movespline->Finalized())
    {
        // start moving
        owner.AddUnitState(UNIT_STATE_CONFUSED_MOVE);

        Position destination(_reference);
        float distance = 4.0f * frand(0.0f, 1.0f) - 2.0f;
        float angle = frand(0.0f, 1.0f) * float(M_PI) * 2.0f;
        owner.MovePositionToFirstCollision(destination, distance, angle);

        if (!_path)
            _path = new PathGenerator(&owner);

        _path->SetPathLengthLimit(30.0f);
        bool result = _path->CalculatePath(destination.GetPositionX(), destination.GetPositionY(), destination.GetPositionZ());
        if (!result || (_path->GetPathType() & PATHFIND_NOPATH)
            || (_path->GetPathType() & PATHFIND_SHORTCUT)
            || (_path->GetPathType() & PATHFIND_FARFROMPOLY))
        {
            _timer.Reset(100);
            return true;
        }

        Movement::MoveSplineInit init(owner);
        init.MovebyPath(_path->GetPath());
        init.SetWalk(true);
        int32 traveltime = init.Launch();
        _timer.Reset(traveltime + urand(800, 1500));
    }

    return true;
}

template<>
void ConfusedMovementGenerator<Player>::DoFinalize(Player &unit)
{
    unit.RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit.ClearUnitState(UNIT_STATE_CONFUSED);
    unit.StopMoving();
}

template<>
void ConfusedMovementGenerator<Creature>::DoFinalize(Creature &unit)
{
    unit.RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit.ClearUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_CONFUSED_MOVE);
    if (unit.getVictim())
        unit.SetTarget(unit.getVictim()->GetGUID());
}

template ConfusedMovementGenerator<Player>::~ConfusedMovementGenerator();
template ConfusedMovementGenerator<Creature>::~ConfusedMovementGenerator();
template void ConfusedMovementGenerator<Player>::DoInitialize(Player& player);
template void ConfusedMovementGenerator<Creature>::DoInitialize(Creature& creature);
template void ConfusedMovementGenerator<Player>::DoReset(Player& player);
template void ConfusedMovementGenerator<Creature>::DoReset(Creature& creature);
template bool ConfusedMovementGenerator<Player>::DoUpdate(Player& player, uint32 diff);
template bool ConfusedMovementGenerator<Creature>::DoUpdate(Creature& creature, uint32 diff);
