from character import Character
from math import floor

# Took the primary stats from: https://www.enworld.org/threads/classes-primary-stat-secondary-stat.616720/

class Barbarian(Character):
    description = "A primal warrior who relies on physical strength and raw fury to overpower their foes."
    primaryStats = ["STR", "CON"]
    def __init__(self):
        super().__init__()

class Bard(Character):
    description = "A performer with magical abilities who uses music and storytelling to inspire allies and hinder enemies."
    primaryStats = ["CHA", "INT"]
    def __init__(self):
        super().__init__()

class Cleric(Character):
    description = "A divine spellcaster who channels the power of their deity to heal allies, smite enemies, and perform miracles."
    primaryStats = ["WIS", "CHA"]
    def __init__(self):
        super().__init__()

class Druid(Character):
    description = "A nature-based spellcaster who draws on the power of the natural world to cast spells, transform into animals, and commune with plants and animals."
    primaryStats = ["WIS", "DEX"]
    def __init__(self):
        super().__init__()

class Fighter(Character):
    description = "A skilled combatant who is highly trained in weapons and armor, and can use a variety of tactics to excel in combat."
    primaryStats = ["STR", "CON"]
    def __init__(self):
        super().__init__()

class Monk(Character):
    description = "A disciplined warrior who uses martial arts and a monk's traditional weapons to fight with both physical and mental prowess."
    primaryStats = ["DEX", "WIS"]
    def __init__(self):
        super().__init__()

class Paladin(Character):
    description = "A holy knight who combines martial prowess with divine magic to serve a cause or deity."
    primaryStats = ["CHA", "STR"]
    def __init__(self):
        super().__init__()

class Ranger(Character):
    description = "A skilled outdoorsman who is highly attuned to nature and uses their expertise to track, hunt, and survive in the wilderness."
    primaryStats = ["STR", "DEX"]
    def __init__(self):
        super().__init__()

class Rogue(Character):
    description = "A sneaky thief who excels at stealth, deception, and picking locks, and can use their cunning to gain an advantage in combat."
    primaryStats = ["DEX", "CHA"]
    def __init__(self):
        super().__init__()

class Sorcerer(Character):
    description = "A spellcaster who has innate magical abilities and can cast spells without relying on external sources of power."
    primaryStats = ["CON", "INT"]
    def __init__(self):
        super().__init__()

class Warlock(Character):
    description = "A spellcaster who has made a pact with a powerful being, granting them magical abilities and otherworldly powers."
    primaryStats = ["INT", "CON"]
    def __init__(self):
        super().__init__()

class Wizard(Character):
    description = "A scholarly spellcaster who learns magic through study and can cast spells from a wide range of schools and disciplines."
    primaryStats = ["INT", "WIS"]
    def __init__(self):
        super().__init__()


Spellblade = type((Fighter, Sorcerer))

Shadowdancer = type((Rogue, Bard))

Shapeshifter = type((Druid, Monk))

HolyAvenger = type((Paladin, Ranger))

EldritchAssassin = type((Warlock, Rogue))

BattleMage = type((Wizard, Fighter))

FuryFist = type((Barbarian, Monk))