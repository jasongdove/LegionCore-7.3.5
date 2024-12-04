/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

/* Script Data Start
SDName: Redridge Mountains
SD%Complete: 0
SDComment:
Script Data End */

#include "MoveSplineInit.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"

enum RedridgeCreature
{
    NPC_CANYON_ETTIN = 43094,
    NPC_SUBDUED_CANYON_ETTIN = 43197,
    NPC_HUGE_BOULDER = 43196,
    NPC_FOREMAN_OSLOW = 341,
    NPC_BRIDGE_WORKER_TRENT = 648,
    NPC_BRIDGE_WORKER_DMITRI = 649,
    NPC_BRIDGE_WORKER_JESS = 650,
    NPC_BRIDGE_WORKER_DANIEL = 651,
    NPC_BRIDGE_WORKER_MATTHEW = 652,
    NPC_BRIDGE_WORKER_ALEX = 653,
};

enum RedridgeSpell
{
    SPELL_CONTROL_ETTIN = 80704,
    SPELL_CONTROL_ETTIN_2 = 80702,
    SPELL_LIFT_HUGE_BOULDER = 80739,
    SPELL_LIFT_BOULDER_RIDE = 82566,
    SPELL_EJECT_PASSENGER_1 = 80743
};

class spell_redridge_control_ettin : public SpellScript
{
    PrepareSpellScript(spell_redridge_control_ettin);

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (!caster || !caster->IsPlayer())
            return;

        if (Creature* target = GetHitCreature())
            if (target->GetEntry() == NPC_CANYON_ETTIN)
                caster->CastSpell(target, SPELL_CONTROL_ETTIN_2, false);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_redridge_control_ettin::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

class spell_redridge_lift_huge_boulder : public SpellScript
{
    PrepareSpellScript(spell_redridge_lift_huge_boulder);

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetCaster())
            if (Creature* target = GetHitCreature())
                caster->CastSpell(target, uint32(GetSpellInfo()->GetEffect(EFFECT_0)->BasePoints), false);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_redridge_lift_huge_boulder::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

enum HugeBoulder
{
    EVENT_START_PHASE_IDLE = 1,
    EVENT_FOREMAN_OSLOW_IDLE_TALK = 2,
    EVENT_BRIDGE_WORKER_ALEX_IDLE_TALK = 3,
    EVENT_BRIDGE_WORKER_ALEX_HARDER = 4,
    EVENT_BRIDGE_WORKER_MATTHEW_HARDER_RESPONSE = 5,
    EVENT_BRIDGE_WORKERS_RESPONSE = 6,
    EVENT_REPOSITION = 7,
    EVENT_LIFT_BOULDER = 8,
    EVENT_ETTIN_LINE_1 = 9,
    EVENT_ETTIN_LINE_2 = 10,
    EVENT_ETTIN_LINE_3 = 11,
    EVENT_MOVE_TO_WATER = 12,
    EVENT_THROW_BOULDER = 13,
    EVENT_PATH_AWAY = 14,
    EVENT_DONE = 15,
    EVENT_BRIDGE_WORKERS_COWER = 16,
    EVENT_FOREMAN_GET_UP = 17,
    EVENT_FOREMAN_STUN = 18,

    POINT_NEAR_ROCK = 1,
    POINT_NEAR_WATER = 2,
    POINT_UP_PATH = 3
};

static constexpr uint8 const EttinPathToWaterSize = 5;
G3D::Vector3 const EttinPathToWater[EttinPathToWaterSize] =
{
    { -9270.847f, -2299.5737f, 69.64171f },
    { -9271.597f, -2309.5737f, 69.89171f },
    { -9279.847f, -2319.0737f, 66.89171f },
    { -9304.097f, -2330.5737f, 61.64171f },
    { -9324.86f,  -2338.94f,   61.2445f  }
};

static constexpr uint8 const EttinPathUpHillSize = 6;
G3D::Vector3 const EttinPathUpHill[EttinPathUpHillSize] =
{
    { -9308.439f, -2330.975f, 61.716003f },
    { -9292.939f, -2325.475f, 62.716003f },
    { -9276.939f, -2316.725f, 68.966f },
    { -9260.689f, -2312.725f, 75.216f },
    { -9237.689f, -2313.225f, 78.716f },
    { -9214.52f,  -2334.01f,  83.6875f }
};

class npc_redridge_subdued_ettin : public CreatureScript
{
public:
    npc_redridge_subdued_ettin() : CreatureScript("npc_redridge_subdued_ettin") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_redridge_subdued_ettinAI(creature);
    }

