# import everything from dice.py (in the same directory)
from dice import *

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


if __name__ == "__main__":
    main()
