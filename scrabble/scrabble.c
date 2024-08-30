#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1 ,1 ,1 ,1 ,4 ,4 ,8 ,4 ,10};

int getScore(string word);

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int score1 = getScore(player1);
    int score2 = getScore(player2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }
}

int getScore(string word)
{
    int total = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (islower(word[i]))
        {
            total += points[word[i] - 'a'];
        }

        else if (isupper(word[i]))
        {
            total += points[word[i] - 'A'];
        }
    }

    return total;
}
