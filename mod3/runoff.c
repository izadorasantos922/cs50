#include <stdio.h>
#include <string.h>
#define MAX_CANDIDATES 9
#define rankNumber 3
typedef struct{
	char name[30];
	int vote;
	int eliminated;
}candidates;

candidates candidateArray[MAX_CANDIDATES];
void addCandidate(int *qtdyCandidates, candidates candidateArray[], char *candidates){
	char *limiter = " \n";
	char *token = strtok(candidates, limiter);
	int i = 0;
	while(token != NULL && i < MAX_CANDIDATES){
		strcpy(candidateArray[i].name, token);
		candidateArray[i].vote = 0;
		candidateArray[i].eliminated = false;
		(*qtdyCandidates)++;
		i++;
		token = strtok(NULL, limiter);
	}
}
int find_min(int qtdyvoters, candidates candidateArray[], int qtdyCandidates) {
    int min = qtdyvoters;
    for (int j = 0; j < qtdyCandidates; j++) {
        if (candidateArray[j].vote < min) {
            min = candidateArray[j].vote;
        }
    }   
    return min;
}

void eliminated(int min, candidates candidateArray[], int qtdyCandidates){
	for(int j = 0; j < qtdyCandidates; j++){
		if(candidateArray[j].vote == min){
			candidateArray[j].eliminated = 1;
		}
	}	
}
void print_winner(candidates candidateArray[], int qtdyCandidates, int qtdyvoters){
	for(int j = 0; j < qtdyCandidates; j++){
		if(candidateArray[j].vote > qtdyvoters/2 && candidateArray[j].eliminated == 0){
			printf(" %s", candidateArray[j].name);
			break;
		}
	}	
}
void tabulate(int preferences[][rankNumber], int qtdyvoters, int qtdyCandidates, candidates candidateArray[]){
	for(int i = 0; i < qtdyvoters; i++){
		for(int j = 0; j < qtdyCandidates; j++){
		int candidateIndex = preferences[i][j];
            if (!candidateArray[candidateIndex].eliminated) {
                candidateArray[candidateIndex].vote++;
                break;
            }
	}	
	}
}
int vote(int voter, int rank, char name[], candidates candidateArray[], int qtdyCandidates, int preferences[][rankNumber]){
	for(int i = 0; i < qtdyCandidates; i++){
		if(strcmp(candidateArray[i].name, name) == 0){
			preferences[voter][rank] = i;
			return 1;
		}	
	}
	return 0;
}

int is_tie(candidates candidateArray[], int qtdyCandidates){
	int count = 0;
	int major = 0;
		for(int i = 0; i < qtdyCandidates; i++){
		if(candidateArray[i].vote > major){
			major += candidateArray[i].vote;
		}
	}
	for(int i = 0; i < qtdyCandidates; i++){
		if(candidateArray[i].vote == major){
			count++;
		}
	}
	
	if(count > 1){
		for(int i = 0; i < qtdyCandidates; i++){
			if(candidateArray[i].vote == major){
			printf("%s ", candidateArray[i].name);
			}
		}
		return 1;
	}else{
		return 0;
	}
}
int main(){
	char candidates[260];
	int qtdyvoters;
	char voteName[30];
	int qtdyCandidates = 0;
	printf("Writte the first name of the candidates (split by spaces): ");
	fgets(candidates, sizeof(candidates), stdin);
	addCandidate(&qtdyCandidates, candidateArray, candidates);
	printf("How many voters ");
	scanf("%d", &qtdyvoters);
	int preferences[qtdyvoters][rankNumber];
	for(int i = 0; i < qtdyvoters; i++){
		for(int j = 0; j < 3; j++){
			printf("Rank %d: ", j+1);
			scanf("%s", voteName);
		  vote(i, j, voteName, candidateArray, qtdyCandidates, preferences);
		}
		printf("\n");
	}
	
	tabulate(preferences, qtdyvoters,qtdyCandidates, candidateArray);
	int min = find_min(qtdyvoters, candidateArray, qtdyCandidates);
	eliminated(min, candidateArray, qtdyCandidates);
	tabulate(preferences, qtdyvoters,qtdyCandidates, candidateArray);
	if(is_tie(candidateArray, qtdyCandidates) == 1){
		
	}else{
		print_winner(candidateArray, qtdyCandidates, qtdyvoters);
	}
	return 0;
}
