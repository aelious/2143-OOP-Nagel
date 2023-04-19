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
    
    # Different way to create an cpp style overloaded operator in python!
    # Allows you to format a class for easy printing. So when we print the 
    # instance, this is how we want it structured!
    def __str__(self) -> str:
        return "[{}]".format(self.sides)

class Dice:
    # Creates a list
    dice = []

    def __init__(self, n, s):
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
                print("Dice {}: rolled a {} out of a possible {}! Current sum is {}.".format(currRoll, tempNum,i.sides, sum))
                currRoll += 1
            rolls -= 1
        print("** WOW! We scored a total of {} pips! **".format(sum))
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
    b = Die(420)
    print("Roll a {} out of 420.".format(b.roll()))
    d = Dice(5, 30)
    d.roll()
    print(len(d.dice))
    print(d.maxRoll())
    print(d.avgRoll())