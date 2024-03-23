#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define MAX 9
string candidates[MAX];
int candidate_count = 0;

int preferences[MAX][MAX];

bool locked[MAX][MAX];
int locked_count = 0;

typedef struct
{
    int winner;
    int loser;
}
pair;

pair pairs[MAX];
int pair_count = 0;

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool creates_cycle(int winner, int loser);
void print_winner(void);

int main (int argc, char *argv[]) {
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;

    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++) {
        int ranks[candidate_count];

        string rank1 = get_string("Rank 1: ");

        bool vote1 = vote(0, rank1, ranks);

        if(!vote1) {
            printf("Not a valid choice\n");
            return 1;
        }


        string rank2 = get_string("Rank 2: ");

        bool vote2 = vote(1, rank2, ranks);

        if(!vote2) {
            printf("Not a valid choice\n");
            return 1;
        }

        string rank3 = get_string("Rank 3: ");

        bool vote3 = vote(2, rank3, ranks);

        if(!vote3) {
            printf("Not a valid choice\n");
            return 1;
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

}

bool vote(int rank, string name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

void record_preferences(int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
                preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if(preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;

            } else if (preferences[j][i] > preferences[i][j]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void) {

    pair t;

     for (int i = 0; i < pair_count; i++) {
        for (int j = i + 1; j < pair_count; j++) {
            if(preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser]) {
                t = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = t;
            }
        }
     }
}

bool creates_cycle(int winner, int loser) {
    if(winner == loser) {
        return true;
    }

    for (int i = 0; i < candidate_count; i++) {
        if(locked[i][winner]) {
            if(creates_cycle(i, loser)) {
                return true;
            }
        }
    }

    return false;
}

void lock_pairs(void) {
    for (int i = 0; i < pair_count; i++) {
        if(!creates_cycle(pairs[i].winner, pairs[i].loser)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
            locked_count++;
        }
    }
}

void print_winner(void) {
    for (int i = 0; i < pair_count; i++) {
        bool won = true;
        for (int j = 0; j < pair_count; j++) {

            if(locked[j][i]) {
                won = false;
                break;
            }
        }

        if(won) {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
