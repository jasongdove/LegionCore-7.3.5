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

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "razorfen_downs.h"

#define    MAX_ENCOUNTER  1

class instance_razorfen_downs : public InstanceMapScript
{
public:
    instance_razorfen_downs() : InstanceMapScript("instance_razorfen_downs", 129) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_razorfen_downs_InstanceMapScript(map);
    }

    struct instance_razorfen_downs_InstanceMapScript : public InstanceScript
    {
        instance_razorfen_downs_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            SetHeaders(DataHeader);
        }

        ObjectGuid uiGongGUID;

        uint32 m_auiEncounter[MAX_ENCOUNTER];

        uint16 uiGongWaves;

        std::string str_data;

        void Initialize()
        {
            uiGongGUID.Clear();

            uiGongWaves = 0;

            memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
        }

        void WriteSaveDataMore(std::ostringstream& data) override
        {
            data << uiGongWaves;
        }

        void ReadSaveDataMore(std::istringstream& data) override
        {
            data >> uiGongWaves;
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_GONG:
                    uiGongGUID = go->GetGUID();
                    if (m_auiEncounter[0] == DONE)
                        go->SetFlag(GAMEOBJECT_FIELD_FLAGS, GO_FLAG_NOT_SELECTABLE);
                    break;
                default:
                    break;
            }
        }

        void SetData(uint32 uiType, uint32 uiData)
        {
            if (uiType == DATA_GONG_WAVES)
            {
                uiGongWaves = uiData;

                switch (uiGongWaves)
                {
                    case 9:
                    case 14:
                        if (GameObject* go = instance->GetGameObject(uiGongGUID))
                            go->RemoveFlag(GAMEOBJECT_FIELD_FLAGS, GO_FLAG_NOT_SELECTABLE);
                        break;
                    case 1:
                    case 10:
                    case 16:
                    {
                        GameObject* go = instance->GetGameObject(uiGongGUID);

                        if (!go)
                            return;

                        go->SetFlag(GAMEOBJECT_FIELD_FLAGS, GO_FLAG_NOT_SELECTABLE);

                        uint32 uiCreature = 0;
                        uint8 uiSummonTimes = 0;

                        switch (uiGongWaves)
                        {
                            case 1:
                                uiCreature = CREATURE_TOMB_FIEND;
                                uiSummonTimes = 7;
                                break;
                            case 10:
                                uiCreature = CREATURE_TOMB_REAVER;
                                uiSummonTimes = 3;
                                break;
                            case 16:
                                uiCreature = CREATURE_TUTEN_KASH;
                                break;
                            default:
                                break;
                        }

                        if (Creature* creature = go->SummonCreature(uiCreature, 2502.635f, 844.140f, 46.896f, 0.633f))
                        {
                            if (uiGongWaves == 10 || uiGongWaves == 1)
                            {
                                for (uint8 i = 0; i < uiSummonTimes; ++i)
                                {
                                    if (Creature* summon = go->SummonCreature(uiCreature, 2502.635f + float(irand(-5, 5)), 844.140f + float(irand(-5, 5)), 46.896f, 0.633f))
                                        summon->GetMotionMaster()->MovePoint(0, 2533.479f + float(irand(-5, 5)), 870.020f + float(irand(-5, 5)), 47.678f);
                                }
                            }
                            creature->GetMotionMaster()->MovePoint(0, 2533.479f + float(irand(-5, 5)), 870.020f + float(irand(-5, 5)), 47.678f);
                        }
                        break;
                    }
                    default:
                        break;
                }
            }

            if (uiType == BOSS_TUTEN_KASH)
            {
                m_auiEncounter[0] = uiData;

                if (uiData == DONE)
                    SaveToDB();
            }
        }

        uint32 GetData(uint32 uiType) const
        {
            switch (uiType)
            {
                case DATA_GONG_WAVES:
                    return uiGongWaves;
            }

            return 0;
        }

        ObjectGuid GetGuidData(uint32 uiType) const
        {
            switch (uiType)
            {
                case DATA_GONG: return uiGongGUID;
            }

            return ObjectGuid::Empty;
        }
    };

};

void AddSC_instance_razorfen_downs()
{
    new instance_razorfen_downs();
}
