#include <stdio.h>

int main(){
    int number;
    printf("Insert a number ");
    scanf("%d", &number);
    for(int i = number; i > 0; i--){
        for (int k = number; k > number - i; k--) {
            printf(" ");
        }
        for(int j = i - 1; j < number; j++){
            printf("#");
        }
        
        printf("\n");
    }
}