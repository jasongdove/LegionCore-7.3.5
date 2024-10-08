/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "mechanar.h"

static DoorData const doorData[] =
{
    { GO_DOOR_MOARG_1,          DATA_GATEWATCHER_IRON_HAND,     DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { GO_DOOR_MOARG_2,          DATA_GATEWATCHER_GYROKILL,      DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { GO_DOOR_NETHERMANCER,     DATA_NETHERMANCER_SEPRETHREA,   DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { 0,                        0,                              DOOR_TYPE_ROOM,     BOUNDARY_NONE }
};

class instance_mechanar : public InstanceMapScript
{
    public:
        instance_mechanar(): InstanceMapScript("instance_mechanar", 554) { }

        struct instance_mechanar_InstanceMapScript : public InstanceScript
        {
            ObjectGuid chahcelegionGUID;
            
            instance_mechanar_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetHeaders(DataHeader);
                SetBossNumber(EncounterCount);
                LoadDoorData(doorData);
            }
            
            void OnGameObjectCreate(GameObject* gameObject)
            {
                switch (gameObject->GetEntry())
                {
                    case GO_DOOR_MOARG_1:
                    case GO_DOOR_MOARG_2:
                    case GO_DOOR_NETHERMANCER:
                        AddDoor(gameObject, true);
                        break;
                    case GO_CHACHE_LEGION:
                        chahcelegionGUID = gameObject->GetGUID();
                        break;
                    default:
                        break;
                }
            }
            ObjectGuid GetGuidData(uint32 identifier) const
            {
                switch (identifier)
                {
                    case DATA_GO_CHAHCE_LEGION:
                        return chahcelegionGUID;
                }
                return ObjectGuid::Empty;
            }
                        
            void OnGameObjectRemove(GameObject* gameObject)
            {
                switch (gameObject->GetEntry())
                {
                    case GO_DOOR_MOARG_1:
                    case GO_DOOR_MOARG_2:
                    case GO_DOOR_NETHERMANCER:
                        AddDoor(gameObject, false);
                        break;
                    default:
                        break;
                }
            }

            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                    case DATA_GATEWATCHER_GYROKILL:
                    case DATA_GATEWATCHER_IRON_HAND:
                    case DATA_MECHANOLORD_CAPACITUS:
                    case DATA_NETHERMANCER_SEPRETHREA:
                    case DATA_PATHALEON_THE_CALCULATOR:
                        break;
                    default:
                        break;
                }

                return true;
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_mechanar_InstanceMapScript(map);
        }
};

void AddSC_instance_mechanar()
{
    new instance_mechanar();
}