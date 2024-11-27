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

#include "TargetedMovementGenerator.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "Player.h"
#include "Spell.h"
#include "World.h"

template<class T, typename D>
TargetedMovementGenerator<T, D>::~TargetedMovementGenerator()
{
    delete _path;
}

template<class T, typename D>
bool TargetedMovementGenerator<T, D>::DoUpdate(T& owner, uint32 diff)
{
    if (!IsTargetValid() || !GetTarget()->IsInWorld())
        return false;

    if (!owner.IsAlive())
        return false;

    if (owner.HasUnitState(UNIT_STATE_NOT_MOVE) || owner.IsMovementPreventedByCasting() || HasLostTarget(owner)
        || (owner.GetTypeId() == TYPEID_UNIT && owner.ToCreature()->IsFocusing(nullptr)))
    {
        _interrupt = true;
        owner.StopMoving();
        return true;
    }

    if (_interrupt || _recalculateTravel)
    {
        _interrupt = false;
        SetTargetLocation(owner, true);
        return true;
    }

    bool targetMoved = false;
    _timer.Update(diff);
    if (!_interrupt && _timer.Passed())
    {
        _timer.Reset(100);

        float distance = owner.GetCombatReach() + sWorld->getRate(RATE_TARGET_POS_RECALCULATION_RANGE);
        if (owner.isPet() && (owner.GetCharmerOrOwnerGUID() == GetTarget()->GetGUID()))
            distance = 1.f; // pet following owner

        G3D::Vector3 destination = owner.movespline->FinalDestination();
        if (owner.movespline->onTransport)
            if (TransportBase* transport = owner.GetDirectTransport())
                transport->CalculatePassengerPosition(destination.x, destination.y, destination.z);

        // First check distance
        if (owner.GetTypeId() == TYPEID_UNIT && owner.ToCreature()->CanFly())
            targetMoved = !GetTarget()->IsWithinDist3d(destination.x, destination.y, destination.z, distance);
        else
            targetMoved = !GetTarget()->IsWithinDist2d(destination.x, destination.y, distance);

        // then, if the target is in range, check also line of sight
        if (!targetMoved)
            targetMoved = !GetTarget()->IsWithinLOSInMap(&owner);
    }

    if (targetMoved)
        SetTargetLocation(owner, targetMoved);

    if (!_targetReached && owner.movespline->Finalized())
    {
        MovementInform(owner);
        if (_angle == 0.f && !owner.HasInArc(0.01f, GetTarget()))
            owner.SetInFront(GetTarget());

        if (!_targetReached)
        {
            _targetReached = true;
            ReachTarget(owner);
        }
    }

    return true;

//    // prevent movement while casting spells with cast time or channel time
//    if (owner.HasUnitState(UNIT_STATE_CASTING) && !owner.HasUnitState(UNIT_STATE_MOVE_IN_CASTING))
//    {
//        if (!owner.IsStopped())
//        {
//            // some spells should be able to be cast while moving
//            // maybe some attribute? here, check the entry of creatures useing these spells
//            switch(owner.GetEntry())
//            {
//                case 36633: // Ice Sphere (Lich King)
//                case 37562: // Volatile Ooze and Gas Cloud (Putricide)
//                case 37697:
//                    break;
//                default:
//                    owner.StopMoving();
//            }
//        }
//        return true;
//    }
}

