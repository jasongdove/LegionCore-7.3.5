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
#include "World.h"
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "Player.h"
#include "Spell.h"

#define RECHECK_DISTANCE_TIMER 200
#define TARGET_NOT_ACCESSIBLE_MAX_TIMER 5000

template<class T, typename D>
void TargetedMovementGeneratorMedium<T,D>::_setTargetLocation(T &owner)
{
    if (!i_target.isValid() || !i_target->IsInWorld() || !owner.IsInWorld())
        return;

    if (owner.HasUnitState(UNIT_STATE_NOT_MOVE))
        return;

    // Hack for Beth'tilac
    switch((&owner)->GetEntry())
    {
        case 52498: // Beth'tilac
            if ((&owner)->GetMapId() == 720)
                if ((&owner)->GetAI()->GetData(2) == 0 && i_target->GetPositionZ() < 100.0f)
                    return;
            break;
        case 52581: // Cinderweb Drone
        case 52447: // Cinderweb Spiderling
        case 53745: // Engorged Broodling
            if ((&owner)->GetMapId() == 720)
                if (i_target->GetPositionZ() > 100.0f)
                    return;
            break;
    }

    if (owner.IsCreature() && !i_target->isInAccessiblePlaceFor(((Creature*)&owner)))
        return;

    float x, y, z;
    float distance = i_offset ? i_offset : ((Creature*)&owner)->GetAttackDist() - 0.5f;
    float realDistance = i_target->GetDistance(&owner);
    if(distance > realDistance)
        distance = realDistance;

    float angle = i_angle ? i_angle : 360.0f;

    if(static_cast<D*>(this)->GetMovementGeneratorType() == FOLLOW_MOTION_TYPE)
    {
        i_target->GetNearPoint(&owner, x, y, z, CONTACT_DISTANCE, distance, i_target->GetOrientation() + angle);

        bool searchLos = false;
        float deltaZ = z > i_target->GetPositionZ() ? z - i_target->GetPositionZ() : i_target->GetPositionZ() - z;
        if (deltaZ > 2.0f)
            searchLos = true;

        if(owner.GetTransport() || searchLos || !i_target->IsWithinLOS(x, y, z))
        {
            if (distance < PET_FOLLOW_DIST)
                distance = PET_FOLLOW_DIST;

            Position pos;
            i_target->GetFirstCollisionPosition(pos, distance, angle);
            x = pos.m_positionX;
            y = pos.m_positionY;
            z = pos.m_positionZ;
        }
        // TC_LOG_DEBUG("misc", "_setTargetLocation FOLLOW_MOTION_TYPE %u IsWithinLOSInMap (%f %f %f) GetAttackDist %f", owner.GetEntry(), x, y , z, ((Creature*)&owner)->GetAttackDist());
    }
    else
    {
        if(owner.IsCreature() && ((Creature*)&owner)->isPet() && !i_target->IsWithinLOSInMap(&owner))
        {
            Position pos;
            i_target->GetFirstCollisionPosition(pos, distance, angle);
            x = pos.m_positionX;
            y = pos.m_positionY;
            z = pos.m_positionZ;
        }
        else
            i_target->GetContactPoint(&owner, x, y, z, distance);
        // TC_LOG_DEBUG("misc", "_setTargetLocation %u IsWithinLOSInMap (%f %f %f) GetAttackDist %f", owner.GetEntry(), x, y , z, ((Creature*)&owner)->GetAttackDist());
    }

    if (!i_path)
        i_path = new PathGenerator(&owner);

    // allow pets following their master to cheat while generating paths
    bool forceDest = false;
    if (Creature* c = owner.ToCreature())
        forceDest |= c->isWorldBoss() || c->IsDungeonBoss();

    i_path->CalculatePath(x, y, z, forceDest);

    if (i_path->GetPathType() & PATHFIND_NOPATH && (owner.IsCreature() && ((Creature*)&owner)->isPet() && owner.HasUnitState(UNIT_STATE_FOLLOW)))
    {
        if (!i_target->IsWithinLOSInMap(&owner))
        {
            owner.NearTeleportTo(x, y, z, owner.GetOrientation());
            return;
        }
        // When patch can't run to target?
    }

    D::_addUnitStateMove(owner);
    i_targetReached = false;
    i_recalculateTravel = false;

    Movement::MoveSplineInit init(owner);
    if (owner.GetTransport())
        init.DisableTransportPathTransformations();

    if (i_path->GetPathType() & PATHFIND_NOPATH)
        init.MoveTo(x,y,z);
    else
        init.MovebyPath(i_path->GetPath());
    init.SetWalk(((D*)this)->EnableWalking());
    init.Launch();
}

