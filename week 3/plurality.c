#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
} candidate;

candidate candidates[MAX];
int candidate_count = 0;

bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

void print_winner(void)
{
    candidate winner = candidates[0];

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > winner.votes)
        {
            winner = candidates[i];
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == winner.votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

int main(int argc, char *argv[])
{
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        bool votee = vote(name);

        if (!votee)
        {
            printf("Not a valid choice\n");
            return 1;
        }
    }

    print_winner();
}