template<class T, typename D>
void TargetedMovementGenerator<T, D>::SetTargetLocation(T& owner, bool updateDestination)
{
    if (!IsTargetValid() || !GetTarget()->IsInWorld())
        return;

    if (!owner.IsInWorld() || !owner.IsAlive())
        return;

    if (owner.HasUnitState(UNIT_STATE_NOT_MOVE) || owner.IsMovementPreventedByCasting() || HasLostTarget(owner)
        || (owner.GetTypeId() == TYPEID_UNIT && owner.ToCreature()->IsFocusing(nullptr)))
    {
        _interrupt = true;
        owner.StopMoving();
        return;
    }

    // Hack for Beth'tilac
    switch((&owner)->GetEntry())
    {
        case 52498: // Beth'tilac
            if ((&owner)->GetMapId() == 720)
                if ((&owner)->GetAI()->GetData(2) == 0 && GetTarget()->GetPositionZ() < 100.0f)
                    return;
            break;
        case 52581: // Cinderweb Drone
        case 52447: // Cinderweb Spiderling
        case 53745: // Engorged Broodling
            if ((&owner)->GetMapId() == 720)
                if (GetTarget()->GetPositionZ() > 100.0f)
                    return;
            break;
    }

    if (owner.GetTypeId() == TYPEID_UNIT && !GetTarget()->isInAccessiblePlaceFor(owner.ToCreature()))
    {
        owner.ToCreature()->SetCannotReachTarget(true);
        return;
    }

    float x, y, z;
    if (updateDestination || !_path)
    {
        if (!_offset)
        {
            if (GetTarget()->IsWithinDistInMap(&owner, CONTACT_DISTANCE))
                return;

            GetTarget()->GetContactPoint(&owner, x, y, z);
        }
        else
        {
            float distance = _offset + 1.0f;
            float size = owner.GetCombatReach();

            if (owner.isPet() && GetTarget()->GetTypeId() == TYPEID_PLAYER)
            {
                distance = 1.0f;
                size = 1.0f;
            }

            if (GetTarget()->IsWithinDistInMap(&owner, distance))
                return;

            GetTarget()->GetClosePoint(x, y, z, size, _offset, _angle);
        }
    }
    else
    {
        // the destination has not changed, we just need to refresh the path (usually speed change)
        G3D::Vector3 end = _path->GetEndPosition();
        x = end.x;
        y = end.y;
        z = end.z;
    }

    if (!_path)
        _path = new PathGenerator(&owner);

    // allow pets to use shortcut if no path found when following their master
    bool forceDest = (owner.GetTypeId() == TYPEID_UNIT && owner.ToCreature()->isPet() && owner.HasUnitState(UNIT_STATE_FOLLOW));

    bool result = _path->CalculatePath(x, y, z, forceDest);
    if (!result || (_path->GetPathType() & PATHFIND_NOPATH))
    {
        // can't reach target
        _recalculateTravel = true;
        if (owner.GetTypeId() == TYPEID_UNIT)
            owner.ToCreature()->SetCannotReachTarget(true);
        return;
    }

    _targetReached = false;
    _recalculateTravel = false;

    AddUnitStateMove(owner);

    if (owner.GetTypeId() == TYPEID_UNIT)
        owner.ToCreature()->SetCannotReachTarget(false);

    Movement::MoveSplineInit init(owner);
    init.MovebyPath(_path->GetPath());
    init.SetWalk(EnableWalking());
    // Using the same condition for facing target as the one that is used for SetInFront on movement end
    // - applies to ChaseMovementGenerator mostly
    if (_angle == 0.f)
        init.SetFacing(GetTarget());

    init.Launch();
}

template<class T, typename D>
bool TargetedMovementGenerator<T, D>::IsReachable() const
{
    return (_path) ? (_path->GetPathType() & PATHFIND_NORMAL) : true;
}

//---- ChaseMovementGenerator

template<class T>
void ChaseMovementGenerator<T>::DoInitialize(T&) { }

template<>
void ChaseMovementGenerator<Player>::DoInitialize(Player& owner)
{
    owner.AddUnitState(UNIT_STATE_CHASE);
    SetTargetLocation(owner, true);
}

template<>
void ChaseMovementGenerator<Creature>::DoInitialize(Creature& owner)
{
    owner.SetWalk(false);
    owner.AddUnitState(UNIT_STATE_CHASE);
    SetTargetLocation(owner, true);
}

template<class T>
void ChaseMovementGenerator<T>::DoFinalize(T& owner)
{
    owner.ClearUnitState(UNIT_STATE_CHASE | UNIT_STATE_CHASE_MOVE);
}

