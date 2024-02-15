#include <stdio.h>
#include <math.h>

int main() {
    double cents;
    int nickel = 5;
    int dime = 10;
    int penny = 1;
    int quarter = 25;
    int count = 0;
    int number = 0;

    printf("Insert the cents: ");
    scanf("%lf", &cents);

    number = round(cents * 100);

    while (number > 0) {
        if (number >= quarter) {
            number -= quarter;
            count++;
        } else if (number >= dime) {
            number -= dime;
            count++;
        }else if (number >= nickel) {
            number -= nickel;
            count++;
        } else if (number >= penny) {
            number -= penny;
            count++;
        }
    }

    printf("Number of coins needed: %d\n", count);

    return 0;
}
