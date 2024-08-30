#include <cs50.h>
#include <stdio.h>

bool formulaLuhn (int userCard);

int main(void)
{
    long userCard = get_long("Card Number: ");
    long checkCard = userCard;
    long valid = 0;
    int i = 0;

    bool result = formulaLuhn(userCard);

    while (checkCard > 0)
    {
        checkCard = checkCard / 10;
        i++;
    }

    if ((i != 13) && (i != 15) && (i != 16))
    {
        printf("INVALID\n");
        return 0;
    }

    while (userCard > 100)
    {
        userCard = userCard / 10;
        valid = userCard;
    }

    if ((valid / 10 == 5) && (0 < valid % 10 && valid % 10 < 6) && (result != false))
    {
        printf("MASTERCARD\n");
    }

    else if ((valid / 10 == 3) && (valid % 10 == 4 || valid % 10 == 7) && (result != false))
    {
        printf("AMEX\n");
    }

    else if (valid / 10 == 4 && result != false)
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}


bool formulaLuhn (int userCard)
{
    int sum1 = 0;
    int sum2 = 0;
    long x = userCard;
    int total = 0;
    int v1;
    int v2;
    int a1;
    int a2;

    while (x > 0)
    {
        // Remove last digit and add to sum1
        v1 = x % 10;
        x = x / 10;
        sum1 = sum1 + v1;

        //Remove second to last and add to sum2
        v2 = x % 10;
        x = x / 10;

        //Multiply and add the digits
        v2 = v2 * 2;
        a1 = v2 % 10;
        v2 = v2 / 10;
        a2 = v2 % 10;
        sum2 = sum2 + a1 + a2;
    }

    total = sum1 + sum2;

    if (total % 10 == 0)
    {
        return true;
    }

    return false;
}