template<class T>
void ChaseMovementGenerator<T>::DoReset(T& owner)
{
    DoInitialize(owner);
}

template<class T>
void ChaseMovementGenerator<T>::ClearUnitStateMove(T& owner)
{
    owner.ClearUnitState(UNIT_STATE_CHASE_MOVE);
}

template<class T>
void ChaseMovementGenerator<T>::AddUnitStateMove(T& owner)
{
    owner.AddUnitState(UNIT_STATE_CHASE_MOVE);
}

template<class T>
bool ChaseMovementGenerator<T>::HasLostTarget(T& owner) const
{
    return owner.getVictim() != TargetedMovementGeneratorBase::GetTarget();
}

template<class T>
void ChaseMovementGenerator<T>::ReachTarget(T& owner)
{
    ClearUnitStateMove(owner);

    if (owner.IsWithinMeleeRange(TargetedMovementGeneratorBase::GetTarget()))
        owner.Attack(TargetedMovementGeneratorBase::GetTarget(), true);

    if (owner.GetTypeId() == TYPEID_UNIT)
        owner.ToCreature()->SetCannotReachTarget(false);
}

template<class T>
void ChaseMovementGenerator<T>::MovementInform(T&) { }

template<>
void ChaseMovementGenerator<Creature>::MovementInform(Creature& owner)
{
    // Pass back the GUIDLow of the target. If it is pet's owner then PetAI will handle
    if (owner.AI())
        owner.AI()->MovementInform(CHASE_MOTION_TYPE, GetTarget()->GetGUID().GetCounter());
}

//---- FollowMovementGenerator

template<class T>
void FollowMovementGenerator<T>::UpdateSpeed(T&) { }

template<>
void FollowMovementGenerator<Player>::UpdateSpeed(Player& /*owner*/) { }

template<>
void FollowMovementGenerator<Creature>::UpdateSpeed(Creature& owner)
{
    // Pet only sync speed with owner
    // Make sure we are not in the process of a map change (IsInWorld)
    if (!owner.isPet() || !owner.IsInWorld() || !IsTargetValid() || GetTarget()->GetGUID() != owner.GetOwnerGUID())
        return;

    owner.UpdateSpeed(MOVE_RUN, true);
    owner.UpdateSpeed(MOVE_WALK, true);
    owner.UpdateSpeed(MOVE_SWIM, true);
}

template<class T>
void FollowMovementGenerator<T>::DoInitialize(T& owner)
{
    _path = nullptr;
    _lastTargetPosition.reset();

    owner.AddUnitState(UNIT_STATE_FOLLOW);
    UpdateSpeed(owner);
    TargetedMovementGenerator<T, FollowMovementGenerator<T>>::SetTargetLocation(owner, true);
}

template<class T>
void FollowMovementGenerator<T>::DoFinalize(T& owner)
{
    owner.ClearUnitState(UNIT_STATE_FOLLOW | UNIT_STATE_FOLLOW_MOVE);
    UpdateSpeed(owner);
}

template<class T>
void FollowMovementGenerator<T>::DoReset(T& owner)
{
    DoInitialize(owner);
}

template<class T>
void FollowMovementGenerator<T>::ClearUnitStateMove(T& owner)
{
    owner.ClearUnitState(UNIT_STATE_FOLLOW_MOVE);
}

template<class T>
void FollowMovementGenerator<T>::AddUnitStateMove(T& owner)
{
    owner.AddUnitState(UNIT_STATE_FOLLOW_MOVE);
}

template<class T>
void FollowMovementGenerator<T>::ReachTarget(T& owner)
{
    ClearUnitStateMove(owner);
}

template<>
bool FollowMovementGenerator<Creature>::EnableWalking() const
{
    return IsTargetValid() && GetTarget()->IsWalking();
}

template<>
bool FollowMovementGenerator<Player>::EnableWalking() const
{
    return false;
}

