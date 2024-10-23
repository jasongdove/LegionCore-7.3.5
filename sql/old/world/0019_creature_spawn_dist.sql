-- Worg
UPDATE `creature` SET `MovementType`=1, `spawndist`=10 WHERE id=1765;

-- Rabid Worg
UPDATE `creature` SET `MovementType`=1, `spawndist`=10 WHERE id=1766;

-- Gorefang
DELETE FROM creature WHERE guid = 129600;
UPDATE `creature` SET `MovementType`=1, `spawndist`=5 WHERE id=12431;

-- Ferocious Grizzled Bear
UPDATE `creature` SET `MovementType`=1, `spawndist`=10 WHERE id=1778;

-- Giant Rabid Bear
UPDATE `creature` SET `MovementType`=1, `spawndist`=10 WHERE id=1797;

-- Bloodfang Scavenger
UPDATE `creature` SET `MovementType`=1, `spawndist`=10 WHERE id=44549;

-- Skitterweb Lurker
UPDATE `creature` SET `MovementType`=1, `spawndist`=10 WHERE id=1781;

-- Northwatch Scout
UPDATE `creature` SET `MovementType`=1, `spawndist`=8 WHERE id=39317;

-- Vile Familiar
UPDATE `creature` SET `MovementType`=1, `spawndist`=5 WHERE id=3101;

-- Mana Wyrm
UPDATE `creature` SET `MovementType`=1, `spawndist`=5 WHERE id=15274;
UPDATE `creature_template` SET `InhabitType`=3 where entry=15274;