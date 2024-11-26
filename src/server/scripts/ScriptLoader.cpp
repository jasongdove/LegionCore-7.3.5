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

#include "ScriptLoader.h"

void AddSpellScripts();
void AddCommandsScripts();

//bg
void AddSC_battleground_seething_shore();
void AddSC_battleground_warsong();
void AddSC_battleground_kotmogu();
void AddSC_battleground_shado_pan();

#ifdef SCRIPTS
void AddBattlePayScripts();
void AddWorldScripts();
void AddKalimdorScripts();
void AddOutlandScripts();
void AddNorthrendScripts();
void AddOutdoorPvPScripts();
void AddScenarioScripts();
void AddCustomScripts();
void AddLegionScripts();
void AddDraenorScripts();
void AddEasternKingdomsScripts();
void AddMaelstromScripts();
void AddPandariaScripts();
void AddBrawlersGuildScripts();
#endif

void AddScripts()
{
    AddSpellScripts();
    AddCommandsScripts();

    // battleground scripts
    AddSC_battleground_seething_shore();
    AddSC_battleground_warsong();
    AddSC_battleground_kotmogu();
    AddSC_battleground_shado_pan();

#ifdef SCRIPTS
    AddBattlePayScripts();
    AddWorldScripts();
    AddKalimdorScripts();
    AddOutlandScripts();
    AddNorthrendScripts();
    AddLegionScripts();
    AddDraenorScripts();
    AddEasternKingdomsScripts();
    AddMaelstromScripts();
    AddPandariaScripts();
    AddOutdoorPvPScripts();
    AddBrawlersGuildScripts();
    AddScenarioScripts();
    AddCustomScripts();
#endif
}
