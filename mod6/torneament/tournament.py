import csv
import sys
import random

# Number of simluations to run
N = 1000

teams = []
def main():
    csvName = input("Writte the file name ")
    csvPath = f"torneament\\{csvName}.csv"
    with open (csvPath, 'r') as FileCsv:
        reader_csv = csv.DictReader(FileCsv)
        for line in reader_csv:
            processed_line = {'team': line['team'], 'rating' : int(line['rating'])}
            teams.append(processed_line)



def simulate_game(team1, team2):
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability

def simulate_round(teams):
    winners = []
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners


def simulate_tournament(teams):
    while(len(teams) > 1):
        teams = simulate_round(teams)
    return teams[0]['team']



if __name__ == "__main__":
    main()

counts = {}
for i in range(N):
    winner = simulate_tournament(teams)
    if winner in counts:
        counts[winner] += 1
    else:
        counts[winner] = 1


for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")