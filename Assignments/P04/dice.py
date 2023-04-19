# I'm going to be using a lot of this to get comfortable using Python again, so there
# will be a lot of extraneous comments that won't help with code function so much as
# syntax reminders and implementation!

# Importing libraries is the same as #include <someLibrary> in cpp
import random 

# Class declaration in python. Every in-line method will require 'self' as a parameter!
class Die:
    # This is a constructor in python! It sets sides = 6 if no value is given to s
    def __init__(self, s = None):
        # Implemented error checking here! :-) You're not allowed to tell me you have a 
        # 'pokemon' sided die >:-( I will change that to 6.
        if s == None or isinstance(s, int) == False:
            s = 6
        self.sides = s

    def roll(self, rolls=1):
        sum = 0
        while rolls > 0:
            sum += (random.randint(1, self.sides))
            rolls -= 1
        return sum
    
    # Different way to create a cpp style overloaded operator in python!
    # Allows you to format a class for easy printing. So when we print the 
    # instance, this is how we want it structured!
    def __str__(self) -> str:
        return "[{}]".format(self.sides)

class Dice:
    def __init__(self, n, s = None):
        self.dice = []
        if isinstance(n, str):
            temp = n.split('.')
            n = int(temp[0])
            s = int(temp[2])
        while (n > 0):
            # Calls the constructor for Die, pushes the instance onto our dice list
            self.dice.append(Die(s))
            n -= 1
    
    def __str__(self) -> str:
        output = ""
        for i in self.dice:
            output += str(i)
        return output

    def roll(self, rolls=1):
        sum = 0
        while (rolls > 0):
            currRoll = 1
            for i in self.dice:
                tempNum = i.roll(1)
                sum += tempNum
                currRoll += 1
            rolls -= 1
        return sum
    
    def maxRoll(self) -> int:
        max = 0
        for i in self.dice:
            max += i.sides
        return max
    
    def avgRoll(self) -> int:
        avg = 0
        for i in self.dice:
            # We use + 1 here since 0 is not included in our avg
            avg += (i.sides + 1) / 2
        return avg
    
if __name__ == '__main__':
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
    print("Our rolled dice totalled {} out of a possible {}".format(myDice.roll(),myDice.maxRoll()))

    # 5 dice * 8 sides = 40 maximum pips...prints 40. I can do maths yay :-)
    print("\nMaximum roll in our current set of dice: {}".format(myDice.maxRoll()))

    # 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 = 36 / 8 = 4.5 avg per dice * 5 total dice = 22.5
    print("Average roll of our current set of dice: {}".format(myDice.avgRoll()))

    # Create a dice via a string
    l = Dice('4.d.20')
    print("\n{}".format(l))