from cs50 import *
import re

while True:
    number = get_int("Number:")
    if number > 0:
        break
digit = len(str(number))
digitArray = list(str(number)) 
odd = 0
even = 0
#  chekc whether the digit is correct
if digit in [13, 15, 16, 3]:
    # check the head
    if(re.search("^5[1-5]", str(number)) or re.search("^34|37", str(number)) or re.search("4", str(number))):
        # use Luhn algorithm，i loop inside digitArray
        # Therefore, i == digitArray[0,1,2..]
        for i in digitArray[digit - 2: -1: -2]:
            print("in1")
            odd = odd + (int(i) * 2 // 10) + (int(i) * 2 % 10)
        for j in digitArray[digit - 1: -1: -2]:
            print("in2")
            even = even + int(j)
        # use Luhn algorithm
        total = odd + even
        if total % 10 == 0:
            # check and print the result for the card
            if digit == 15:
                print("AMEX")
            elif digit == 13 or (digit == 16 and int(digitArray[0]) == 4):  # since type(digitArray) == string, change to int
                print("VISA")
            elif digit == 16 and digitArray[0] == '5': 
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")
