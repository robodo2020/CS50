from sys import *
import cs50
import csv
# TODO check command-line arguments
if len(argv) != 2:
    print("Usage: python roster.py Gryffindor")
    exit(1)

# TODO Query database for all students in house
db = cs50.SQL("sqlite:///students.db")
name = db.execute("SELECT first, middle, last, birth FROM students WHERE house = %s ORDER BY last, first ASC", argv[1])
# TODO print out each student's full name and birth year
# try if else inside print
for i in name:
    print(f"{i['first']} {''if i['middle']== None else i['middle']+' '}{i['last']}, born {i['birth']}")