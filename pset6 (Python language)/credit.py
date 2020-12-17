from cs50 import *
import re

while True:
    number = get_int("Number:")
    if number > 0:
        break
digit = len(str(number))
digitArray = list(str(number))  # 注意這邊儲存的是string的 list 所以要做計算時一定要做轉換
odd = 0
even = 0
#  檢查位數是否正確
if digit in [13, 15, 16, 3]:
    # 檢查開頭
    if(re.search("^5[1-5]", str(number)) or re.search("^34|37", str(number)) or re.search("4", str(number))):
        # 跑Luhn算法，這邊注意，i是在digitArray裡面loop，
        # 所以i會等於 digitArray[0,1,2..]的數，因此如果for內用digitArray[i]處理會報錯
        for i in digitArray[digit - 2: -1: -2]:
            print("in1")
            odd = odd + (int(i) * 2 // 10) + (int(i) * 2 % 10)
        for j in digitArray[digit - 1: -1: -2]:
            print("in2")
            even = even + int(j)
        # 跑Luhn算法
        total = odd + even
        if total % 10 == 0:
            # 最後檢查屬於哪個卡 print出結果
            if digit == 15:
                print("AMEX")
            elif digit == 13 or (digit == 16 and int(digitArray[0]) == 4):  # 因為digitArray是string 所以要比對要轉成int
                print("VISA")
            elif digit == 16 and digitArray[0] == '5':  # 或者不轉用'5'也可以
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")
