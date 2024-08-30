#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


bool noRepeatChar(string text);
string cipher(string text, string code);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isalpha(argv[1][i]) || len != 26 || noRepeatChar(argv[1]) != true)
        {
            printf("Only alphabetic characters and must contain 26 characters\n");
            return 1;
        }
    }

    string userText = get_string("plaintext:  ");
    string result = cipher(userText, argv[1]);
    printf("ciphertext: %s\n", result);

}


bool noRepeatChar(string text)
{
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        for (int k = i + 1; k < len; k++)
        {
            if (text[i] == text[k])
            {
                return false;
            }
        }
    }

    return true;
}

string cipher(string text, string code)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            int index = text[i] - 'a';
            text[i] = tolower(code[index]);
        }

        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            int index = text[i] - 'A';
            text[i] = toupper(code[index]);
        }
    }

    return text;
}
