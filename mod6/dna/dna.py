import csv
from collections import Counter
csvFileName = input("Wriite the name of csv file ")
txtFileName = input("Writte the name of txt file ")
txt_path = f"dna\\sequences\\{txtFileName}.txt"
csv_path = f"dna\\databases\\{csvFileName}.csv"
data = {}
with open(csv_path, 'r') as fileCsv:
    reader_csv = csv.DictReader(fileCsv)

    for line in reader_csv:
        name = line['name']

        sequences_str = {key: int(valor) for key, valor in line.items() if key != 'name'}
        data[name] = sequences_str

keys = list(sequences_str.keys())
matches = []

def count_letters(txt_path, arrayLetters):
    with open(txt_path, "r") as fileTxt:
        reader_txt = fileTxt.read();

    countTheLetters = {letter : 0 for letter in arrayLetters}

    for letter in arrayLetters:
        countTheLetters[letter] += reader_txt.count(letter)
    for letter, count in countTheLetters.items():
        for name, sequences_str in data.items():
            for key, value in sequences_str.items():
                if(key == letter and value == count):
                    matches.append(name)
count_letters(txt_path, keys)

count_m = Counter(matches)
if count_m:
    count_matches = count_m.most_common(1)[0][1]
    if count_matches == 3:
        mostCommon = count_m.most_common(1)[0][0]
        print(mostCommon)
    else:
        print("Not match")
else:
    print("Not match")
