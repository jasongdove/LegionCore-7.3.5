-- dungeon mobs should not reward pandaren rep without tabard
DELETE FROM `creature_onkill_reputation` WHERE RewFaction in (1352, 1353);
