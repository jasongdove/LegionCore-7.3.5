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

#ifndef MOTIONMASTER_H
#define MOTIONMASTER_H

#include "Common.h"
#include "Object.h"
#include "SharedDefines.h"
#include "WaypointManager.h"
#include <LockedVector.h>

class MovementGenerator;
class Unit;
class Spell;
class DelayCastEvent;
class PathGenerator;

namespace Movement
{
    struct SpellEffectExtraData;
}

// Creature Entry ID used for waypoints show, visible only for GMs
#define VISUAL_WAYPOINT 1
// assume it is 25 yard per 0.6 second
#define SPEED_CHARGE    42.0f

// values 0 ... MAX_DB_MOTION_TYPE-1 used in DB
enum MovementGeneratorType
{
    IDLE_MOTION_TYPE                = 0,                   // IdleMovementGenerator.h
    RANDOM_MOTION_TYPE              = 1,                   // RandomMovementGenerator.h
    WAYPOINT_MOTION_TYPE            = 2,                   // WaypointMovementGenerator.h
    MAX_DB_MOTION_TYPE              = 3,                   // Below motion types can't be set in DB.
    ANIMAL_RANDOM_MOTION_TYPE       = MAX_DB_MOTION_TYPE,  // AnimalRandomMovementGenerator.h
    CONFUSED_MOTION_TYPE            = 4,                   // ConfusedMovementGenerator.h
    CHASE_MOTION_TYPE               = 5,                   // TargetedMovementGenerator.h
    HOME_MOTION_TYPE                = 6,                   // HomeMovementGenerator.h
    FLIGHT_MOTION_TYPE              = 7,                   // WaypointMovementGenerator.h
    POINT_MOTION_TYPE               = 8,                   // PointMovementGenerator.h
    FLEEING_MOTION_TYPE             = 9,                   // FleeingMovementGenerator.h
    DISTRACT_MOTION_TYPE            = 10,                  // IdleMovementGenerator.h
    ASSISTANCE_MOTION_TYPE          = 11,                  // PointMovementGenerator.h (first part of flee for assistance)
    ASSISTANCE_DISTRACT_MOTION_TYPE = 12,                  // IdleMovementGenerator.h (second part of flee for assistance)
    TIMED_FLEEING_MOTION_TYPE       = 13,                  // FleeingMovementGenerator.h (alt.second part of flee for assistance)
    FOLLOW_MOTION_TYPE              = 14,
    ROTATE_MOTION_TYPE              = 15,
    EFFECT_MOTION_TYPE              = 16,
    NULL_MOTION_TYPE                = 17,
    SPLINE_CHAIN_MOTION_TYPE        = 18,                  // NYI
    MAX_MOTION_TYPE                                        // limit
};

enum MovementSlot
{
    MOTION_SLOT_IDLE,
    MOTION_SLOT_ACTIVE,
    MOTION_SLOT_CONTROLLED,
    MAX_MOTION_SLOT,
};

enum MMCleanFlag
{
    MMCF_NONE   = 0,
    MMCF_UPDATE = 1, // Clear or Expire called from update
    MMCF_RESET  = 2  // Flag if need top()->Reset()
};

enum RotateDirection
{
    ROTATE_DIRECTION_LEFT,
    ROTATE_DIRECTION_RIGHT,
};

struct JumpArrivalCastArgs
{
    uint32 SpellId;
    ObjectGuid Target;
};

inline bool IsInvalidMovementSlot(uint8 const slot) { return slot >= MAX_MOTION_SLOT; }

class MotionMaster
{
    private:
        typedef std::vector<MovementGenerator*> ExpireList;

    public:
        explicit MotionMaster(Unit* unit) : _expireList(nullptr), _top(-1), _owner(unit), _cleanFlag(MMCF_NONE)
        {
            for (uint8 i = 0; i < MAX_MOTION_SLOT; ++i)
            {
                _slot[i] = nullptr;
                _initialize[i] = true;
            }
        }
        ~MotionMaster();

        bool empty() const { return (_top < 0); }
        int size() const { return _top + 1; }
        MovementGenerator* top() const { ASSERT(!empty()); return _slot[_top]; }

        void Initialize();
        void InitDefault();

        void UpdateMotion(uint32 diff);

        void Clear(bool reset = true);
        void MovementExpired(bool reset = true);

