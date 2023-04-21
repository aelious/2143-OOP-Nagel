from dice import Dice
from math import floor
from weapons import Weapons

w = Weapons()

class Character(object):
    d20_1 = Dice(1, 20)
    d6_1 = Dice(1, 6)
    primaryStats = []
    equippableWeapons = []
    equippedWeapon = ""
    

    def __init__(self):
        self.Stats = {"STR":0, "DEX":0, "CON":0, "INT":0, "WIS":0, "CHA":0}
        self.rollStats(self.Stats)
        self.boostPrimaryStats()
        self.inventory = []
        
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
        pass
    
class MeleeUser(Character):
    attacks = []
    equippedWeapon = ""
    
    def __init__(self):
        super().__init__()
    
    def attack(self):
        if (type == "attack"):
            damage = w.availableWeapons[self.equippedWeapon][0].roll()
            print("You dealt {}!".format(damage))

class MixedClass(Character):
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
                print("You cast {}!")
            else:
                print("You don't know that spell...")