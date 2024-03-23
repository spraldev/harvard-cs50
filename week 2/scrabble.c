#include <cs50.h>
#include <stdio.h>
#include <string.h>

int points(const char *str);

int main(void)
{
    const char *player1 = get_string("Player 1: \n");
    const char *player2 = get_string("Player 2: \n");

    if (points(player1) > points(player2))
    {
        printf("Player 1 wins! (%i)\n", points(player1));
    }
    else if (points(player1) < points(player2))
    {
        printf("Player 2 wins! (%i)\n", points(player2));
    }
    else
    {
        printf("Tie!\n");
    }
}

int points(const char *str)
{
    int score = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        switch (str[i])
        {
            case 'a':
            case 'A':
                score++;
                break;

            case 'b':
            case 'B':
                score += 3;
                break;

            case 'c':
            case 'C':
                score += 3;
                break;

            case 'd':
            case 'D':
                score += 2;
                break;

            case 'e':
            case 'E':
                score++;
                break;

            case 'f':
            case 'F':
                score += 4;
                break;

            case 'g':
            case 'G':
                score += 2;
                break;

            case 'h':
            case 'H':
                score += 4;
                break;

            case 'i':
            case 'I':
                score++;
                break;

            case 'j':
            case 'J':
                score += 8;
                break;

            case 'k':
            case 'K':
                score += 5;
                break;

            case 'l':
            case 'L':
                score++;
                break;

            case 'm':
            case 'M':
                score += 3;
                break;

            case 'n':
            case 'N':
                score++;
                break;

            case 'o':
            case 'O':
                score++;
                break;

            case 'p':
            case 'P':
                score += 3;
                break;

            case 'q':
            case 'Q':
                score += 10;
                break;

            case 'r':
            case 'R':
                score++;
                break;

            case 's':
            case 'S':
                score++;
                break;

            case 't':
            case 'T':
                score++;
                break;

            case 'u':
            case 'U':
                score++;
                break;

            case 'v':
            case 'V':
                score += 4;
                break;

            case 'w':
            case 'W':
                score += 4;
                break;

            case 'x':
            case 'X':
                score += 8;
                break;

            case 'y':
            case 'Y':
                score += 4;
                break;

            case 'z':
            case 'Z':
                score += 10;
                break;

            default:
                score += 0;
        }
    }

    return score;
}
