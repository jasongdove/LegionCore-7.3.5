/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
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

#include "ScenarioPackets.h"
#include "WorldSession.h"
#include "Scenario.h"

void WorldSession::HandleQueryScenarioPOI(WorldPackets::Scenario::QueryScenarioPOI& packet)
{
    TC_LOG_DEBUG("spells", "HandleQueryScenarioPOI MissingScenarioPOITreeIDs %zu", packet.MissingScenarioPOITreeIDs.size());
    WorldPackets::Scenario::ScenarioPOIs response;

    // Read criteria tree ids and add the in a unordered_set so we don't send POIs for the same criteria tree multiple times
    std::unordered_set<uint32> criteriaTreeIds;
    for (uint32 MissingScenarioPOITreeID : packet.MissingScenarioPOITreeIDs)
        criteriaTreeIds.insert(MissingScenarioPOITreeID);

    for (uint32 criteriaTreeId : criteriaTreeIds)
    {
        if (ScenarioPOIVector const* poi = sObjectMgr->GetScenarioPOIVector(criteriaTreeId))
        {
            WorldPackets::Scenario::ScenarioPOIs::POIData data;
            data.CriteriaTreeID = criteriaTreeId;
            WorldPackets::Scenario::ScenarioPOIs::POIData::BlobData &blobData = data.BlobDatas[poi->size()];

            for (const auto& itr : *poi)
            {
                blobData.BlobID            = itr.BlobID;
                blobData.MapID             = itr.MapID;
                blobData.WorldMapAreaID    = itr.WorldMapAreaID;
                blobData.Floor             = itr.Floor;
                blobData.Priority          = itr.Priority;
                blobData.Flags             = itr.Flags;
                blobData.WorldEffectID     = itr.WorldEffectID;
                blobData.PlayerConditionID = itr.PlayerConditionID;

                WorldPackets::Scenario::ScenarioPOIs::POIData::BlobData::POIPointData &points = blobData.Points[itr.points.size()];

                for (auto point : itr.points)
                {
                    points.X = point.x;
                    points.Y = point.y;
                }
            }
        }
    }

    SendPacket(response.Write());
}
