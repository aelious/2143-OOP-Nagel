#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#              
#  Author:           Stephanie Nagel
#  Email:            aeliousx@gmail.com
#  Label:            P04
#  Title:            Roll Them Bones!
#  Course:           CMPS 2143
#  Semester:         Spring 2023
# 
#  Description:
#        This program implements dice and die classes which have different
#        functionality such as the ability to roll your die, compute max
#        and average rolls of your different dice sets, and allows for easy
#        printing of the dice!
# 
#  Usage:
#        Inside directory: python main.py OR python dice.py
# 
#  Files:            main.py
#                    dice.py
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# main.py

# import everything from dice.py (in the same directory)
from dice import *

"""
# Function printDiceRange:
#     Rolls a given dice set a supplied number of times
#     or 1000 times if no amount of rounds is given.
#     Determines a minimum and maximum from these rounds
#     of rolling the dice and then prints the values.
# 
# Params:
#     diceInstance: Instance of a Dice (would also work  with a die)
#     rounds: The number of rounds of rolling to calculate the range
# 
# Returns:
#     N/A
"""
def printDiceRange(diceInstance, rounds = 1000):
    min = 999999
    max = 0
    while rounds > 0:
        tempNum = diceInstance.roll()
        if tempNum > max:
            max = tempNum
        if tempNum < min:
            min = tempNum
        rounds -= 1
    print("Min Roll: {}\nMax Roll: {}\n".format(min, max))

def main():
    d10_3 = Dice(3, 10)
    d12_4 = Dice("4.d.12")
    d20_5 = Dice("5.d.20")
    
    print(d10_3)
    printDiceRange(d10_3, 1000000)
    
    print(d12_4)
    printDiceRange(d12_4, 1000000)
    
    print(d20_5)
    printDiceRange(d20_5, 1000000)

    # Don't run this on a slow computer..

# Runs only if python is run on this file
if __name__ == "__main__":
    main()