template<class T>
void FollowMovementGenerator<T>::MovementInform(T&) { }

template<>
void FollowMovementGenerator<Player>::MovementInform(Player&) { }

template<>
void FollowMovementGenerator<Creature>::MovementInform(Creature& owner)
{
    if (owner.GetTypeId() != TYPEID_UNIT)
        return;

    // Pass back the GUIDLow of the target. If it is pet's owner then PetAI will handle
    if (owner.AI())
        owner.AI()->MovementInform(FOLLOW_MOTION_TYPE, GetTarget()->GetGUID().GetCounter());
}

static Optional<float> GetVelocity(Unit* owner, Unit* target, G3D::Vector3 const& dest, bool playerPet)
{
    Optional<float> speed = {};
    if (!owner->isInCombat() && !owner->IsVehicle() && !owner->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED) &&
        (owner->isPet() || owner->isGuardian() || owner->GetGUID() == target->GetCritterGUID() || owner->GetCharmerOrOwnerGUID() == target->GetGUID()))
    {
        uint32 moveFlags = target->GetUnitMovementFlags();
        if (target->movespline->isWalking())
        {
            moveFlags |= MOVEMENTFLAG_WALKING;
        }

        UnitMoveType moveType = (UnitMoveType)Movement::SelectSpeedType(moveFlags);
        speed = target->GetSpeed(moveType);
        if (playerPet)
        {
            float distance = owner->GetDistance2d(dest.x, dest.y) - target->GetObjectSize() - (*speed / 2.f);
            if (distance > 0.f)
            {
                float multiplier = 1.f + (distance / 10.f);
                *speed *= multiplier;
            }
        }
    }

    return speed;
}

static Position const PredictPosition(Unit* target)
{
    Position pos = target->GetPosition();

    // 0.5 - it's time (0.5 sec) between starting movement opcode (e.g. MSG_MOVE_START_FORWARD) and MSG_MOVE_HEARTBEAT sent by client
    float speed = target->GetSpeed((UnitMoveType)Movement::SelectSpeedType(target->GetUnitMovementFlags())) * 0.5f;
    float orientation = target->GetOrientation();

    if (target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_FORWARD))
    {
        pos.m_positionX += cos(orientation) * speed;
        pos.m_positionY += std::sin(orientation) * speed;
    }
    else if (target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_BACKWARD))
    {
        pos.m_positionX -= cos(orientation) * speed;
        pos.m_positionY -= std::sin(orientation) * speed;
    }

    if (target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_STRAFE_LEFT))
    {
        pos.m_positionX += cos(orientation + M_PI / 2.f) * speed;
        pos.m_positionY += std::sin(orientation + M_PI / 2.f) * speed;
    }
    else if (target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_STRAFE_RIGHT))
    {
        pos.m_positionX += cos(orientation - M_PI / 2.f) * speed;
        pos.m_positionY += std::sin(orientation - M_PI / 2.f) * speed;
    }

    return pos;
}

template<class T>
bool FollowMovementGenerator<T>::DoUpdate(T&, uint32) { return false; }

template<>
bool FollowMovementGenerator<Player>::DoUpdate(Player& owner, uint32 diff) { return false; }

