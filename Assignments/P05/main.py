from character import Character
from classes import *
import json

myChar = Character()
myChar.printStats()

myBarb = Barbarian()
myBarb.printStats()
print(myBarb.primaryStats)

myBard = Bard()
print(myBard.primaryStats)

mySB = Spellblade

myBarb.equipWeapon("Battleaxe")



""" o = open('weapons.txt', "a")
f = open('weapons.json')
data = json.load(f)
for i in data:
    dmgText = i["Damage"]
    keepText = ""
    if len(dmgText) != 0:
        keepText += "d" + dmgText[2] + "_" + dmgText[0]
    o.write('\t"{}": [{}, "{}"],\n'.format(i["Name"], keepText, i["Damage"][4:])) """