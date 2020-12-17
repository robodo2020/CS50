from cs50 import *

while True:
    h = get_int("Height:")
    if h > 8 or h < 1:
        print("invalid")
    else:
        break
for i in range(h):
    print(" "*(h-(i+1)) + "#" * (i+1) + "  " + "#" * (i+1))