template<>
bool FollowMovementGenerator<Creature>::DoUpdate(Creature& owner, uint32 diff)
{
    if (!GetTarget())
        return false;

    if (!GetTarget()->IsInWorld() || !owner.IsInMap(GetTarget()))
        return false;

    if (!owner.ToCreature() || !owner.IsAlive())
        return false;

    Creature* cOwner = owner.ToCreature();
    Unit* target = GetTarget();

    // the owner might be unable to move (rooted or casting), or we have lost the target, pause movement
    if (owner.HasUnitState(UNIT_STATE_NOT_MOVE) || (cOwner && cOwner->IsMovementPreventedByCasting()))
    {
        _path = nullptr;
        owner.StopMoving();
        _lastTargetPosition.reset();
        return true;
    }

    bool followingMaster = false;
    Pet* oPet = owner.ToPet();
    if (oPet)
    {
        if (target->GetGUID() == oPet->GetOwnerGUID())
            followingMaster = true;
    }

    bool forceDest =
        (followingMaster) || // allow pets following their master to cheat while generating paths
        (GetTarget()->GetTypeId() == TYPEID_PLAYER && GetTarget()->ToPlayer()->isGameMaster()) // for .npc follow
        ; // closes "bool forceDest", that way it is more appropriate, so we can comment out crap whenever we need to

    bool targetIsMoving = false;
    if (PositionOkay(target, owner.isGuardian() && target->GetTypeId() == TYPEID_PLAYER, targetIsMoving, diff))
    {
        if (owner.HasUnitState(UNIT_STATE_FOLLOW_MOVE) && owner.movespline->Finalized())
        {
            owner.ClearUnitState(UNIT_STATE_FOLLOW_MOVE);
            _path = nullptr;
            MovementInform(owner);

            if (_recheckPredictedDistance)
            {
                _recheckPredictedDistanceTimer.Reset(1000);
            }

            owner.SetFacingTo(target->GetOrientation());
        }
    }
    else
    {
        Position targetPosition = target->GetPosition();
        _lastTargetPosition = targetPosition;

        // If player is moving and their position is not updated, we need to predict position
        if (targetIsMoving)
        {
            Position predictedPosition = PredictPosition(target);
            if (_lastPredictedPosition && _lastPredictedPosition->GetExactDistSq(&predictedPosition) < 0.25f)
                return true;

            _lastPredictedPosition = predictedPosition;
            targetPosition = predictedPosition;
            _recheckPredictedDistance = true;
        }
        else
        {
            _recheckPredictedDistance = false;
            _recheckPredictedDistanceTimer.Reset(0);
        }

        if (!_path)
            _path = std::make_unique<PathGenerator>(&owner);
        else
            _path->Clear();

        target->MovePositionToFirstCollision(targetPosition, owner.GetCombatReach() + _range, target->ToAbsoluteAngle(Position::NormalizeOrientation(_range)) - target->GetOrientation());

        float x, y, z;
        targetPosition.GetPosition(x, y, z);

        //if (owner->IsHovering())
        if (owner.m_movementInfo.HasMovementFlag(MOVEMENTFLAG_HOVER)) // alt: owner.isHover()
            owner.UpdateAllowedPositionZ(x, y, z);

        bool success = _path->CalculatePath(x, y, z, forceDest);
        if (!success || (_path->GetPathType() & PATHFIND_NOPATH && !followingMaster))
        {
            if (!owner.IsStopped())
                owner.StopMoving();

            return true;
        }

        owner.AddUnitState(UNIT_STATE_FOLLOW_MOVE);

        Movement::MoveSplineInit init(*owner.ToUnit());
        init.MovebyPath(_path->GetPath());
        if (_inheritWalkState)
            init.SetWalk(target->IsWalking() || target->movespline->isWalking());

        if (Optional<float> velocity = GetVelocity(owner.ToUnit(), target, _path->GetActualEndPosition(), owner.isGuardian()))
            init.SetVelocity(*velocity);
        init.Launch();
    }

    return true;
}

template<class T>
bool FollowMovementGenerator<T>::PositionOkay(Unit* target, bool isPlayerPet, bool& targetIsMoving, uint32 diff)
{
    if (!_lastTargetPosition)
        return false;

    float exactDistSq = target->GetExactDistSq(_lastTargetPosition->GetPositionX(), _lastTargetPosition->GetPositionY(), _lastTargetPosition->GetPositionZ());
    float distanceTolerance = 0.25f;
    // For creatures, increase tolerance
    if (target->GetTypeId() == TYPEID_UNIT)
    {
        distanceTolerance += _range + _range;
    }

    if (isPlayerPet)
    {
        targetIsMoving = target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_BACKWARD | MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT);
    }

    if (exactDistSq > distanceTolerance)
        return false;

    if (isPlayerPet)
    {
        if (!targetIsMoving)
        {
            if (_recheckPredictedDistanceTimer.GetExpiry())
            {
                _recheckPredictedDistanceTimer.Update(diff);
                if (_recheckPredictedDistanceTimer.Passed())
                {
                    _recheckPredictedDistanceTimer = (TimeTrackerSmall)0;
                    return false;
                }
            }

            return true;
        }

        return false;
    }

    return true;
}

