# import everything from dice.py (in the same directory)
from dice import *


# Create an instance of Die called d with sides = 4
d = Die(4)

# Prints 4
print("Sides of our dice = {}".format(d.sides))

print("\nCool, now let's roll our {}-sided die twice three times!".format(d.sides))
# Rolls our 4-sided die twice, 3 times!
for i in range(1, 4):
    print("Two-Roll Results {}: {}".format(i, d.roll(2)))

# Error testing for bad inputs >:-( I told you you can't make a 'pokemon'-sided die!
m = Die('pokemon')

# Prints 6, get rekt
print("\nSides of our 'pokemon' dice = {}\nHaha >:-(".format(m.sides))

# Create a set of dice containing 5 8-sided die
myDice = Dice(5, 8)

print("\nOur new shiny set of dice:")
# Prints our set of dice
print(myDice)

print("\nLets roll each of the dice in our set once!")
# Roll each of our 5 dice 1 time
myDice.roll()

# 5 dice * 8 sides = 40 maximum pips...prints 40. I can do maths yay :-)
print("\nMaximum roll in our current set of dice: {}".format(myDice.maxRoll()))

# 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 = 36 / 8 = 4.5 avg per dice * 5 total dice = 22.5
print("\nAverage roll of our current set of dice: {}".format(myDice.avgRoll()))