from dice import Dice
from math import floor
from weaponsAndSpells import *

w = Weapons()
s = Spells()

class Character(object):
    d20_1 = Dice(1, 20)
    d6_1 = Dice(1, 6)
    primaryStats = []
    equippableWeapons = []
    
    def __init__(self):
        self.Stats = {"STR":0, "DEX":0, "CON":0, "INT":0, "WIS":0, "CHA":0}
        self.rollStats(self.Stats)
        self.boostPrimaryStats()
        self.inventory = []
        self.equippedWeapon = ""

    def rollStats(self, statList):
        for k in self.Stats:
            statList[k] = self.generateStat()
    
    def printStats(self):
        for k in self.Stats:
            print(k, self.Stats[k])

    def generateStat(self) -> int:
        self.diceRolls = []
        # Roll 4 d6 to generate stats
        for i in range(4):
            self.diceRolls.append(self.d6_1.roll())
        self.diceRolls.sort()
        # Remove lowest rolled value!
        self.diceRolls.pop(0)
        # Return highest 3 rolled values!
        return sum(self.diceRolls)
    
    def equipWeapon(self, weapon):
        if (len(self.equippedWeapon) != 0):
            print("You already have a weapon equipped! Take it off first!")
        else:
            if (weapon in w.availableWeapons.keys()):
                typeOfWeap = w.availableWeapons[weapon][2]
                if (typeOfWeap in self.equippableWeapons):
                    self.equippedWeapon = weapon
                    print("You equipped a {}!".format(weapon))
                else:
                    print("That weapon exists but your class can't equip it!")
            else:
                print("That weapon doesn't exist!!...")
    
    def unequipWeapon(self):
        if(len(self.equippedWeapon) == 0):
            print("You don't have a weapon equipped!")
        else:
            self.inventory.append(self.equippedWeapon)
            print("Removing {}.".format(self.equippedWeapon))
            self.equippedWeapon = ""

    def checkInventory(self):
        if len(self.inventory) == 0:
            print("You have nothing in your inventory!")
            return
        print("Inventory:\n==========")
        for i in self.inventory:
            print(i)

    def boostPrimaryStats(self):
        for k in self.Stats:
            if (k in self.primaryStats):
                print("BOOSTING {}: {}".format(k, self.Stats[k]))
                self.Stats[k] *= 1.3
                self.Stats[k] = floor(self.Stats[k])
                print("BOOSTED {}: {}".format(k, self.Stats[k]))

class MagicUser(Character):
    spells = []
    def __init__(self):
        super().__init__()
    
    def attack(self, spell):
        if (spell in self.spells):
            print("You cast {}!".format(spell))
        else:
            print("You don't know that spell...")
    
class MeleeUser(Character):
    attacks = []

    def __init__(self):
        super().__init__()
    
    def attack(self):
        if (len(self.equippedWeapon) != 0):
            damage = w.generateDamage(self.equippedWeapon)
            print("You dealt {} damage!".format(damage))
        else:
            print("You punch them for 1 damage... Maybe try equipping a weapon.")

class MixedUser(Character):
    spells = []
    attacks = []
    def __init__(self):
        super().__init__()

    def attack(self, type, spell = None):
        if (type == "attack"):
            damage = w.availableWeapons[self.equippedWeapon][0].roll()
            print("You dealt {}!".format(damage))
        if (type == "spell" and spell == None):
            print ("You need to tell me what you want to cast!")
        elif (type == "spell" and spell != None):
            if (spell in self.spells):
                print("You cast {}!".format(spell))
                s.castSpell(spell)
            else:
                print("You don't know that spell...")