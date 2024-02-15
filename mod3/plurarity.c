#include <stdio.h>
#include <string.h>

struct candidate{
	char name[20];
	int vote;
};

void addCandidates(char *candidates, int *count, struct candidate candidateArray[]){
	char *limiter = " \n";
	char *token;
	token = strtok(candidates, limiter);
	int i = 0;
	while(token != NULL && i < 9){
		strcpy(candidateArray[i].name, token);
		candidateArray[i].vote = 0;
		i++;
		(*count)++;
		token = strtok(NULL, limiter);
	}
}

void vote(int count, struct candidate candidateArray[]){
	int numberOfvoters;
	printf("Numbers of voters ");
	scanf("%d", &numberOfvoters);
	for(int i = 0; i < numberOfvoters; i++){
		printf("Vote %d: ", i+1);
		char voterChoice[20];
		scanf("%s", &voterChoice);
		
		for(int j = 0; j < count; j++){
			if(strcmp(voterChoice,candidateArray[j].name) == 0){
			candidateArray[j].vote++;
			break;
		}
	}
	}
}

int main(){
	int count = 0;
	int major = 0;
	char win[30];
	char candidates[50];
	struct candidate candidateArray[9];
	printf("Writte the candidates names ");
	fgets(candidates, sizeof(candidates), stdin);
	addCandidates(candidates, &count, candidateArray);
	vote(count, candidateArray);
	for(int i = 0; i < count; i++){
		if(candidateArray[i].vote > major){
			major = candidateArray[i].vote;
			strcpy(win, candidateArray[i].name);
		}
	}
	for(int i = 0; i < count; i++){
		if(candidateArray[i].vote == major){
			printf("\n The elected is %s, with %d votes \n", candidateArray[i].name, candidateArray[i].vote);
		}
	}
	
for(int i = 0; i < count; i++){
	printf("\n\n The candidate is %s, with %d votes \n", candidateArray[i].name, candidateArray[i].vote);
}	
} 
