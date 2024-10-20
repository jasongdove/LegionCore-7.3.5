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

#ifndef TRINITY_FLEEINGMOVEMENTGENERATOR_H
#define TRINITY_FLEEINGMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "PathGenerator.h"
#include "Timer.h"

template<class T>
class FleeingMovementGenerator : public MovementGeneratorMedium< T, FleeingMovementGenerator<T> >
{
    public:
        explicit FleeingMovementGenerator(ObjectGuid fleeTargetGUID) : _path(nullptr), _fleeTargetGUID(fleeTargetGUID), _timer(0), _interrupt(false) { }

        MovementGeneratorType GetMovementGeneratorType() override { return FLEEING_MOTION_TYPE; }

        void DoInitialize(T &);
        void DoFinalize(T &);
        void DoReset(T &);
        bool DoUpdate(T &, const uint32 &);

    private:
        void SetTargetLocation(T &owner);
        void GetPoint(T &owner, Position &position);

        std::unique_ptr<PathGenerator> _path;
        ObjectGuid _fleeTargetGUID;
        TimeTracker _timer;
        bool _interrupt;
};

class TimedFleeingMovementGenerator : public FleeingMovementGenerator<Creature>
{
    public:
        explicit TimedFleeingMovementGenerator(ObjectGuid fleeTargetGUID, uint32 time) : FleeingMovementGenerator<Creature>(fleeTargetGUID), _totalFleeTime(time) { }

        MovementGeneratorType GetMovementGeneratorType() override { return TIMED_FLEEING_MOTION_TYPE; }

        bool Update(Unit &, const uint32&) override;
        void Finalize(Unit &) override;

    private:
        TimeTracker _totalFleeTime;
};

#endif