    struct npc_redridge_subdued_ettinAI : public CreatureAI
    {
        npc_redridge_subdued_ettinAI(Creature* creature) : CreatureAI(creature) { }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            _events.Reset();
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LIFT_BOULDER:
                        if (Creature* boulder = me->FindNearestCreature(NPC_HUGE_BOULDER, 10.0f))
                        {
                            _boulderGUID = boulder->GetGUID();
                            boulder->CastSpell(me, SPELL_LIFT_HUGE_BOULDER, false);
                            boulder->GetAI()->SetData(0, 0);
                        }
                        _events.ScheduleEvent(EVENT_ETTIN_LINE_1, 1s);
                        break;
                    case EVENT_ETTIN_LINE_1:
                        sCreatureTextMgr->SendChat(me, 0);
                        _events.ScheduleEvent(EVENT_ETTIN_LINE_2, 4s);
                        break;
                    case EVENT_ETTIN_LINE_2:
                        sCreatureTextMgr->SendChat(me, 1);
                        _events.ScheduleEvent(EVENT_ETTIN_LINE_3, 6s);
                        break;
                    case EVENT_ETTIN_LINE_3:
                        sCreatureTextMgr->SendChat(me, 2);
                        _events.ScheduleEvent(EVENT_MOVE_TO_WATER, 5s);
                        break;
                    case EVENT_MOVE_TO_WATER:
                    {
                        Movement::MoveSplineInit init(*me);
                        Movement::PointsArray path(EttinPathToWater, EttinPathToWater + EttinPathToWaterSize);
                        init.MovebyPath(path);
                        me->GetMotionMaster()->LaunchMoveSpline(std::move(init), POINT_NEAR_WATER, MOTION_SLOT_ACTIVE, POINT_MOTION_TYPE);
                        break;
                    }
                    case EVENT_THROW_BOULDER:
                        me->RemoveAurasDueToSpell(SPELL_LIFT_BOULDER_RIDE);
                        _events.ScheduleEvent(EVENT_PATH_AWAY, 6s);
                        break;
                    case EVENT_PATH_AWAY:
                    {
                        if (Creature* boulder = me->GetMap()->GetCreature(_boulderGUID))
                            boulder->GetAI()->SetData(0, 1);

                        // run up path
                        Movement::MoveSplineInit init(*me);
                        Movement::PointsArray path(EttinPathUpHill, EttinPathUpHill + EttinPathUpHillSize);
                        init.MovebyPath(path);
                        me->GetMotionMaster()->LaunchMoveSpline(std::move(init), POINT_UP_PATH, MOTION_SLOT_ACTIVE, POINT_MOTION_TYPE);

                        // despawn after 15s
                        _events.ScheduleEvent(EVENT_DONE, 15s);
                        break;
                    }
                    case EVENT_DONE:
                        me->DisappearAndDie();
                        break;
                }
            }
        }

        void CalcExitVehiclePos(Position& pos) override
        {
            // location to throw huge boulder
            // doesn't really work yet; something is strange with vehicle exit code
            pos.Relocate(-9310.855f, -2366.367f, 55.16147f);
        }

        void MovementInform(uint32 movementType, uint32 pointId) override
        {
            if (movementType != POINT_MOTION_TYPE)
                return;

            switch (pointId)
            {
                case POINT_NEAR_ROCK:
                    if (Creature* daniel = me->FindNearestCreature(NPC_BRIDGE_WORKER_DANIEL, 20.0f))
                        me->SetFacingTo(daniel);

                    _events.ScheduleEvent(EVENT_LIFT_BOULDER, 0);
                    break;
                case POINT_NEAR_WATER:
                    me->SetFacingTo(5.0614f);
                    _events.ScheduleEvent(EVENT_THROW_BOULDER, 1s);
                    break;
                default:
                    break;
            }
        }

    private:
        EventMap _events;
        ObjectGuid _boulderGUID;
    };
};

