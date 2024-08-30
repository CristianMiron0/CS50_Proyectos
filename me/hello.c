#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string userAnswer = get_string("What's your name? ");
    printf("hello, %s\n", userAnswer);
}