template<>
void TargetedMovementGeneratorMedium<Player,ChaseMovementGenerator<Player> >::UpdateFinalDistance(float /*fDistance*/)
{
    // nothing to do for Player
}

template<>
void TargetedMovementGeneratorMedium<Player,FollowMovementGenerator<Player> >::UpdateFinalDistance(float /*fDistance*/)
{
    // nothing to do for Player
}

template<>
void TargetedMovementGeneratorMedium<Creature,ChaseMovementGenerator<Creature> >::UpdateFinalDistance(float fDistance)
{
    i_offset = fDistance;
    i_recalculateTravel = true;
}

template<>
void TargetedMovementGeneratorMedium<Creature,FetchMovementGenerator<Creature> >::UpdateFinalDistance(float fDistance)
{
    i_offset = fDistance;
    i_recalculateTravel = true;
}

template<>
void TargetedMovementGeneratorMedium<Creature,FollowMovementGenerator<Creature> >::UpdateFinalDistance(float fDistance)
{
    i_offset = fDistance;
    i_recalculateTravel = true;

    //TC_LOG_DEBUG("misc", "FollowMovementGenerator UpdateFinalDistance");
}

template<class T, typename D>
bool TargetedMovementGeneratorMedium<T,D>::DoUpdate(T &owner, const uint32 & time_diff)
{
    if (!i_target.isValid() || !i_target->IsInWorld())
    {
        if (i_targetSearchingTimer >= TARGET_NOT_ACCESSIBLE_MAX_TIMER)
            return false;
        i_targetSearchingTimer += time_diff;
        return true;
    }

    if (!owner.isAlive() || !i_target->isAlive())
        return false;

    if (owner.HasUnitState(UNIT_STATE_NOT_MOVE))
    {
        D::_clearUnitStateMove(owner);
        return true;
    }

    // prevent movement while casting spells with cast time or channel time
    if (owner.HasUnitState(UNIT_STATE_CASTING) && !owner.HasUnitState(UNIT_STATE_MOVE_IN_CASTING))
    {
        if (!owner.IsStopped())
        {
            // some spells should be able to be cast while moving
            // maybe some attribute? here, check the entry of creatures useing these spells
            switch(owner.GetEntry())
            {
                case 36633: // Ice Sphere (Lich King)
                case 37562: // Volatile Ooze and Gas Cloud (Putricide)
                case 37697:
                    break;
                default:
                    owner.StopMoving();
            }
        }
        return true;
    }

    // prevent crash after creature killed pet
    if (static_cast<D*>(this)->_lostTarget(owner))
    {
        D::_clearUnitStateMove(owner);
        if (i_targetSearchingTimer >= TARGET_NOT_ACCESSIBLE_MAX_TIMER)
            return false;
        i_targetSearchingTimer += time_diff;
        return true;
    }

    i_recheckDistance.Update(time_diff);
    if (i_recheckDistance.Passed())
    {
        i_recheckDistance.Reset(RECHECK_DISTANCE_TIMER);

        G3D::Vector3 dest = owner.movespline->FinalDestination();
        if (Transport* transport = owner.GetTransport())
            transport->CalculatePassengerPosition(dest.x, dest.y, dest.z);

        float allowed_dist = 0.0f;
        bool targetIsVictim = owner.getVictim() && owner.getVictim()->GetGUID() == i_target->GetGUID();
        if (((Creature*)&owner)->isPet())
            allowed_dist = sWorld->getRate(RATE_TARGET_POS_RECALCULATION_RANGE);
        else if (targetIsVictim)
            allowed_dist = owner.GetMeleeReach() + owner.getVictim()->GetMeleeReach()/* + owner.getVictim()->GetObjectSize()*/;
        else
            allowed_dist = i_target->GetObjectSize() + sWorld->getRate(RATE_TARGET_POS_RECALCULATION_RANGE);

        if (allowed_dist < owner.GetObjectSize())
            allowed_dist = owner.GetObjectSize();

        bool targetMoved = false;

        if(static_cast<D*>(this)->GetMovementGeneratorType() == FOLLOW_MOTION_TYPE)
        {
            allowed_dist = sWorld->getRate(RATE_TARGET_POS_RECALCULATION_RANGE);
            if (owner.IsCreature() && ((Creature*)&owner)->IsFlying())
                targetMoved = !i_target->IsWithinDist3d(dest.x, dest.y, dest.z, allowed_dist);
            else
                targetMoved = !i_target->IsWithinDist2d(dest.x, dest.y, allowed_dist);
        }
        else
        {
            if (owner.IsCreature() && ((Creature*)&owner)->IsFlying())
                targetMoved = !i_target->IsWithinDist3d(dest.x, dest.y, dest.z, allowed_dist);
            else
                targetMoved = !i_target->IsWithinDist2d(dest.x, dest.y, allowed_dist);
        }

        if (targetIsVictim && owner.IsCreature() && !((Creature*)&owner)->isPet())
        {
            if ((!owner.getVictim() || !owner.getVictim()->isAlive()) && owner.movespline->Finalized())
                return false;

            if (!i_offset && owner.movespline->Finalized() && !owner.IsWithinMeleeRange(owner.getVictim())
                && !i_target->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_PENDING_STOP))
            {
                if (i_targetSearchingTimer >= TARGET_NOT_ACCESSIBLE_MAX_TIMER)
                {
                    owner.DeleteFromThreatList(owner.getVictim());
                    return false;
                }
                i_targetSearchingTimer += time_diff;
                targetMoved = true;
            }
            else
                i_targetSearchingTimer = 0;
        }
        else
            i_targetSearchingTimer = 0;

        if (targetMoved || (owner.movespline->Finalized() && !i_target->IsWithinLOSInMap(&owner)))
        {
            //TC_LOG_DEBUG("misc", "DoUpdate Pet %u targetMoved %i search %i Finalized %i i_recalculateTravel %i allowed_dist %f Type %i",
            //owner.GetEntry(), targetMoved, i_targetSearchingTimer, owner.movespline->Finalized(), i_recalculateTravel, allowed_dist, static_cast<D*>(this)->GetMovementGeneratorType());

            _updateSpeed(owner);
            _setTargetLocation(owner);
        }
    }

    if (owner.movespline->Finalized())
    {
        static_cast<D*>(this)->MovementInform(owner);
        if (i_angle == 0.f && !owner.HasInArc(0.01f, i_target.getTarget()))
            owner.SetInFront(i_target.getTarget());

        if (!i_targetReached)
        {
            i_targetReached = true;
            static_cast<D*>(this)->_reachTarget(owner);
        }
    }
    else
    {
        if (i_recalculateTravel)
        {
            //TC_LOG_DEBUG("misc", "DoUpdate i_recalculateTravel");
            _setTargetLocation(owner);
        }
    }
    return true;
}

