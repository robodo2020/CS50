#include <cs50.h>
#include <stdio.h>
#include <string.h>
//嘗試把上課觀念加進去，不要用以前的想法
// Max number of candidates
#define MAX 9
bool back = false;
// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        // Check for invalid vote
        if (!vote(name))  //當vote(name)返回值不為true 就會invalid
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    //在candidate內找name
    //If有找到 candidates[i].votes +1; return true
    for (int i = 0; i < candidate_count ; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }

    }
    //若沒找到
    return false;

    //return放的位置為啥是這樣 一開始一直導致錯誤
    //
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO找到票數最多的，print it’s name
    //若同時最高票有兩人，兩人都要print
    int winnervote = 0;

    for (int i = 0; i < candidate_count ; i++)
    {
        if (candidates[i].votes > winnervote)
        {
            winnervote = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count ; i++)
    {
        if (winnervote == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

