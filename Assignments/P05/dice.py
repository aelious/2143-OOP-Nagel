#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#              
#  Author:           Stephanie Nagel
#  Email:            aeliousx@gmail.com
#  Label:            P05
#  Title:            D&D
#  Course:           CMPS 2143
#  Semester:         Spring 2023
# 
#  Description:
#        WE MAKIN' CHARACTERS WOO WOOOOO
# 
#  Usage:
#        Inside directory: python main.py
# 
#  Files:            main.py
#                    dice.py
#                    character.py
#                    classes.py
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# dice.py

# Importing libraries is the same as #include <someLibrary> in cpp
from random import randint


"""
# Class Die
#
# Description:
#     This class implements a single die with a given number of sides (or 6 if a number is 
#     unavailable)
#
# Methods:
#     __init__(self, s)
#     roll(self, rolls)
#     __str__(self)
#    
"""
# Class declaration in python. Every in-line method will require 'self' as a parameter!
class Die:

    """
    # __init__
    # Description:
    #     This is a constructor in python! It sets the sides of the created die to s.
    #     If s is a bad type or isn't declared upon creation, sides will be set to 6.
    # Returns:
    #     N/A
    """
    def __init__(self, s = None):
        # Implemented error checking here! :-) You're not allowed to tell me you have a 
        # 'pokemon' sided die >:-( I will change that to 6.
        if s == None or isinstance(s, int) == False:
            s = 6
        self.sides = s

    """
    # __str__
    # Description:
    #     This is similar to ostream overloading in c++. We define how we'd like our
    #     die to be structured in the event that we print it.
    # Returns:
    #     The structured die as a string
    """
    def __str__(self) -> str:
        return "[{}]".format(self.sides)
    
    """
    # roll
    # Description:
    #     This method rolls our die a given number of times. If the number of times
    #     isn't declared, the die will only be rolled once!
    # Returns:
    #     The sum of the rounds of rolls of our die
    """
    def roll(self, rolls=1):
        sum = 0
        while rolls > 0:
            sum += (randint(1, self.sides))
            rolls -= 1
        return sum
    
"""
# Class Dice
#
# Description:
#     Implements a class that will hold n amount of die of side s. Allows for easy reuse
#     of popular die-combinations! E.g. Casting a popular spell that requires you to
#     roll 3 die with 20 sides to determine damage.
#
# Methods:
#     __init__(self, n, s)
#     __str__(self)
#     roll(self)
#     maxRoll(self)
#     avgRoll(self)
#
"""
class Dice:

    """
    # __init__
    # Description:
    #     Constructor for our Dice class. Creates n number of die, each with s sides.
    #     If n is a string, n and s will be determined by splitting up the string.
    # Returns:
    #     N/A
    """
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

    """
    # __str__
    # Description:
    #     Defines how we'd like our Dice class to be structured upon printing
    # Returns:
    #     The structured dice as a string
    """
    def __str__(self) -> str:
        output = ""
        for i in self.dice:
            output += str(i)
        return output

    """
    # roll
    # Description:
    #     This method rolls each of the die in our set of dice a given number of times. 
    #     If the number of times isn't declared, each die will only be rolled once!
    # Returns:
    #     The sum of the rounds of rolls of our die
    """   
    # This implementation will need to be reverted if mixed Dice sets are needed in
    # the future. For example, 4d20 plus a d3 or something like that.
    def roll(self, rolls=1):
        sum = 0
        while (rolls > 0):
            sum += self.dice[0].roll(len(self.dice))
            rolls -= 1
        return sum
    
    """
    # maxRoll
    # Description:
    #     This method determines the max possible sum of rolled die in the dice set
    # Returns:
    #     The maximum possible roll value of the set of dice
    """
    def maxRoll(self) -> int:
        max = 0
        for i in self.dice:
            max += i.sides
        return max
    
    """
    # avgRoll
    # Description:
    #     This method determines the average summed die rolls
    # Returns:
    #     The average total when rolling the set of dice
    """
    def avgRoll(self) -> int:
        avg = 0
        for i in self.dice:
            # We use + 1 here since 0 is not included in our avg
            avg += (i.sides + 1) / 2
        return avg

# Unnecessary but it makes for a cleaner output :-)
def main():
    # Create an instance of Die called d with sides = 4
    d = Die(4)

    # Prints the number of sides our newly created die has
    print("Sides of our dice = {}".format(d.sides))

    print("\nCool, now let's roll our {}-sided die twice three times!".format(d.sides))
    # Rolls our die twice, 3 times!
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
    print("Our rolled dice totalled {} out of a possible {}".format(myDice.roll(),
        myDice.maxRoll()))

    # 5 dice # 8 sides = 40 maximum pips...prints 40. I can do maths yay :-)
    print("\nMaximum roll in our current set of dice: {}".format(myDice.maxRoll()))

    # 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 = 36 / 8 = 4.5 avg per dice # 5 total dice = 22.5
    print("Average roll of our current set of dice: {}".format(myDice.avgRoll()))

    # Create a dice via a string
    l = Dice('4.d.20')
    print("\nDice set created from string!\n{}\n".format(l))

    d20_1 = Dice(1, 20)
    maxd20 = d20_1.maxRoll()

    # Trying to roll a 20 on a d20 5 times!
    for i in range(1, 6):
        temp = 0
        count = 0
        while(temp != maxd20):
            temp = d20_1.roll()
            count += 1
        print("Attempt {}: It took {} roll(s) to roll a 20 on a d20.".format(i, count))

# Runs only if python is run on this file
if __name__ == '__main__':
    main()