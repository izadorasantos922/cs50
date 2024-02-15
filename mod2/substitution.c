#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
	char key[30];
	char plaintext[300];
	int lengthKey;
	int count = 0;
	int repeated = 0;
	do{
		printf("Writte a key (no spaces and no repeated) ");
		fgets(key, sizeof(key), stdin);
		lengthKey = strlen(key);
		for(int i = 0; i < lengthKey; i++){
			if(key[i] == ' '){
				count++;
			}
		}
		for(int i = 0; i < lengthKey; i++){
			for(int j = i + 1; i < lengthKey; j++){
			if(key[i] == key[j]){
				repeated = 1;
				break;
			}
		}
		}
		
	}while(lengthKey != 26 || count >0 || repeated > 0);
	printf("Writte a text ");
	fgets(plaintext, sizeof(plaintext), stdin);
	printf("Plaintext: %s", plaintext);
	printf("Ciphertext: ");
	for(int i =0; i < strlen(plaintext); i++){
			if(islower(plaintext[i])){
			printf("%c", key[plaintext[i]- 'a']);
		}else if(isupper(plaintext[i])){
			printf("%c",toupper(key[plaintext[i]-'a']));
		}else {
			printf("%c", plaintext[i]);
		}
	}
	return 0;
}
