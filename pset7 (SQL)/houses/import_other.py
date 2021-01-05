import re
from sys import *
import cs50
import csv


def sepname(studentdic):
    name = studentdic.split()
    # return (name if len(name)==3 else [name[0],None,name[1]])
    if len(name) == 3:
        return name
    elif len(name) == 2:
        name.insert(1, None)
        return name


# Check command-line argument
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

#  Open CSV file by command arg
# use DictReader to save data
db = cs50.SQL("sqlite:///students.db")
studentdic = {}
# db.execute("CREATE TABLE trysql (first TEXT, middle TEXT, last TEXT, house TEXT, birth INT)")
with open(argv[1], newline='') as studentdata:
    studentdic = csv.DictReader(studentdata)
    for row in studentdic:
        nameseparate = sepname(row['name'])
        sql = "INSERT INTO students (first, middle, last, house, birth) VALUES (%s, %s, %s, %s, %s)"
        val = (nameseparate[0], nameseparate[1], nameseparate[2], row['house'], row['birth'])
        db.execute(sql, val)
