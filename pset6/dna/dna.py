import csv
from sys import *
import re
# This version I use csv reader to store the file I opened in list straightforward
# So I don't need to seperate the data by myself and just use it as two dimensional array


# this function is for checking the maxium continuous STR in sequences
def MaxContinuousSTR(STR):
    STRnumber = []
    dnaregex = re.compile(rf'({dnaSTR[STR]})+')
    for j in dnaregex.finditer(whosdna):
        STRnumber.append((j.end() - j.start())//len(dnaSTR[STR]))
    if STRnumber == []:   # if didn't find any STR in sequences, print 0
        return '0'
    return str(max(STRnumber))  # use string for checkDNAname function to compare


# this function use re.match to find alphabets(name, namely, who's DNA) in line
def checkDNAname():
    for i in range(1, len(namelist), 1):
        if DNAresult == namelist[i][1:]:
            return namelist[i][0]
    return "No match"


if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# TODO open file typed in terminal
dnafile = open(argv[2], "r")
whosdna = dnafile.readline()  # 讀取DNA序列

with open(argv[1], newline='') as namefile:
    # csv output is iterator over rows and don't support index, so need to use list()
    namelist = list(csv.reader(namefile, delimiter=','))

dnaSTR = namelist[0]

# 判斷DNA序列裡面的STR最長連續有幾個
DNAresult = []
for i in range(1, len(dnaSTR), 1):
    DNAresult.append(MaxContinuousSTR(i))
# output result
print(checkDNAname())