//-----------------------------------------------//

template<class T>
void FetchMovementGenerator<T>::DoInitialize(T&) { }

template<>
void FetchMovementGenerator<Player>::DoInitialize(Player&) { }

template<>
void FetchMovementGenerator<Creature>::DoInitialize(Creature& owner)
{
    owner.SetWalk(false);
    owner.AddUnitState(UNIT_STATE_CHASE | UNIT_STATE_CHASE_MOVE);
    SetTargetLocation(owner, true);
}

template<class T>
void FetchMovementGenerator<T>::DoFinalize(T& owner)
{
    owner.ClearUnitState(UNIT_STATE_CHASE | UNIT_STATE_CHASE_MOVE);
}

template<class T>
void FetchMovementGenerator<T>::DoReset(T& owner)
{
    DoInitialize(owner);
}

template<class T>
void FetchMovementGenerator<T>::ClearUnitStateMove(T& owner)
{
    owner.ClearUnitState(UNIT_STATE_CHASE_MOVE);
}

template<class T>
void FetchMovementGenerator<T>::AddUnitStateMove(T& owner)
{
    owner.AddUnitState(UNIT_STATE_CHASE_MOVE);
}

template<class T>
void FetchMovementGenerator<T>::MovementInform(T& /*unit*/)
{
}

template<>
void FetchMovementGenerator<Creature>::MovementInform(Creature& unit)
{
    if(Unit* _petowner = unit.GetOwner())
    {
        if (Player* _player = _petowner->ToPlayer())
        {
            if(Pet* pet = _player->GetPet())
            {
                _player->GetSession()->LootCorps(GetTarget()->GetGUID(), pet);
                pet->CastSpell(GetTarget(), 125056, false);

                pet->AttackStop();
                pet->InterruptNonMeleeSpells(false);
                pet->GetMotionMaster()->Clear(false);
                //pet->GetMotionMaster()->MoveFollow(_petowner, PET_FOLLOW_DIST, pet->GetFollowAngle());
                //if (CharmInfo* charmInfo = pet->GetCharmInfo())
                //{
                //    charmInfo->SetCommandState(COMMAND_FOLLOW);
                //    charmInfo->SetIsCommandAttack(false);
                //    charmInfo->SetIsAtStay(false);
                //    charmInfo->SetIsReturning(true);
                //    charmInfo->SetIsFollowing(false);
                //}
            }
        }
    }
    // Pass back the GUIDLow of the target. If it is pet's owner then PetAI will handle
    if (unit.AI())
        unit.AI()->MovementInform(CHASE_MOTION_TYPE, GetTarget()->GetGUIDLow());
}

//-----------------------------------------------//

