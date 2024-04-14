from cs50 import get_string
import string

text = get_string("Text: ")
letters = 0
words = 1
sentences = 0


for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    if text[i].isspace():
        words += 1
    if text[i] == "!" or text[i] == "." or text[i] == "?":
        sentences += 1


l = (100 / words) * letters
s = (100 / words) * sentences

score = round(0.0588 * l - 0.296 * s - 15.8)

if score > 16:
    print("Grade 16+")

elif score < 1:
    print("Before Grade 1")
else:
    print(f"Grade {score}")
