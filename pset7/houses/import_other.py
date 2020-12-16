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


# TODO Check command-line argument
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# TODO Open CSV file by command arg
# 使用DictReader儲存資料
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
        # 要處理要在with open 內 不然I/O operation就會close file
        # 可是之前解法用reader儲存就沒這問題為啥?
        # 因為原本的有用list(csv.reader) 不然一樣會報錯