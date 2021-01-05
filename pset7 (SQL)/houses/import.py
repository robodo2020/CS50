import re
from sys import *
import cs50
import csv

# Check command-line argument
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)
# Open CSV file by command arg
studentlist = []
with open(argv[1], newline='') as studentdata:
    studentlist = list(csv.reader(studentdata, delimiter=','))
# print(studentlist)
# For each row, parse name
name = []
for i in range(1, len(studentlist), 1):
    name.append(studentlist[i][0])
# print(name)
namesep = [[]] * len(name)
for i in range(len(name)):
    namesep[i] = re.split(r' ', name[i])
    # add null
    if len(namesep[i]) == 2:
        namesep[i].insert(1, None)
    namesep[i].insert(3, studentlist[i+1][1])  # +1 since studentlist[i] is table name
    namesep[i].insert(4, studentlist[i+1][2])
# print(namesep)

# Insert each student into the students table of student.db
db = cs50.SQL("sqlite:///students.db")

#db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT)")
for i in range(len(namesep)):
    sql = "INSERT INTO students (first, middle, last, house, birth) VALUES (%s, %s, %s, %s, %s)"
    val = (namesep[i][0], namesep[i][1], namesep[i][2], namesep[i][3], namesep[i][4])
    db.execute(sql, val)

