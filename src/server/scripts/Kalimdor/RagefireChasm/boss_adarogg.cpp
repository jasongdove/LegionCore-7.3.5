/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
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
#include "ScriptedCreature.h"
#include "TaskScheduler.h"
#include "ragefire_chasm.h"

// 61408 - Adarogg
// this is a placeholder to allow boss kill credit/messaging from BossAI::JustDied
struct boss_adarogg : public BossAI
{
    boss_adarogg(Creature* creature) : BossAI(creature, BOSS_ADAROGG) { }
};

void AddSC_boss_adarogg()
{
    RegisterRagefireChasmCreatureAI(boss_adarogg);
}
