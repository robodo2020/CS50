from cs50 import *
import re

# User input
text = get_string("Text:")


SentenceNum = LetterNum = 0
L = S = index = 0
WordNum = 1
for i in range(len(text)):
    # Count for sentences
    if re.search("\!|\.|\?", text[i]):  # 找特殊字元方式加上\
        SentenceNum += 1
    # Count for words
    if re.search(" |'", text[i]):   # 記得要判斷I've是兩個字, 但如果是'S要排除
        WordNum += 1
        if text[i] == "\'" and text[i + 1] == 's':
            WordNum -= 1
    # Count for letters
    if re.search("[A-Z]", text[i], re.IGNORECASE):
        LetterNum += 1
# regex = re.compile("'s")
# mo = regex.search(text)
# if mo.group():
#     WordNum -= 1

print(f"You have {SentenceNum} sentences.")
print(f"You have {WordNum} words.")
print(f"You have {LetterNum} letters.")
# Calculate for readability.
L = LetterNum * 100 // WordNum
S = SentenceNum * 100 // WordNum
index = 0.0588 * L - 0.296 * S - 15.8

if (round(index) < 1):
    print("Before Grade 1")
elif(round(index) > 16):
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")