from csv import *
from sys import *
import re


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
    for i in range(1, len(namelist) - 1, 1):
        if dnacompare in namelist[i]:
            resultregex = re.compile(r'[a-z]+', re.I)
            mo = resultregex.match(namelist[i])
            return mo.group()
    return "No match"
    

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# open file typed in terminal
namefile = open(argv[1], "r")
dnafile = open(argv[2], "r")

# seperate each line and store line in list ex:namelist[0] means one line, but can use csv...
namedata = namefile.readlines()  # namedata 
namelist = []
for i in namedata:
    namelist.append(i)
# separate the first line in order to get STR sequence rule for using
dnaSTR = re.split(r'[,\n]', namelist[0]) 

# read DNA sequence
whosdna = dnafile.readline()

# check the longest STR inside DNA sequence
DNAresult = []
for i in range(1, len(dnaSTR) - 1, 1):
    DNAresult.append(MaxContinuousSTR(i))

dnacompare = ','.join(DNAresult)

print(checkDNAname())