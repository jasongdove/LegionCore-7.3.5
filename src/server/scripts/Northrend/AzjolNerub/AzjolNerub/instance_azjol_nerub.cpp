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
#include "azjol_nerub.h"

#define MAX_ENCOUNTER     3

/* Azjol Nerub encounters:
0 - Krik'thir the Gatewatcher
1 - Hadronox
2 - Anub'arak
*/

class instance_azjol_nerub : public InstanceMapScript
{
public:
    instance_azjol_nerub() : InstanceMapScript("instance_azjol_nerub", 601)
    {}

    struct instance_azjol_nerub_InstanceScript : public InstanceScript
    {
        instance_azjol_nerub_InstanceScript(InstanceMap *map) : InstanceScript(map)
        {}

        ObjectGuid uiKrikthir;
        ObjectGuid uiHadronox;
        ObjectGuid uiAnubarak;
        ObjectGuid uiWatcherGashra;
        ObjectGuid uiWatcherSilthik;
        ObjectGuid uiWatcherNarjil;
        ObjectGuid uiAnubarakDoor[3];

        ObjectGuid uiKrikthirDoor;

        uint32 auiEncounter[MAX_ENCOUNTER];

        void Initialize() override
        {
            SetHeaders(DataHeader);
            memset(&auiEncounter, 0, sizeof(auiEncounter));
            memset(&uiAnubarakDoor, 0, sizeof(uiAnubarakDoor));

            uiKrikthir.Clear();
            uiHadronox.Clear();
            uiAnubarak.Clear();
            uiWatcherGashra.Clear();
            uiWatcherSilthik.Clear();
            uiWatcherNarjil.Clear();
            uiKrikthirDoor.Clear();
        }

        bool IsEncounterInProgress() const override
        {
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (auiEncounter[i] == IN_PROGRESS)
                    return true;

            return false;
        }

        void OnCreatureCreate(Creature *creature) override
        {
            switch (creature->GetEntry())
            {
                case 28684:
                    uiKrikthir = creature->GetGUID();
                    break;
                case 28921:
                    uiHadronox = creature->GetGUID();
                    break;
                case 29120:
                    uiAnubarak = creature->GetGUID();
                    break;
                case 28730:
                    uiWatcherGashra = creature->GetGUID();
                    break;
                case 28731:
                    uiWatcherSilthik = creature->GetGUID();
                    break;
                case 28729:
                    uiWatcherNarjil = creature->GetGUID();
                    break;
            }
        }

        void OnGameObjectCreate(GameObject *go) override
        {
            switch (go->GetEntry())
            {
                case 192395:
                    uiKrikthirDoor = go->GetGUID();
                    if (auiEncounter[0] == DONE)
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    break;
                case 192396:
                    uiAnubarakDoor[0] = go->GetGUID();
                    break;
                case 192397:
                    uiAnubarakDoor[1] = go->GetGUID();
                    break;
                case 192398:
                    uiAnubarakDoor[2] = go->GetGUID();
                    break;
            }
        }

        ObjectGuid GetGuidData(uint32 identifier) const override
        {
            switch (identifier)
            {
                case DATA_KRIKTHIR_THE_GATEWATCHER:
                    return uiKrikthir;
                case DATA_HADRONOX:
                    return uiHadronox;
                case DATA_ANUBARAK:
                    return uiAnubarak;
                case DATA_WATCHER_GASHRA:
                    return uiWatcherGashra;
                case DATA_WATCHER_SILTHIK:
                    return uiWatcherSilthik;
                case DATA_WATCHER_NARJIL:
                    return uiWatcherNarjil;
            }

            return ObjectGuid::Empty;
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
                case DATA_KRIKTHIR_THE_GATEWATCHER_EVENT:
                    auiEncounter[0] = data;
                    if (data == DONE)
                        HandleGameObject(uiKrikthirDoor, true);
                    break;
                case DATA_HADRONOX_EVENT:
                    auiEncounter[1] = data;
                    break;
                case DATA_ANUBARAK_EVENT:
                    auiEncounter[2]  = data;
                    if (data == IN_PROGRESS)
                        for (uint8 i = 0; i < 3; ++i)
                            HandleGameObject(uiAnubarakDoor[i], false);
                    else if (data == NOT_STARTED || data == DONE)
                        for (uint8 i = 0; i < 3; ++i)
                            HandleGameObject(uiAnubarakDoor[i], true);
                    break;
            }

            if (data == DONE)
            {
                SaveToDB();
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
                case DATA_KRIKTHIR_THE_GATEWATCHER_EVENT:
                    return auiEncounter[0];
                case DATA_HADRONOX_EVENT:
                    return auiEncounter[1];
                case DATA_ANUBARAK_EVENT:
                    return auiEncounter[2];
            }

            return 0;
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "A N " << auiEncounter[0] << ' ' << auiEncounter[1] << ' '
                       << auiEncounter[2];

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char *in) override
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char   dataHead1, dataHead2;
            uint16 data0, data1, data2;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2;

            if (dataHead1 == 'A' && dataHead2 == 'N')
            {
                auiEncounter[0] = data0;
                auiEncounter[1] = data1;
                auiEncounter[2] = data2;

                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (auiEncounter[i] == IN_PROGRESS)
                        auiEncounter[i] = NOT_STARTED;

            } else
                OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };

    InstanceScript *GetInstanceScript(InstanceMap *map) const override
    {
        return new instance_azjol_nerub_InstanceScript(map);
    }
};

void AddSC_instance_azjol_nerub()
{
   new instance_azjol_nerub;
}
