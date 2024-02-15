#include <stdio.h>

int main()
{
    int startSize, endSize;
    int died = 0;
	int born = 0;
    int years = 0;
    
    do{
    	printf("Insert the start size (bigger than 9) ");
    	scanf("%d", &startSize);
	}while(startSize < 9);
	do{
    	printf("Insert the end size (bigger than start) ");
    	scanf("%d", &endSize);
	}while(startSize > endSize);
	while (startSize < endSize) {
		born = startSize/3;
		died = startSize/4;
        startSize += born - died;
        years++;
    }
	printf("It will take %d year(s)", years);
    return 0;
}
