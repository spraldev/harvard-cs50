#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./plurality choice1 choice2 choice3 etc...\n");
        return 1;
    }

    const char *c = get_string("Number of Voters: ");
    int voters;

    if (isdigit(*c))
    {
        voters = atoi(c);
    }
    else
    {
        printf("That is not a number.\n");
        return 1;
    }

    if (voters < 1)
    {
        printf("There must be voters.\n");
        return 1;
    }

    int votes[argc - 1];
    memset(votes, 0, sizeof(votes));

    for (int i = 0; i < voters; i++)
    {
        const char *vote = get_string("Vote: ");
        int found = 0;

        for (int y = 1; y < argc; y++)
        {
            if (strcmp(vote, argv[y]) == 0)
            {
                found = 1;
                votes[y - 1]++;
                break;
            }
        }

        if (!found)
        {
            printf("That is not a choice.\n");
            return 1;
        }
    }

    int largest = votes[0];
    int winnerIndex = 0;

    for (int i = 1; i < argc - 1; i++)
    {
        if (votes[i] > largest)
        {
            largest = votes[i];
            winnerIndex = i;
        }
    }

    printf("%s\n", argv[winnerIndex + 1]);

    return 0;
}