        MovementSlot GetCurrentSlot() const;
        MovementGeneratorType GetCurrentMovementGeneratorType() const;
        MovementGeneratorType GetMotionSlotType(int slot) const;
        MovementGenerator* GetMotionSlot(int slot) const;

        void PropagateSpeedChange();

        bool GetDestination(float &x, float &y, float &z);

        void MoveIdle();
        void MoveTargetedHome();
        void MoveRandom(float spawndist = 0.0f);
        void MoveFollow(Unit* target, float dist, float angle, MovementSlot slot = MOTION_SLOT_ACTIVE);
        void MoveFetch(Unit* target, float dist, float angle, MovementSlot slot = MOTION_SLOT_ACTIVE);
        void MoveChase(Unit* target, float dist = 0.0f, float angle = 0.0f);
        void MoveConfused();
        void MoveFleeing(Unit* enemy, uint32 time = 0);
        void MovePoint(uint32 id, const Position &pos, bool generatePath = true, float speed = 0.0f)
        {
            MovePoint(id, pos.m_positionX, pos.m_positionY, pos.m_positionZ, generatePath, speed);
        }
        void MovePoint(uint32 id, float x, float y, float z, bool generatePath = true, float speed = 0.0f);
        void MovePointWithRot(uint32 id, float x, float y, float z, float orientation = -1000.0f, bool generatePath = true);

        // These two movement types should only be used with creatures having landing/takeoff animations
        void MoveLand(uint32 id, Position const& pos);
        void MoveTakeoff(uint32 id, float x, float y, float z);

        void MoveCharge(float x, float y, float z, float speed = SPEED_CHARGE, uint32 id = EVENT_CHARGE, bool generatePath = false, Unit const* target = nullptr, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        void MoveCharge(PathGenerator const& path, float speed = SPEED_CHARGE, Unit const* target = nullptr, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        void MoveKnockbackFrom(float srcX, float srcY, float speedXY, float speedZ, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        void MoveJumpTo(float angle, float speedXY, float speedZ);
        void MoveJump(Position const& pos, float speedXY, float speedZ, uint32 id = EVENT_JUMP, bool hasOrientation = false, JumpArrivalCastArgs const* arrivalCast = nullptr, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr)
        {
            MoveJump(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), speedXY, speedZ, id, hasOrientation, arrivalCast, spellEffectExtraData);
        }
        void MoveJump(float x, float y, float z, float o, float speedXY, float speedZ, uint32 id = EVENT_JUMP, bool hasOrientation = false, JumpArrivalCastArgs const* arrivalCast = nullptr, Movement::SpellEffectExtraData const* spellEffectExtraData = nullptr);
        void MoveFall(uint32 id = 0);
        void MoveCirclePath(float x, float y, float z, float radius, bool clockwise, uint8 stepCount);
        void MoveSmoothPath(uint32 pointId, G3D::Vector3 const* pathPoints, size_t pathSize, bool walk);
        void MoveSmoothFlyPath(uint32 pointId, G3D::Vector3 const* path, size_t size);
        void MoveSmoothFlyPath(uint32 pointId, Position const position, float flightSpeed = 0.0f);

        void MoveSeekAssistance(float x, float y, float z);
        void MoveSeekAssistanceDistract(uint32 timer);
        void MoveTaxiFlight(uint32 path, uint32 pathnode);
        void MoveDistract(uint32 time);
        void MovePath(uint32 pathId, bool repeatable, float randomMoveX = 0, float randomMoveY = 0);
        void MovePath(WaypointPath& path, bool repeatable);
        void MoveRotate(uint32 time, RotateDirection direction, bool repeat = false);
        void MoveBackward(uint32 id, float x, float y, float z, float speed = 0.0f);

    private:
        void pop();
        bool NeedInitTop() const;
        void InitTop();

        void Mutate(MovementGenerator *m, MovementSlot slot);                  // use Move* functions instead

        void DirectClean(bool reset);
        void DelayedClean();
        void DirectExpire(bool reset);
        void DelayedExpire();
        void DirectDelete(MovementGenerator* curr);
        void DelayedDelete(MovementGenerator* curr);

        ExpireList* _expireList;
        MovementGenerator* _slot[MAX_MOTION_SLOT];
        int _top;
        Unit* _owner;
        bool _initialize[MAX_MOTION_SLOT];
        uint8 _cleanFlag;
};
#endif

