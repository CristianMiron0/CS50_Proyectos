#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int numberLetters(string sentence);
int numberWords(string sentence);
int numberSentences(string sentence);

int main(void)
{
    string text = get_string("Text: ");

    int letters = numberLetters(text);
    int words = numberWords(text);
    int sentences = numberSentences(text);

    float L = ((float) letters / (float) words) * 100;
    float S = ((float) sentences / (float) words) * 100;

    float result = 0.0588 * L - 0.296 * S - 15.8;
    result = round(result);

    if ((int) result <= 1)
    {
        printf("Before Grade 1\n");
    }

    else if ((int) result >= 16)
    {
        printf("clear\n");
    }

    else
    {
        printf("Grade %i\n", (int) result);
    }
}


int numberLetters(string sentence)
{
    int total = 0;

    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        if (isblank(sentence[i]) || ispunct(sentence[i]))
        {
            continue;
        }

        else
        {
            total++;
        }
    }

    return total;
}

int numberWords(string sentence)
{
    int total = 0;

    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        if (isblank(sentence[i]))
        {
            total++;
        }

        else
        {
            continue;
        }
    }

    return total + 1;
}

int numberSentences(string sentence)
{
    int total = 0;

    for (int i = 0, n = strlen(sentence); i < n; i++)
    {
        if (sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?')
        {
            total++;
        }

        else
        {
            continue;
        }
    }

    return total;
}
