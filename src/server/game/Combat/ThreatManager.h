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

#ifndef _THREATMANAGER
#define _THREATMANAGER

#include "Common.h"
#include "SharedDefines.h"
#include "LinkedReference/Reference.h"
#include "UnitEvents.h"

class Unit;
class Creature;
class ThreatManager;
class SpellInfo;

#define THREAT_UPDATE_INTERVAL 1 * IN_MILLISECONDS    // Server should send threat update to client periodically each second

struct ThreatCalcHelper
{
    static float calcThreat(Unit* hatedUnit, Unit* hatingUnit, float threat, SpellSchoolMask schoolMask = SPELL_SCHOOL_MASK_NORMAL, SpellInfo const* threatSpell = nullptr);
    static bool isValidProcess(Unit* hatedUnit, Unit* hatingUnit, SpellInfo const* threatSpell = nullptr);
};

class HostileReference : public Reference<Unit, ThreatManager>
{
public:
    HostileReference(Unit* refUnit, ThreatManager* threatManager, float threat);

    void addThreat(float modThreat);
    void setThreat(float threat) { addThreat(threat - iThreat); }

    void addThreatPercent(int32 percent);

    float getThreat() const { return iThreat + iTempThreatModifier; }

    bool isOnline() const { return iOnline; }

    // The Unit might be in water and the creature can not enter the water, but has range attack
    // in this case online = true, but accessible = false
    bool isAccessible() const { return iAccessible; }

    // used for temporary setting a threat and reducing it later again.
    // the threat modification is stored
    void setTempThreat(float threat)
    {
        addTempThreat(threat - iTempThreatModifier);
    }

    void addTempThreat(float threat)
    {
        if (!threat)
            return;
        iTempThreatModifier += threat;
        ThreatRefStatusChangeEvent event(UEV_THREAT_REF_THREAT_CHANGE, this, threat);
        fireStatusChanged(event);
    }

    void resetTempThreat()
    {
        addTempThreat(-iTempThreatModifier);
    }

    float getTempThreatModifier() { return iTempThreatModifier; }

    void updateOnlineStatus();

    void setOnlineOfflineState(bool isOnline);

    void setAccessibleState(bool isAccessible);

    bool operator==(HostileReference const& hostileRef) const { return hostileRef.getUnitGuid() == getUnitGuid(); }

    ObjectGuid getUnitGuid() const { return iUnitGuid; }

    // reference is not needed anymore. really delete it !
    void removeReference();

    HostileReference* next() { return static_cast<HostileReference*>(Reference<Unit, ThreatManager>::next()); }

    // Tell our refTo (target) object that we have a link
    void targetObjectBuildLink() override;

    // Tell our refTo (target) object, that the link is cut
    void targetObjectDestroyLink() override;

    // Tell our refFrom (source) object, that the link is cut (Target destroyed)
    void sourceObjectDestroyLink() override;

private:
    // Inform the source, that the status of that reference was changed
    void fireStatusChanged(ThreatRefStatusChangeEvent& threatRefStatusChangeEvent);

    Unit* getSourceUnit();

private:
    float iThreat;
    float iTempThreatModifier;                          // used for SPELL_AURA_MOD_TOTAL_THREAT
    ObjectGuid iUnitGuid;
    bool iOnline;
    bool iAccessible;
};

class ThreatManager;

class ThreatContainer
{
    std::list<HostileReference*> iThreatList;
    bool iDirty;
    std::recursive_mutex i_threat_lock;
protected:
    friend class ThreatManager;

    void remove(HostileReference* hostileRef);
    void addReference(HostileReference* hostileRef);
    void clearReferences();

    void update();
public:
    ThreatContainer();
    ~ThreatContainer();

    HostileReference* addThreat(Unit* victim, float threat);

    void modifyThreatPercent(Unit* victim, int32 percent);

    HostileReference* selectNextVictim(Creature* attacker, HostileReference* currentVictim);

    void setDirty(bool isDirty);
    bool isDirty() const;
    bool empty() const;

    HostileReference* getMostHated();
    HostileReference* getReferenceByTarget(Unit* victim);
    std::list<HostileReference*>& getThreatList();
};

class ThreatManager
{
public:
    friend class HostileReference;

    explicit ThreatManager(Unit* owner);
    ~ThreatManager();

    void clearReferences();

    void addThreat(Unit* victim, float threat, SpellSchoolMask schoolMask = SPELL_SCHOOL_MASK_NORMAL, SpellInfo const* threatSpell = nullptr);

    void doAddThreat(Unit* victim, float threat, SpellSchoolMask schoolMask = SPELL_SCHOOL_MASK_NORMAL, SpellInfo const* threatSpell = nullptr);

    void modifyThreatPercent(Unit* victim, int32 percent);

    float getThreat(Unit* victim, bool alsoSearchOfflineList = false);

    bool isThreatListEmpty();

    void processThreatEvent(ThreatRefStatusChangeEvent* threatRefStatusChangeEvent);

    bool isNeedUpdateToClient(uint32 time);

    HostileReference* getCurrentVictim();

    Unit* getOwner();

    Unit* getHostilTarget();

    void tauntApply(Unit* taunter);
    void tauntFadeOut(Unit* taunter);

    void setCurrentVictim(HostileReference* hostileRef);

    void setDirty(bool isDirty);

    void resetAllAggro();

    template<class PREDICATE> void resetAggro(PREDICATE predicate)
    {
        auto& threatList = getThreatList();
        if (threatList.empty())
            return;

        for (auto itr = threatList.begin(); itr != threatList.end(); ++itr)
        {
            auto ref = *itr;
            if (predicate(ref->getTarget()))
            {
                ref->setThreat(0);
                setDirty(true);
            }
        }
    }

    std::list<HostileReference*>& getThreatList();
    std::list<HostileReference*>& getOfflineThreatList();

    ThreatContainer& getOnlineContainer();
    ThreatContainer& getOfflineContainer();
private:
    void _addThreat(Unit* victim, float threat);

    HostileReference* iCurrentVictim;
    Unit* iOwner;
    uint32 iUpdateTimer;
    ThreatContainer iThreatContainer;
    ThreatContainer iThreatOfflineContainer;
};

#endif