//-----------------------------------------------//
template<class T>
void ChaseMovementGenerator<T>::_reachTarget(T &owner)
{
    if (owner.IsWithinMeleeRange(this->i_target.getTarget()))
        owner.Attack(this->i_target.getTarget(), true);
}

template<>
void ChaseMovementGenerator<Player>::DoInitialize(Player &owner)
{
    //TC_LOG_DEBUG("misc", "ChaseMovementGenerator DoInitialize Player");
    owner.AddUnitState(UNIT_STATE_CHASE | UNIT_STATE_CHASE_MOVE);
    _setTargetLocation(owner);
}

template<>
void ChaseMovementGenerator<Creature>::DoInitialize(Creature &owner)
{
    //TC_LOG_DEBUG("misc", "ChaseMovementGenerator DoInitialize i_target %u, owner %u", i_target.getTarget()->GetGUIDLow(), owner.GetGUIDLow());
    owner.SetWalk(false);
    owner.AddUnitState(UNIT_STATE_CHASE | UNIT_STATE_CHASE_MOVE);
    _setTargetLocation(owner);
}

template<class T>
void ChaseMovementGenerator<T>::DoFinalize(T &owner)
{
    owner.ClearUnitState(UNIT_STATE_CHASE | UNIT_STATE_CHASE_MOVE);
    if (owner.IsCreature() && !((Creature*)&owner)->isPet() && owner.isAlive())
    {
        if (!owner.isInCombat() || ( this->i_target.getTarget() && !this->i_target.getTarget()->isInAccessiblePlaceFor(((Creature*)&owner))))
        {
            if (owner.isInCombat())
                owner.CombatStop(true);

            owner.GetMotionMaster()->MoveTargetedHome();
        }
    }
}

