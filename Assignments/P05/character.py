from dice import Dice
from math import floor

class Character(object):
    d20_1 = Dice(1, 20)
    d6_1 = Dice(1, 6)
    primaryStats = []

    def __init__(self):
        self.Stats = {"STR":0, "DEX":0, "CON":0, "INT":0, "WIS":0, "CHA":0}
        self.rollStats(self.Stats)
        self.boostPrimaryStats()
        
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

    def boostPrimaryStats(self):
        for k in self.Stats:
            if (k in self.primaryStats):
                print("BOOSTING {}: {}".format(k, self.Stats[k]))
                self.Stats[k] *= 1.3
                self.Stats[k] = floor(self.Stats[k])
                print("BOOSTED {}: {}".format(k, self.Stats[k]))