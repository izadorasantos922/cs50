#include <stdio.h>
#include <string.h>
#include <math.h>

int countWords(char *str){
	int count = 1;
	int length = strlen(str);
	for (int i = 0; i < length; i++) {
        if (str[i] == ' ') {
            count++;
        }
    }
			
	return count;
}
int countLetters(char *str){
	int count = 0;
	int length = strlen(str);
	for (int i = 0; i < length; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z')|| (str[i] >= 'A' && str[i] <= 'Z')) {
            count++;
        }
    }
			
	return count;
}

int countSentences(char *str){
	int count = 0;
	int length = strlen(str);
	for (int i = 0; i < length; i++) {
        if (str[i] == '!'|| str[i] == '.'||str[i] == '?') {
            count++;
        }
    }
			
	return count;
}

int main(){
	char text[200];
	int opcao;
	do{
		printf("Writte a number 1 (calculate a indice) or 2 (exit) ");
		scanf("%d", &opcao);
		fflush(stdin);
		switch(opcao){
			case 1: 
				printf("Writte a text ");
				fgets(text, sizeof(text), stdin);
				int length = countLetters(text);
				float indice = (0.0588 * length / countWords(text) * 100) - (0.296 * countSentences(text)/ countWords(text) * 100) - 15.8;
				int finalIndice = (int)round(indice);
				if(finalIndice < 1){
					printf("The grade -1\n");
				}else if(finalIndice > 16){
					printf("The grade +16\n");
				}else{
					printf("The grade %d\n", finalIndice);
				}
			break;
		}
	}while(opcao == 1);
	return 0;
}