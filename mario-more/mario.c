#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int userInput = get_int("Height: ");

    while (userInput < 1 || userInput > 8)
    {
        userInput = get_int("Height: ");
    }

    for (int i = 1; i <= userInput; i++)
    {
        for (int c = 0; c < userInput - i; c++)
        {
            printf(" ");
        }

        for (int z = 0; z < i; z++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