template<class T>
void ChaseMovementGenerator<T>::DoReset(T &owner)
{
    DoInitialize(owner);
}

template<class T>
void ChaseMovementGenerator<T>::MovementInform(T & /*unit*/)
{
}

template<>
void ChaseMovementGenerator<Creature>::MovementInform(Creature &unit)
{
    // Pass back the GUIDLow of the target. If it is pet's owner then PetAI will handle
    if (unit.AI())
        unit.AI()->MovementInform(CHASE_MOTION_TYPE, i_target.getTarget()->GetGUIDLow());
}

//-----------------------------------------------//
template<class T>
void FetchMovementGenerator<T>::_reachTarget(T &owner)
{
    //TC_LOG_DEBUG("network", "FetchMovementGenerator _reachTarget i_target %u, owner %u", this->i_target.getTarget()->GetGUIDLow(), owner.GetGUIDLow());
}

template<>
void FetchMovementGenerator<Creature>::DoInitialize(Creature &owner)
{
    owner.SetWalk(false);
    owner.AddUnitState(UNIT_STATE_CHASE|UNIT_STATE_CHASE_MOVE);
    _setTargetLocation(owner);
    //TC_LOG_DEBUG("network", "FetchMovementGenerator Initialize i_target %u, owner %u", i_target.getTarget()->GetGUIDLow(), owner.GetGUIDLow());
}

template<class T>
void FetchMovementGenerator<T>::DoFinalize(T &owner)
{
    //TC_LOG_DEBUG("network", "FetchMovementGenerator Finalize i_target %u, owner %u", this->i_target.getTarget()->GetGUIDLow(), owner.GetGUIDLow());
    owner.ClearUnitState(UNIT_STATE_CHASE|UNIT_STATE_CHASE_MOVE);
}

template<class T>
void FetchMovementGenerator<T>::DoReset(T &owner)
{
    //TC_LOG_DEBUG("network", "FetchMovementGenerator Reset i_target %u, owner %u", this->i_target.getTarget()->GetGUIDLow(), owner.GetGUIDLow());
    DoInitialize(owner);
}

template<class T>
void FetchMovementGenerator<T>::MovementInform(T & /*unit*/)
{
}

