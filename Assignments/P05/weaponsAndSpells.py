from dice import Dice

d1_1 = Dice(1, 1)
d2_1 = Dice(2, 1)
d3_1 = Dice(3, 1)
d4_1 = Dice(1, 4)
d4_2 = Dice(2, 4)
d6_1 = Dice(1, 6)
d6_2 = Dice(2, 6)
d6_3 = Dice(3, 6)
d8_1 = Dice(1, 8)
d8_2 = Dice(2, 8)
d8_3 = Dice(3, 8)
d10_1 = Dice(1, 10)
d10_2 = Dice(2, 10)

availableSpells = {
    "DONT DO THIS TO ME": ["PLEASE", "DONT MAKE ME IMPLEMENT SPELLS"],
    "HEAL": ["healing", d10_1],
    "DAMAGE": ["damage", d8_1],
    "BUFF": ["buff"],
    "NERF": ["nerf"]
}

availableAttacks = {
    "MASSIVE ATTACK WOW": ["maw", d10_2],
    "HUGE DEATH CRUSH": ["hdc", d8_2],
    "BIG WOMBO COMBO": ["bwc", d8_3]
}

availableWeapons = {
    "Battleaxe": [d8_1, "slashing", "axe"],
    "Flail": [d8_1, "bludgeoning", "mace"],
    "Greataxe": [d10_1, "slashing", "axe"],
    "Greatsword": [d6_2, "slashing", "sword"],
    "Halberd": [d10_1, "slashing", "axe"],
    "Longsword": [d8_1, "slashing/piercing", "sword"],
    "Morningstar": [d8_1, "piercing/bludgeoning", "mace"],
    "Rapier": [d8_1, "piercing", "sword"],
    "Scimitar": [d6_1, "slashing", "sword"], 
    "Shortsword": [d6_1, "piercing", "sword"],
    "War Pick": [d8_1, "piercing", "mace"],
    "Club": [d4_1, "bludgeoning", "mace"],
    "Dagger": [d4_1, "piercing", "dagger"],
    "Handaxe": [d6_1, "slashing", "axe"],
    "Javelin": [d6_1, "piercing", "ranged"],
    "Mace": [d6_1, "bludgeoning", "mace"],
    "Sickle": [d4_1, "slashing", "sword"],
    "Quarterstaff": [d6_1, "bludgeoning", "staff"],
    "Staff": [d6_1, "bludgeoning", "staff"],
    "Spear": [d4_1, "piercing", "ranged"],
    "Crossbow": [d8_1, "piercing", "ranged"],
    "Dart": [d4_1, "piercing", "ranged"],
    "Shortbow": [d6_1, "piercing", "ranged"],
    "Sling": [d4_1, "bludgeoning", "ranged"],
    "Longbow": [d8_1, "piercing", "ranged"]
}