class npc_redridge_huge_boulder : public CreatureScript
{
public:
    npc_redridge_huge_boulder() : CreatureScript("npc_redridge_huge_boulder") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_redridge_huge_boulderAI(creature);
    }

    struct npc_redridge_huge_boulderAI : public CreatureAI
    {
        npc_redridge_huge_boulderAI(Creature* creature) : CreatureAI(creature) { }

        void Reset() override
        {
            _events.Reset();
            _events.ScheduleEvent(EVENT_START_PHASE_IDLE, 0);
        }

        void JustSummoned(Creature* summoned) override
        {
            Reset();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (!caster || !caster->IsPlayer())
                return;

            if (spell->Id != SPELL_CONTROL_ETTIN)
                return;

            if (Creature* ettin = me->FindNearestCreature(NPC_SUBDUED_CANYON_ETTIN, 20.0f))
            {
                _playerGUID = caster->GetGUID();
                _ettinGUID = ettin->GetGUID();
                _events.Reset();
                _events.ScheduleEvent(EVENT_REPOSITION, 1s);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_PHASE_IDLE:
                        // wait for everyone to appear
                        if (!LocateGUIDs())
                            _events.Repeat(500);

                        _events.ScheduleEvent(EVENT_FOREMAN_OSLOW_IDLE_TALK, 45s, 60s);
                        _events.ScheduleEvent(EVENT_BRIDGE_WORKER_ALEX_IDLE_TALK, 20s, 30s);
                        break;
                    case EVENT_FOREMAN_OSLOW_IDLE_TALK:
                        if (Creature* foreman = GetForeman())
                            sCreatureTextMgr->SendChat(foreman, 0);
                        _events.Repeat(45s, 60s);
                        break;
                    case EVENT_BRIDGE_WORKER_ALEX_IDLE_TALK:
                        if (Creature* alex = GetAlex())
                        {
                            uint32 text = urand(0, 3);
                            switch (text)
                            {
                                case 1:
                                    sCreatureTextMgr->SendChat(alex, text);
                                    _events.ScheduleEvent(EVENT_BRIDGE_WORKERS_RESPONSE, 1s);
                                    break;
                                case 2:
                                    sCreatureTextMgr->SendChat(alex, text);
                                    _events.ScheduleEvent(EVENT_BRIDGE_WORKER_ALEX_HARDER, 3s);
                                    break;
                                default:
                                    sCreatureTextMgr->SendChat(alex, text);
                                    _events.Repeat(10s);
                                    break;
                            }
                        }
                        break;
                    case EVENT_BRIDGE_WORKER_ALEX_HARDER:
                        if (Creature* alex = GetAlex())
                        {
                            sCreatureTextMgr->SendChat(alex, 4);
                            _events.ScheduleEvent(EVENT_BRIDGE_WORKER_MATTHEW_HARDER_RESPONSE, 4s);
                        }
                        break;
                    case EVENT_BRIDGE_WORKER_MATTHEW_HARDER_RESPONSE:
                        if (Creature* matthew = GetMatthew())
                            sCreatureTextMgr->SendChat(matthew, 1, _foremanGUID);
                        _events.ScheduleEvent(EVENT_BRIDGE_WORKER_ALEX_IDLE_TALK, 20s, 30s);
                        break;
                    case EVENT_BRIDGE_WORKERS_RESPONSE:
                        if (Creature* matthew = GetMatthew())
                            sCreatureTextMgr->SendChat(matthew, 0, _foremanGUID);
                        if (Creature* trent = GetTrent())
                            sCreatureTextMgr->SendChat(trent, 0, _foremanGUID);
                        if (Creature* dmitri = GetDmitri())
                            sCreatureTextMgr->SendChat(dmitri, 0, _foremanGUID);
                        if (Creature* jess = GetJess())
                            sCreatureTextMgr->SendChat(jess, 0, _foremanGUID);
                        if (Creature* daniel = GetDaniel())
                            sCreatureTextMgr->SendChat(daniel, 0, _foremanGUID);
                        _events.ScheduleEvent(EVENT_BRIDGE_WORKER_ALEX_IDLE_TALK, 20s, 30s);
                        break;
                    case EVENT_REPOSITION:
                        if (Creature* ettin = GetEttin())
                            ettin->GetMotionMaster()->MovePoint(POINT_NEAR_ROCK, -9271.833f, -2290.7075f, 68.538925f);

                        if (Creature* trent = GetTrent())
                        {
                            trent->SetAnimKitId(0);
                            trent->GetMotionMaster()->MovePoint(0, -9281.44f, -2285.27f, 67.5123f);
                        }

                        if (Creature* dmitri = GetDmitri())
                        {
                            dmitri->SetAnimKitId(0);
                            dmitri->GetMotionMaster()->MovePoint(0, -9282.8f, -2293.28f, 67.5089f);
                        }

                        if (Creature* jess = GetJess())
                        {
                            jess->SetAnimKitId(0);
                            jess->GetMotionMaster()->MovePoint(0, -9282.27f, -2290.95f, 67.5319f);
                        }

                        if (Creature* daniel = GetDaniel())
                        {
                            daniel->SetAnimKitId(0);
                            daniel->GetMotionMaster()->MovePoint(0, -9281.77f, -2287.55f, 67.5869f);
                        }

                        if (Creature* matthew = GetMatthew())
                        {
                            matthew->SetAnimKitId(0);
                            matthew->GetMotionMaster()->MovePoint(0, -9280.71f, -2283.21f, 67.5747f);
                        }

                        if (Creature* alex = GetAlex())
                        {
                            alex->SetAnimKitId(0);
                            alex->GetMotionMaster()->MovePoint(0, -9279.86f, -2281.42f, 67.5854f);
                        }

                        _events.ScheduleEvent(EVENT_LIFT_BOULDER, 100ms);
                        break;
                    case EVENT_LIFT_BOULDER:
                        if (Creature* foreman = GetForeman())
                            if (Creature* ettin = GetEttin())
                            {
                                bool allStopped = ettin->IsStopped();

                                if (Creature* trent = GetTrent())
                                {
                                    if (trent->IsStopped())
                                        trent->SetFacingTo(foreman);

                                    allStopped = allStopped && trent->IsStopped();
                                }

                                if (Creature* dmitri = GetDmitri())
                                {
                                    if (dmitri->IsStopped())
                                        dmitri->SetFacingTo(foreman);

                                    allStopped = allStopped && dmitri->IsStopped();
                                }

                                if (Creature* jess = GetJess())
                                {
                                    if (jess->IsStopped())
                                        jess->SetFacingTo(foreman);

                                    allStopped = allStopped && jess->IsStopped();
                                }

                                if (Creature* daniel = GetDaniel())
                                {
                                    if (daniel->IsStopped())
                                        daniel->SetFacingTo(foreman);

                                    allStopped = allStopped && daniel->IsStopped();
                                }

                                if (Creature* matthew = GetMatthew())
                                {
                                    if (matthew->IsStopped())
                                        matthew->SetFacingTo(foreman);

                                    allStopped = allStopped && matthew->IsStopped();
                                }

                                if (Creature* alex = GetAlex())
                                {
                                    if (alex->IsStopped())
                                        alex->SetFacingTo(foreman);

                                    allStopped = allStopped && alex->IsStopped();
                                }

                                if (allStopped)
                                    _events.ScheduleEvent(EVENT_BRIDGE_WORKERS_COWER, 6s);
                                else
                                    _events.Repeat(100ms);
                            }
                        break;
                    case EVENT_BRIDGE_WORKERS_COWER:
                    {
                        uint32 a = urand(0, 5);
                        uint32 b = urand(0, 5);
                        if (a == b)
                            b = (a + 2) % 6;

                        if (Creature* alex = GetAlex())
                        {
                            alex->SetUInt32Value(UNIT_FIELD_EMOTE_STATE, 431);
                            if (a == 0 || b == 0)
                                alex->MonsterSay(int32(43230 + urand(0, 2)), LANG_UNIVERSAL, ObjectGuid::Empty);
                        }

                        if (Creature* matthew = GetMatthew())
                        {
                            matthew->SetUInt32Value(UNIT_FIELD_EMOTE_STATE, 431);
                            if (a == 1 || b == 1)
                                matthew->MonsterSay(int32(43230 + urand(0, 2)), LANG_UNIVERSAL, ObjectGuid::Empty);
                        }

                        if (Creature* trent = GetTrent())
                        {
                            trent->SetUInt32Value(UNIT_FIELD_EMOTE_STATE, 431);
                            if (a == 2 || b == 2)
                                trent->MonsterSay(int32(43230 + urand(0, 2)), LANG_UNIVERSAL, ObjectGuid::Empty);
                        }

                        if (Creature* dmitri = GetDmitri())
                        {
                            dmitri->SetUInt32Value(UNIT_FIELD_EMOTE_STATE, 431);
                            if (a == 3 || b == 3)
                                dmitri->MonsterSay(int32(43230 + urand(0, 2)), LANG_UNIVERSAL, ObjectGuid::Empty);
                        }

                        if (Creature* jess = GetJess())
                        {
                            jess->SetUInt32Value(UNIT_FIELD_EMOTE_STATE, 431);
                            if (a == 4 || b == 4)
                                jess->MonsterSay(int32(43230 + urand(0, 2)), LANG_UNIVERSAL, ObjectGuid::Empty);
                        }

                        if (Creature* daniel = GetDaniel())
                        {
                            daniel->SetUInt32Value(UNIT_FIELD_EMOTE_STATE, 431);
                            if (a == 5 || b == 5)
                                daniel->MonsterSay(int32(43230 + urand(0, 2)), LANG_UNIVERSAL, ObjectGuid::Empty);
                        }

                        break;
                    }
                    case EVENT_FOREMAN_GET_UP:
                        if (Creature* foreman = GetForeman())
                            foreman->SetStandState(UNIT_STAND_STATE_STAND);
                        _events.ScheduleEvent(EVENT_FOREMAN_STUN, 2s);
                        break;
                    case EVENT_FOREMAN_STUN:
                        if (Creature* foreman = GetForeman())
                            foreman->SetUInt32Value(UNIT_FIELD_EMOTE_STATE, 64);
                        break;
                    case EVENT_DONE:
                        // quest credit
                        if (Player* player = ObjectAccessor::FindPlayer(me->GetMap(), _playerGUID))
                            player->RewardPlayerAndGroupAtEvent(NPC_FOREMAN_OSLOW, player);

                        if (Creature* alex = GetAlex())
                            alex->DisappearAndDie();
                        if (Creature* matthew = GetMatthew())
                            matthew->DisappearAndDie();
                        if (Creature* trent = GetTrent())
                            trent->DisappearAndDie();
                        if (Creature* dmitri = GetDmitri())
                            dmitri->DisappearAndDie();
                        if (Creature* jess = GetJess())
                            jess->DisappearAndDie();
                        if (Creature* daniel = GetDaniel())
                            daniel->DisappearAndDie();
                        if (Creature* foreman = GetForeman())
                            foreman->DisappearAndDie();

                        _events.Reset();
                        me->DisappearAndDie();
                        break;
                }
            }
        }

        void SetData(uint32 /*id*/, uint32 value) override
        {
            if (value == 0)
                _events.ScheduleEvent(EVENT_FOREMAN_GET_UP, 3s);
            else
                _events.ScheduleEvent(EVENT_DONE, 0);
        }

        bool LocateGUIDs()
        {
            if (Creature* foreman = me->FindNearestCreature(NPC_FOREMAN_OSLOW, 10.0f))
                if (Creature* alex = me->FindNearestCreature(NPC_BRIDGE_WORKER_ALEX, 10.0f))
                    if (Creature* matthew = me->FindNearestCreature(NPC_BRIDGE_WORKER_MATTHEW, 10.0f))
                        if (Creature* trent = me->FindNearestCreature(NPC_BRIDGE_WORKER_TRENT, 10.0f))
                            if (Creature* dmitri = me->FindNearestCreature(NPC_BRIDGE_WORKER_DMITRI, 10.0f))
                                if (Creature* jess = me->FindNearestCreature(NPC_BRIDGE_WORKER_JESS, 10.0f))
                                    if (Creature* daniel = me->FindNearestCreature(NPC_BRIDGE_WORKER_DANIEL, 10.0f))
                                    {
                                        _foremanGUID = foreman->GetGUID();
                                        _alexGUID = alex->GetGUID();
                                        _matthewGUID = matthew->GetGUID();
                                        _trentGUID = trent->GetGUID();
                                        _dmitriGUID = dmitri->GetGUID();
                                        _jessGUID = jess->GetGUID();
                                        _danielGUID = daniel->GetGUID();
                                        return true;
                                    }

            return false;
        }

        Creature* GetForeman()
        {
            return me->GetMap()->GetCreature(_foremanGUID);
        }

        Creature* GetAlex()
        {
            return me->GetMap()->GetCreature(_alexGUID);
        }

        Creature* GetMatthew()
        {
            return me->GetMap()->GetCreature(_matthewGUID);
        }

        Creature* GetTrent()
        {
            return me->GetMap()->GetCreature(_trentGUID);
        }

        Creature* GetDmitri()
        {
            return me->GetMap()->GetCreature(_dmitriGUID);
        }

        Creature* GetJess()
        {
            return me->GetMap()->GetCreature(_jessGUID);
        }

        Creature* GetDaniel()
        {
            return me->GetMap()->GetCreature(_danielGUID);
        }

        Creature* GetEttin()
        {
            return me->GetMap()->GetCreature(_ettinGUID);
        }

    private:
        EventMap _events;
        ObjectGuid _playerGUID;
        ObjectGuid _foremanGUID;
        ObjectGuid _alexGUID;
        ObjectGuid _matthewGUID;
        ObjectGuid _trentGUID;
        ObjectGuid _dmitriGUID;
        ObjectGuid _jessGUID;
        ObjectGuid _danielGUID;
        ObjectGuid _ettinGUID;
    };
};

void AddSC_redridge_mountains()
{
    RegisterSpellScript(spell_redridge_control_ettin);
    RegisterSpellScript(spell_redridge_lift_huge_boulder);
    new npc_redridge_subdued_ettin();
    new npc_redridge_huge_boulder();
}