template<>
void FetchMovementGenerator<Creature>::MovementInform(Creature &unit)
{
    if(Unit* _petowner = unit.GetOwner())
    {
        if (Player* _player = _petowner->ToPlayer())
        {
            if(Pet* pet = _player->GetPet())
            {
                _player->GetSession()->LootCorps(i_target.getTarget()->GetGUID(), pet);
                pet->CastSpell(i_target.getTarget(), 125056, false);

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
        unit.AI()->MovementInform(CHASE_MOTION_TYPE, i_target.getTarget()->GetGUIDLow());
}

//-----------------------------------------------//
template<>
bool FollowMovementGenerator<Creature>::EnableWalking() const
{
    return i_target.isValid() && i_target->IsWalking();
}

template<>
bool FollowMovementGenerator<Player>::EnableWalking() const
{
    return false;
}

template<class T, typename D>
void TargetedMovementGeneratorMedium<T,D>::_updateSpeed(T &u)
{
    // pet only sync speed with owner
    if (!((Creature&)u).isPet() || !i_target.isValid() || i_target->GetGUID() != u.GetOwnerGUID())
        return;

    //TC_LOG_DEBUG("misc", "FollowMovementGenerator _updateSpeed i_target %u, owner %u", i_target.getTarget()->GetGUIDLow(), u.GetGUIDLow());

    u.UpdateSpeed(MOVE_RUN,true);
    u.UpdateSpeed(MOVE_WALK,true);
    u.UpdateSpeed(MOVE_SWIM,true);
}

//-----------------------------------------------//
template<class T>
void FollowMovementGenerator<T>::DoInitialize(T& owner)
{
    i_path = nullptr;
    _lastTargetPosition.reset();
    owner.AddUnitState(UNIT_STATE_FOLLOW);

    //TC_LOG_DEBUG("misc", "FollowMovementGenerator DoInitialize i_target %u, owner %u", i_target.getTarget()->GetGUIDLow(), owner.GetGUIDLow());
}

template<class T>
void FollowMovementGenerator<T>::DoFinalize(T& owner)
{
    owner.ClearUnitState(UNIT_STATE_FOLLOW | UNIT_STATE_FOLLOW_MOVE);

    //TC_LOG_DEBUG("misc", "FollowMovementGenerator DoFinalize owner %u", owner.GetGUIDLow());
}

template<class T>
void FollowMovementGenerator<T>::DoReset(T &owner)
{
    //TC_LOG_DEBUG("misc", "FollowMovementGenerator DoReset owner %u", owner.GetGUIDLow());
    DoInitialize(owner);
}

template<class T>
void FollowMovementGenerator<T>::MovementInform(T& owner)
{
    if (owner.GetTypeId() != TYPEID_UNIT)
        return;

    // Pass back the GUIDLow of the target. If it is pet's owner then PetAI will handle
    if (CreatureAI* AI = owner.ToCreature()->AI())
        AI->MovementInform(FOLLOW_MOTION_TYPE, this->i_target.getTarget()->GetGUID().GetCounter());
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

bool IsMovementPreventedByCasting(Creature* owner)
{
    Spell* spell = owner->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
    // first check if currently a movement allowed channel is active and we're not casting
    if (spell && spell->getState() != SPELL_STATE_FINISHED && spell->IsChannelActive() &&
        (spell->GetSpellInfo() && spell->GetSpellInfo()->IsChanneled() && spell->GetSpellInfo()->HasAttribute(SPELL_ATTR5_USABLE_WHILE_MOVING))
        )
    {
        return false;
    }

    /*if (owner->HasSpellFocus())
    {
        return true;
    }*/

    if (owner->HasUnitState(UNIT_STATE_CASTING))
    {
        return true;
    }

    return false;
}

template<class T>
bool FollowMovementGenerator<T>::DoUpdate(T& owner, uint32 time_diff)
{
    if (!this->i_target.isValid() || !this->i_target->IsInWorld() || !owner.IsInMap(this->i_target.getTarget()))
        return false;

    if (!owner.ToCreature() || !owner.isAlive())
        return false;

    Creature* cOwner = owner.ToCreature();
    Unit* target = this->i_target.getTarget();

    // the owner might be unable to move (rooted or casting), or we have lost the target, pause movement
    if (owner.HasUnitState(UNIT_STATE_NOT_MOVE) || (cOwner && IsMovementPreventedByCasting(owner.ToCreature())))
    {
        i_path = nullptr;
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
        (this->i_target->GetTypeId() == TYPEID_PLAYER && this->i_target->ToPlayer()->isGameMaster()) // for .npc follow
        ; // closes "bool forceDest", that way it is more appropriate, so we can comment out crap whenever we need to

    bool targetIsMoving = false;
    if (PositionOkay(target, owner.isGuardian() && target->GetTypeId() == TYPEID_PLAYER, targetIsMoving, time_diff))
    {
        if (owner.HasUnitState(UNIT_STATE_FOLLOW_MOVE) && owner.movespline->Finalized())
        {
            owner.ClearUnitState(UNIT_STATE_FOLLOW_MOVE);
            i_path = nullptr;
            MovementInform(owner);

            if (i_recheckPredictedDistance)
            {
                i_recheckPredictedDistanceTimer.Reset(1000);
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
            i_recheckPredictedDistance = true;
        }
        else
        {
            i_recheckPredictedDistance = false;
            i_recheckPredictedDistanceTimer.Reset(0);
        }

        if (!i_path)
            i_path = std::make_unique<PathGenerator>(&owner);
        else
            i_path->Clear();

        target->MovePositionToFirstCollision(targetPosition, owner.GetCombatReach() + _range, target->ToAbsoluteAngle(Position::NormalizeOrientation(_range)) - target->GetOrientation());

        float x, y, z;
        targetPosition.GetPosition(x, y, z);

        //if (owner->IsHovering())
        if (owner.m_movementInfo.HasMovementFlag(MOVEMENTFLAG_HOVER)) // alt: owner.isHover()
            owner.UpdateAllowedPositionZ(x, y, z);

        bool success = i_path->CalculatePath(x, y, z, forceDest);
        if (!success || (i_path->GetPathType() & PATHFIND_NOPATH && !followingMaster))
        {
            if (!owner.IsStopped())
                owner.StopMoving();

            return true;
        }

        owner.AddUnitState(UNIT_STATE_FOLLOW_MOVE);

        Movement::MoveSplineInit init(*owner.ToUnit());
        init.MovebyPath(i_path->GetPath());
        if (_inheritWalkState)
            init.SetWalk(target->IsWalking() || target->movespline->isWalking());
        
        if (Optional<float> velocity = GetVelocity(owner.ToUnit(), target, i_path->GetActualEndPosition(), owner.isGuardian()))
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
            if (i_recheckPredictedDistanceTimer.GetExpiry())
            {
                i_recheckPredictedDistanceTimer.Update(diff);
                if (i_recheckPredictedDistanceTimer.Passed())
                {
                    i_recheckPredictedDistanceTimer = (TimeTrackerSmall)0;
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
template void TargetedMovementGeneratorMedium<Player,ChaseMovementGenerator<Player> >::_setTargetLocation(Player &);
template void TargetedMovementGeneratorMedium<Player,FollowMovementGenerator<Player> >::_setTargetLocation(Player &);
template void TargetedMovementGeneratorMedium<Creature,ChaseMovementGenerator<Creature> >::_setTargetLocation(Creature &);
template void TargetedMovementGeneratorMedium<Creature,FollowMovementGenerator<Creature> >::_setTargetLocation(Creature &);
template void TargetedMovementGeneratorMedium<Creature,FetchMovementGenerator<Creature> >::_setTargetLocation(Creature &);
template bool TargetedMovementGeneratorMedium<Player,ChaseMovementGenerator<Player> >::DoUpdate(Player &, const uint32 &);
template bool TargetedMovementGeneratorMedium<Player,FollowMovementGenerator<Player> >::DoUpdate(Player &, const uint32 &);
template bool TargetedMovementGeneratorMedium<Creature,ChaseMovementGenerator<Creature> >::DoUpdate(Creature &, const uint32 &);
template bool TargetedMovementGeneratorMedium<Creature,FollowMovementGenerator<Creature> >::DoUpdate(Creature &, const uint32 &);
template bool TargetedMovementGeneratorMedium<Creature,FetchMovementGenerator<Creature> >::DoUpdate(Creature &, const uint32 &);
template void TargetedMovementGeneratorMedium<Creature,FollowMovementGenerator<Creature> >::_updateSpeed(Creature &);

template void ChaseMovementGenerator<Player>::_reachTarget(Player &);
template void ChaseMovementGenerator<Creature>::_reachTarget(Creature &);
template void ChaseMovementGenerator<Player>::DoFinalize(Player &);
template void ChaseMovementGenerator<Creature>::DoFinalize(Creature &);
template void ChaseMovementGenerator<Player>::DoReset(Player &);
template void ChaseMovementGenerator<Creature>::DoReset(Creature &);
template void ChaseMovementGenerator<Player>::MovementInform(Player &unit);

template void FetchMovementGenerator<Creature>::_reachTarget(Creature &);
template void FetchMovementGenerator<Creature>::DoFinalize(Creature &);
template void FetchMovementGenerator<Creature>::DoReset(Creature &);

template void FollowMovementGenerator<Player>::DoInitialize(Player&);
template void FollowMovementGenerator<Creature>::DoInitialize(Creature&);
template void FollowMovementGenerator<Player>::DoFinalize(Player &);
template void FollowMovementGenerator<Creature>::DoFinalize(Creature &);
template void FollowMovementGenerator<Player>::DoReset(Player &);
template void FollowMovementGenerator<Creature>::DoReset(Creature &);
template bool FollowMovementGenerator<Player>::DoUpdate(Player&, uint32);
template bool FollowMovementGenerator<Creature>::DoUpdate(Creature&, uint32);
