from character import Character
from classes import *

myChar = Character()
myChar.printStats()

myBarb = Barbarian()
myBarb.printStats()
print(myBarb.primaryStats)

myBard = Bard()
print(myBard.primaryStats)

mySB = Spellblade

myBarb.equipWeapon("Battleaxe")
myBarb.equipWeapon("Crossbow")
myBarb.unequipWeapon()
myBarb.equipWeapon("Crossbow")
myBarb.equipWeapon("Eye of Sauron")
myBarb.equipWeapon("Greatsword")
myBarb.checkInventory()

myBard.learnSpell("HEAL")
myBard.attack("spell", "HEAL")
myBard.learnSpell("NERF")
myBard.printStats()
myBard.attack("spell", "NERF")
myBard.printStats()
myBard.checkInventory()