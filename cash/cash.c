#include <cs50.h>
#include <stdio.h>

int calculateQuarters(int userChange);
int calculateDimes(int userChange);
int calculateNickels(int userChange);
int calculatePennies(int userChange);

int main(void)
{
    int userChange;

    do
    {
        userChange = get_int("Change owed: ");
    }while ( userChange <= 0 );

    int quarters = calculateQuarters(userChange);
    userChange = userChange % 25;

    int dimes = calculateDimes(userChange);
    userChange = userChange % 10;

    int nickels = calculateNickels(userChange);
    userChange = userChange % 5;

    int pennies = calculatePennies(userChange);
    userChange = userChange % 1;

    int sum = quarters + dimes + nickels + pennies;

    printf("%i\n", sum);
}

int calculateQuarters(int userChange)
{
    int q = userChange / 25;

    return q;
}

int calculateDimes(int userChange)
{
    int d = userChange / 10;

    return d;
}

int calculateNickels(int userChange)
{
    int n = userChange / 5;

    return n;
}

int calculatePennies(int userChange)
{
    int p = userChange / 1;

    return p;
}
