import re
from sys import *
import cs50
import csv
# check command-line arguments
if len(argv) != 2:
    print("Usage: python roster.py Gryffindor")
    exit(1)
# Query database for all students in house
db = cs50.SQL("sqlite:///students.db")
name = db.execute("SELECT first, middle, last, birth FROM students WHERE house = %s ORDER BY last ASC, first ASC", argv[1])
# print out each student's full name and birth year
print(name)
# print(type(name[0]))

for i in name:
    if i['middle'] == None:
        print(f"{i['first']} {i['last']}, born {i['birth']}")
    else:
        print(f"{i['first']} {i['middle']} {i['last']}, born {i['birth']}")