template TargetedMovementGenerator<Player, ChaseMovementGenerator<Player>>::~TargetedMovementGenerator();
template TargetedMovementGenerator<Player, FollowMovementGenerator<Player>>::~TargetedMovementGenerator();
template TargetedMovementGenerator<Player, FetchMovementGenerator<Player>>::~TargetedMovementGenerator();
template TargetedMovementGenerator<Creature, ChaseMovementGenerator<Creature>>::~TargetedMovementGenerator();
template TargetedMovementGenerator<Creature, FollowMovementGenerator<Creature>>::~TargetedMovementGenerator();
template TargetedMovementGenerator<Creature, FetchMovementGenerator<Creature>>::~TargetedMovementGenerator();
template bool TargetedMovementGenerator<Player, ChaseMovementGenerator<Player>>::DoUpdate(Player&, uint32);
template bool TargetedMovementGenerator<Player, FollowMovementGenerator<Player>>::DoUpdate(Player&, uint32);
template bool TargetedMovementGenerator<Player, FetchMovementGenerator<Player>>::DoUpdate(Player&, uint32);
template bool TargetedMovementGenerator<Creature, ChaseMovementGenerator<Creature>>::DoUpdate(Creature&, uint32);
template bool TargetedMovementGenerator<Creature, FollowMovementGenerator<Creature>>::DoUpdate(Creature&, uint32);
template bool TargetedMovementGenerator<Creature, FetchMovementGenerator<Creature>>::DoUpdate(Creature&, uint32);
template void TargetedMovementGenerator<Player, ChaseMovementGenerator<Player>>::SetTargetLocation(Player&, bool);
template void TargetedMovementGenerator<Player, FollowMovementGenerator<Player>>::SetTargetLocation(Player&, bool);
template void TargetedMovementGenerator<Creature, ChaseMovementGenerator<Creature>>::SetTargetLocation(Creature&, bool);
template void TargetedMovementGenerator<Creature, FollowMovementGenerator<Creature>>::SetTargetLocation(Creature&, bool);

template void ChaseMovementGenerator<Player>::DoFinalize(Player&);
template void ChaseMovementGenerator<Creature>::DoFinalize(Creature&);
template void ChaseMovementGenerator<Player>::DoReset(Player&);
template void ChaseMovementGenerator<Creature>::DoReset(Creature&);
template void ChaseMovementGenerator<Player>::ClearUnitStateMove(Player&);
template void ChaseMovementGenerator<Creature>::ClearUnitStateMove(Creature&);
template void ChaseMovementGenerator<Player>::AddUnitStateMove(Player&);
template void ChaseMovementGenerator<Creature>::AddUnitStateMove(Creature&);
template bool ChaseMovementGenerator<Player>::HasLostTarget(Player&) const;
template bool ChaseMovementGenerator<Creature>::HasLostTarget(Creature&) const;
template void ChaseMovementGenerator<Player>::ReachTarget(Player&);
template void ChaseMovementGenerator<Creature>::ReachTarget(Creature&);
template void ChaseMovementGenerator<Player>::MovementInform(Player&);

template void FetchMovementGenerator<Player>::ClearUnitStateMove(Player&);
template void FetchMovementGenerator<Creature>::ClearUnitStateMove(Creature&);
template void FetchMovementGenerator<Player>::AddUnitStateMove(Player&);
template void FetchMovementGenerator<Creature>::AddUnitStateMove(Creature&);
template void FetchMovementGenerator<Player>::DoFinalize(Player&);
template void FetchMovementGenerator<Creature>::DoFinalize(Creature&);
template void FetchMovementGenerator<Player>::DoReset(Player&);
template void FetchMovementGenerator<Creature>::DoReset(Creature&);

template void FollowMovementGenerator<Player>::DoInitialize(Player&);
template void FollowMovementGenerator<Creature>::DoInitialize(Creature&);
template void FollowMovementGenerator<Player>::DoFinalize(Player&);
template void FollowMovementGenerator<Creature>::DoFinalize(Creature&);
template void FollowMovementGenerator<Player>::DoReset(Player&);
template void FollowMovementGenerator<Creature>::DoReset(Creature&);
template void FollowMovementGenerator<Player>::ClearUnitStateMove(Player&);
template void FollowMovementGenerator<Creature>::ClearUnitStateMove(Creature&);
template void FollowMovementGenerator<Player>::AddUnitStateMove(Player&);
template void FollowMovementGenerator<Creature>::AddUnitStateMove(Creature&);
template void FollowMovementGenerator<Player>::ReachTarget(Player&);
template void FollowMovementGenerator<Creature>::ReachTarget(Creature&);
