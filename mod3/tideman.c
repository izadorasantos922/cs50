#include <stdio.h>
#include <string.h>
#define MAX_CANDIDATES 9

typedef struct{
	char name[20];
	int vote;
} candidates;

typedef struct {
	int winner;
	int loser;
} pair;
pair pairs[6];
candidates candidatesArray[9];

void addCandidate(char *candidatesInput, int *qtdycandidates, candidates candidatesArray[]){
	char *limiter = " ";
	char *token = strtok(candidatesInput, limiter);
	int i = 0;
	while(token != NULL && i < 9){
		strcpy(candidatesArray[i].name, token);
		(*qtdycandidates)++;
		i++;
		token = strtok(NULL, limiter);
	}
}
void vote(int voter,int rank, char name[], int qtdycandidates, int qtdyvoters, int ranks[][ MAX_CANDIDATES], candidates candidatesArray[]) {
	for(int i = 0; i < qtdycandidates ; i++){
		if(strcmp(candidatesArray[i].name, name) == 0){
			ranks[voter][rank] = i;
		}
	}
}

void record_preferences(int ranks[][MAX_CANDIDATES], int qtdycandidates, int qtdyvoters, int preferences[][MAX_CANDIDATES]){
	for (int i = 0; i < qtdyvoters; i++) {
        for (int j = 0; j < qtdycandidates; j++){
            for (int k = j+1; k < qtdycandidates; k++){
            preferences[ranks[i][j]][ranks[i][k]]++;
        }
        }
    }
}

void add_pair(int preferences[][MAX_CANDIDATES], int *pair_count, int qtdycandidates, pair pairs[]){
		for(int i = 0; i < qtdycandidates; i++){
			for(int j = 0; j < qtdycandidates; j++){
				if(preferences[i][j] > preferences[j][i]){
					pairs[*pair_count].winner = i;
					pairs[*pair_count].loser = j;
				}else{
					pairs[*pair_count].winner = j;
					pairs[*pair_count].loser = i;
				}
				(*pair_count)++;
			}
		}
}

void sort_pairs(int pairs[], int count_pairs, preferences[][MAX_CANDIDATES]){
	int temp;
	int index;
	for(int i = 0; i< count_pairs; i++){
		index = i;
		for(int j = i + 1; j < count_pairs; j++){
			current_strength = preferences[pairs[index].winner]preferences[pairs[index].loser] - preferences[pairs[index].loser]preferences[pairs[index].winner];
			other_strength = preferences[pairs[j].winner]preferences[pairs[j].loser] - preferences[pairs[j].loser]preferences[pairs[j].winner]
			if(other_strength > current_strength ){
				index = j;
			}
		}
		temp = pairs[i];
		pairs[i] = pairs[index];
		pairs[index] = temp;
	}
}

void lock_pairs(){
	
}
//lock_pairs .
//A função deve criar o gráfico locked , adicionando todas as arestas em ordem decrescente de força de vitória, desde que a aresta não crie um ciclo.
//print_winner .
//A função deve imprimir o nome do candidato que é a fonte do gráfico. Você pode presumir que não haverá mais de uma fonte.

int main(){
	int pair_count = 0;
	int qtdyvoters;
	int qtdycandidates = 0;
	char voteName[30];
	char candidates[200];
	printf("Writte the candidates's names split by spaces ");
	fgets(candidates, sizeof(candidates), stdin);
	addCandidate(candidates, &qtdycandidates, candidatesArray);
	printf("How many voters ");
	scanf("%d", &qtdyvoters);
	fflush(stdin);
    int ranks[qtdyvoters][MAX_CANDIDATES];
	int preferences[MAX_CANDIDATES][MAX_CANDIDATES];
    for (int i = 0; i < qtdyvoters; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Rank %d ", j+1);
            fgets(voteName, sizeof(voteName), stdin);
            strtok(voteName, "\n");
			vote(i, j, voteName, qtdycandidates, qtdyvoters, ranks, candidatesArray);
        }
        printf("\n");
    }
    record_preferences(ranks,qtdycandidates,qtdyvoters,preferences);
    add_pair(preferences, &pair_count, qtdycandidates, pairs);
   for (int i = 0; i < 6; i++) {
        printf("Pair %d: winner = %d, loser = %d\n", i + 1, pairs[i].winner, pairs[i].loser);
    }
return 0;
}