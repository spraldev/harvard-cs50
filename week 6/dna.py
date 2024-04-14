import csv
import sys


def main():

    db = sys.argv[1]
    sq = sys.argv[2]


    dbrows = []
    dbhead = []

    with open(db) as file:
        reader = csv.DictReader(file)
        for row in reader:
            dbrows.append(row)

    with open(db) as file:
        reader = csv.DictReader(file)
        dbhead = reader.fieldnames

    dbhead.pop(0)

    f = open(sq)
    dna = f.read()
    f.close()

    compdict = {}

    for i in range(len(dbhead)):
        compdict[dbhead[i]] = 0


    for i in dbhead:
        counter = 0
        max = 0

        j = 0

        while (j < len(dna)):
            if(dna[j:j+len(i)] == i):
                counter += 1
                j+=len(i)
            else:
                if(counter > max):
                    max = counter
                j += 1

        compdict.update({i: max})
        counter = 0



    for i in dbrows:
        found = False
        found_count = 0
        for j in dbhead:
            if(compdict[j] == i[j]):
                found = True
                found_count += 1

                if(found and found_count == len(dbhead)):
                    print(i['name'])






    return

