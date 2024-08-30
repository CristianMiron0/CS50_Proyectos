#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

string cipher(string text, int number);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        else
        {
            continue;
        }
    }

    string input = get_string("plaintext:  ");
    int key = atoi(argv[1]);
    cipher(input, key);
    printf("ciphertext: %s\n", input);
}

string cipher(char text[], int number)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (islower(text[i]))
        {
            text[i] = 'a' + (text[i] - 'a' + number) % 26;
        }

        else if (isupper(text[i]))
        {
            text[i] = 'A' + (text[i] - 'A' + number) % 26;
        }
    }

    return text;
}
