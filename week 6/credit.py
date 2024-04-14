from cs50 import get_int

creditnum = get_int("Number: ")
count = 0
tempnum = creditnum

while tempnum > 0:
    count += 1
    tempnum = tempnum // 10

sum = 0
newcreditnum = creditnum

for i in range(count):
    if (i % 2) == 0:
        digit = (newcreditnum % 10) * 2
        newcreditnum = newcreditnum // 10

        if digit > 9:
            sum += digit // 10
            sum += digit % 10
            continue

        sum += digit

    else:
        digit = newcreditnum % 10
        sum += digit
        newcreditnum = newcreditnum // 10


if (sum % 10) != 0:
    print("INVALID")

firstdigi = creditnum

while firstdigi >= 100:
    firstdigi = firstdigi // 10

if (count == 15) and ((firstdigi == 37) or (firstdigi == 34)):
    print("AMEX")

if (count == 16) and (
    (firstdigi == 51)
    or (firstdigi == 52)
    or (firstdigi == 53)
    or (firstdigi == 54)
    or (firstdigi == 55)
):
    print("MASTERCARD")

sinfirstdigi = creditnum

while sinfirstdigi >= 10:
    sinfirstdigi = sinfirstdigi // 10

if ((count == 13) or (count == 16)) and ((sinfirstdigi == 4)):
    print("VISA")
