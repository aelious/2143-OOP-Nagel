from character import *
from weaponsAndSpells import *

# Took the primary stats from: https://www.enworld.org/threads/classes-primary-stat-secondary-stat.616720/


class Barbarian(MeleeUser):
    description = "A primal warrior who relies on physical strength and raw fury to overpower their foes."
    primaryStats = ["STR", "CON"]
    equippableWeapons = ["axe", "mace", "sword"]
    def __init__(self):
        super().__init__()

class Bard(MixedUser):
    description = "A performer with magical abilities who uses music and storytelling to inspire allies and hinder enemies."
    primaryStats = ["CHA", "INT"]
    equippableWeapons = ["mace"]
    spells = ["HEAL"]
    def __init__(self):
        super().__init__()

class Cleric(MagicUser):
    description = "A divine spellcaster who channels the power of their deity to heal allies, smite enemies, and perform miracles."
    primaryStats = ["WIS", "CHA"]
    equippableWeapons = ["mace"]
    def __init__(self):
        super().__init__()

class Druid(MixedUser):
    description = "A nature-based spellcaster who draws on the power of the natural world to cast spells, transform into animals, and commune with plants and animals."
    primaryStats = ["WIS", "DEX"]
    equippableWeapons = ["mace", "staff"]
    def __init__(self):
        super().__init__()

class Fighter(MeleeUser):
    description = "A skilled combatant who is highly trained in weapons and armor, and can use a variety of tactics to excel in combat."
    primaryStats = ["STR", "CON"]
    equippableWeapons = ["sword", "axe"]
    def __init__(self):
        super().__init__()

class Monk(MeleeUser):
    description = "A disciplined warrior who uses martial arts and a monk's traditional weapons to fight with both physical and mental prowess."
    primaryStats = ["DEX", "WIS"]
    equippableWeapons = ["mace", "staff"]
    def __init__(self):
        super().__init__()

class Paladin(MixedUser):
    description = "A holy knight who combines martial prowess with divine magic to serve a cause or deity."
    primaryStats = ["CHA", "STR"]
    equippableWeapons = ["mace", "sword"]
    def __init__(self):
        super().__init__()

class Ranger(MeleeUser):
    description = "A skilled outdoorsman who is highly attuned to nature and uses their expertise to track, hunt, and survive in the wilderness."
    primaryStats = ["STR", "DEX"]
    equippableWeapons = ["dagger", "ranged"]
    def __init__(self):
        super().__init__()

class Rogue(MixedUser):
    description = "A sneaky thief who excels at stealth, deception, and picking locks, and can use their cunning to gain an advantage in combat."
    primaryStats = ["DEX", "CHA"]
    equippableWeapons = ["dagger", "sword"]
    def __init__(self):
        super().__init__()

class Sorcerer(MagicUser):
    description = "A spellcaster who has innate magical abilities and can cast spells without relying on external sources of power."
    primaryStats = ["CON", "INT"]
    equippableWeapons = ["dagger", "mace", "staff"]
    def __init__(self):
        super().__init__()

class Warlock(MagicUser):
    description = "A spellcaster who has made a pact with a powerful being, granting them magical abilities and otherworldly powers."
    primaryStats = ["INT", "CON"]
    equippableWeapons = ["dagger", "staff"]
    def __init__(self):
        super().__init__()

class Wizard(MagicUser):
    description = "A scholarly spellcaster who learns magic through study and can cast spells from a wide range of schools and disciplines."
    primaryStats = ["INT", "WIS"]
    equippableWeapons = ["dagger", "staff"]
    def __init__(self):
        super().__init__()


Spellblade = type((Fighter, Sorcerer))

Shadowdancer = type((Rogue, Bard))

Shapeshifter = type((Druid, Monk))

HolyAvenger = type((Paladin, Ranger))

EldritchAssassin = type((Warlock, Rogue))

BattleMage = type((Wizard, Fighter))

FuryFist = type((Barbarian, Monk))