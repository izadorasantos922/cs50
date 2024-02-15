#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
	int key;
	char plaintext[300];
	printf("Writte a key ");
	scanf("%d", &key);
	fflush(stdin);
	printf("Writte a text ");
	fgets(plaintext, sizeof(plaintext), stdin);
	printf("Plaintext: %s", plaintext);
	printf("Ciphertext: ");
	for(int i =0; i < strlen(plaintext); i++){
		if(islower(plaintext[i])){
			printf("%c", (((plaintext[i] - 65)+key)%26) + 65);
		}else if(isupper(plaintext[i])){
			printf("%c", (((plaintext[i] - 65)+key)%26) + 65);
		}else {
			printf("%c", plaintext[i]);
		}
	}
	return 0;
}
