#include <stdio.h>

int main()
{
    int position = 0;
    int mutiplyByTwo = 0;
    int sumEven = 0;
    int sumOdd = 0;
    int sumTotal = 0;
    long long int creditCard;
    printf("Insert a number of credit card ");
    scanf("%lld", &creditCard);
    long long int temp = creditCard;
    while(temp > 0){
       int digit = temp % 10;
        if(position % 2 == 1){
            mutiplyByTwo = digit * 2;
            if(mutiplyByTwo > 9){
            	while(mutiplyByTwo > 0){
            		sumOdd += mutiplyByTwo % 10;
            		mutiplyByTwo /= 10;
				}
			}
            sumOdd += mutiplyByTwo;
        }else{
        	sumEven += digit;
		}
        temp/= 10;
        position++;
    }
     long long int otherVarible = creditCard;
    while(otherVarible > 100){
    	otherVarible/= 10;
	}
	int firstDigitOfCreditCard = otherVarible;
    sumTotal = sumOdd + sumEven;
    int lastDigitOfSumTotal = sumTotal % 10;
    int lastDigitOfCreditCard = creditCard % 10;
    
    if(lastDigitOfSumTotal == 0 && lastDigitOfCreditCard == 4 && (position == 13 || position == 16)){
    	printf("It's a Visa credit card\n");
	}else if(lastDigitOfSumTotal == 0 && (firstDigitOfCreditCard >= 51 && firstDigitOfCreditCard <= 55) &&  position == 16){
    	printf("It's a Mastercard credit card\n");
	}else if(lastDigitOfSumTotal == 0 && (firstDigitOfCreditCard == 34 || firstDigitOfCreditCard == 37) && (position == 13 || position == 16)){
    	printf("It's a American express credit card\n");
	}else{
		printf("Invalid!\n");
	}
    return 0;
}
