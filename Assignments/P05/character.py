from dice import Dice
from math import floor
from weaponsAndSpells import *

class Character(object):
    d20_1 = Dice(1, 20)
    d6_1 = Dice(1, 6)
    primaryStats = []
    equippableWeapons = []
    description = ""
    
    def __init__(self, n):
        self.Stats = {"STR":0, "DEX":0, "CON":0, "INT":0, "WIS":0, "CHA":0}
        self.name = n
        self.rollStats(self.Stats)
        self.inventory = []
        self.equippedWeapon = ""

    def rollStats(self, statList):
        for k in self.Stats:
            statList[k] = self.generateStat()
        self.boostPrimaryStats()
    
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
        # Return sum of highest 3 rolled values!
        return sum(self.diceRolls)
    
    def equipWeapon(self, weapon):
        if (len(self.equippedWeapon) != 0):
            print("You already have a weapon equipped! Take it off first!")
        else:
            if (weapon in availableWeapons.keys()):
                typeOfWeap = availableWeapons[weapon][2]
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

    def buffStats(self):
        for k in self.Stats:
            self.Stats[k] *= 1.2
            self.Stats[k] = floor(self.Stats[k])

    def nerfStats(self):
        for k in self.Stats:
            self.Stats[k] *= .8
            self.Stats[k] = floor(self.Stats[k])

    def printCharacterSheet(self):
        print("~~~ {} ~~~\n===================".format(self.name))
        print("Class:\n{}".format(self.__class__.__name__))
        print("Story:\n{} is {}".format(self.name, self.description))
        print("Stats:")
        self.printStats()
        print("Primary Stats: {}".format(self.primaryStats))

    

class MagicUser(Character):
    def __init__(self, n):
        self.spells = []
        super().__init__(n)
    
    def magicAttack(self, spell):
        if (spell in self.spells and spell in availableSpells):
            print("You cast {}!".format(spell))
            self.castSpell(spell)
        else:
            print("You don't know that spell...")

    def castSpell(self, spell):
        if(availableSpells[spell][0] == "healing"):
            healing = availableSpells[spell][1].roll()
            print("You healed {} hitpoints!".format(healing))
        elif(availableSpells[spell][0] == "damage"):
            damage = availableSpells[spell][1].roll()
            print("You dealt {} damage!".format(damage))
        elif(availableSpells[spell][0] == "buff"):
            self.buffStats()
            print("BUFFED STATS, YOU'RE INSANE NOW! WOW")
        elif(availableSpells[spell][0] == "nerf"):
            self.nerfStats()
            print("Yeah I guess I need to implement targeting... You nerfed yourself.")

    def learnSpell(self, spell):
        if(spell in availableSpells):
            self.spells.append(spell)
    
class MeleeUser(Character):
    def __init__(self, n):
        self.attacks = []
        super().__init__(n)
    
    def generateDamage(self, weapon):
        return availableWeapons[weapon][0].roll()
    
    def learnAttack(self, attack):
        if(attack in availableAttacks and attack not in self.attacks):
            self.attacks.append(attack)    

    def meleeAttack(self):
        if (len(self.equippedWeapon) != 0):
            damage = self.generateDamage(self.equippedWeapon)
            print("You dealt {} damage!".format(damage))
        else:
            print("You punch them for 1 damage... Maybe try equipping a weapon.")

class MixedUser(MagicUser, MeleeUser):
    def __init__(self, n):
        super().__init__(n)
    
    def attack(self, type, spell = None):
        if (type == "attack"):
            super().meleeAttack()
        elif (type == "spell" and spell != None):
            super().magicAttack(spell)

