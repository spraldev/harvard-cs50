#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int letters[26] = {0};

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must contain only letters.\n");
            return 1;
        }

        int index = toupper(argv[1][i]) - 'A';

        if (letters[index])
        {
            printf("Key must not contain duplicate letters.\n");
            return 1;
        }

        letters[index] = 1;
    }

    const char *plaintext = get_string("plaintext: ");
    char ciphertext[strlen(plaintext) + 1];

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int num = isupper(plaintext[i]) ? plaintext[i] - 'A' : plaintext[i] - 'a';
            ciphertext[i] = isupper(plaintext[i]) ? toupper(argv[1][num]) : tolower(argv[1][num]);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[strlen(plaintext)] = '\0';

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}
