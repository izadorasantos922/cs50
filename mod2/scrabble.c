#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char word[]){
    int point = 0;
    for(int i = 0; i < strlen(word); i++){
        if ((word[i] == 'a') || (word[i] == 'A')){
            point += POINTS[0];
        } else if ((word[i] == 'b') || (word[i] == 'B')){
            point += POINTS[1];
        } else if ((word[i] == 'c') || (word[i] == 'C')){
            point += POINTS[2];
        } else if ((word[i] == 'd') || (word[i] == 'D')){
            point += POINTS[3];
        } else if ((word[i] == 'e') || (word[i] == 'E')){
            point += POINTS[4];
        } else if ((word[i] == 'f') || (word[i] == 'F')){
            point += POINTS[5];
        } else if ((word[i] == 'g') || (word[i] == 'G')){
            point += POINTS[6];
        } else if ((word[i] == 'h') || (word[i] == 'H')){
            point += POINTS[7];
        } else if ((word[i] == 'i') || (word[i] == 'I')){
            point += POINTS[8];
        } else if ((word[i] == 'j') || (word[i] == 'J')){
            point += POINTS[9];
        } else if ((word[i] == 'k') || (word[i] == 'K')){
            point += POINTS[10];
        } else if ((word[i] == 'l') || (word[i] == 'L')){
            point += POINTS[11];
        } else if ((word[i] == 'm') || (word[i] == 'M')){
            point += POINTS[12];
        } else if ((word[i] == 'n') || (word[i] == 'N')){
            point += POINTS[13];
        } else if ((word[i] == 'o') || (word[i] == 'O')){
            point += POINTS[14];
        } else if ((word[i] == 'p') || (word[i] == 'P')){
            point += POINTS[15];
        } else if ((word[i] == 'q') || (word[i] == 'Q')){
            point += POINTS[16];
        } else if ((word[i] == 'r') || (word[i] == 'R')){
            point += POINTS[17];
        } else if ((word[i] == 's') || (word[i] == 'S')){
            point += POINTS[18];
        } else if ((word[i] == 't') || (word[i] == 'T')){
            point += POINTS[19];
        } else if ((word[i] == 'u') || (word[i] == 'U')){
            point += POINTS[20];
        } else if ((word[i] == 'v') || (word[i] == 'V')){
            point += POINTS[21];
        } else if ((word[i] == 'w') || (word[i] == 'W')){
            point += POINTS[22];
        } else if ((word[i] == 'x') || (word[i] == 'X')){
            point += POINTS[23];
        } else if ((word[i] == 'y') || (word[i] == 'Y')){
            point += POINTS[24];
        } else if ((word[i] == 'z') || (word[i] == 'Z')){
            point += POINTS[25];
        }
    }
    return point;
}

int main(void)
{
    char playerOne[50];
    char playerTwo[50];
    printf("Player 1: ");
    fgets(playerOne, sizeof(playerOne), stdin);
    printf("Player 2: ");
    fgets(playerTwo, sizeof(playerTwo), stdin);
    int score1 = compute_score(playerOne);
    int score2 = compute_score(playerTwo);
    if(score1 > score2){
        printf("Player 1 win!\n");
    } else if(score1 < score2){
        printf("Player 2 win!\n");
    } else {
        printf("Tie!\n");
    }
    return 0;
}
