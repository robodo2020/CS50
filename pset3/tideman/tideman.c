#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j 多少人認為i打j贏
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair Newpairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;


// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void); 
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates 寫入candidate名稱而已
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO 找name對不對，如果有找到，update ranks並return true ranks[i]是排序，候選人是ABC的話 目前判斷0是A 1是B 2是C
    for (int i = 0; i < candidate_count ; i++)
    {
        //if 找到name符合
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    //若沒找到
    return false;
}

// Update preferences given one voter's ranks 用來更新preference[i][j]
void record_preferences(int ranks[])
{
    // TODO
    //recursion solution 還沒想到嗚嗚
    int a = 0;
    if (a == candidate_count)
    {
        return;
    }
    record_preferences(i - 1);
    
    for (int i = 0; i < candidate_count ; i++)
    {
        preferences[ranks[a]][ranks[i]] += 1;
        a ++;
    }
    //preference[][] += 1;
    


    //iteration solution
    //for (int j = 0; j < candidate_count ; j++)
    //{
    //    for (int k = j + 1; k < candidate_count ; k++)
    //    {
    //        preferences[ranks[j]][ranks[k]] += 1;
    //    }
    //}

}

// Record pairs of candidates where one is preferred over the other  計算有幾組pairs嗎?
void add_pairs(void)
{
    // TODO


    for (int j = 0; j < candidate_count ; j++)
    {
        for (int k = j + 1; k < candidate_count ; k++)
        {
            if (preferences[j][k] > preferences[k][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = k;
                pair_count++;

            }
            else if (preferences[j][k] < preferences[k][j])
            {
                pairs[pair_count].winner = k;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
//排序pairs[]讓其從贏最多的排序到贏最少的
void sort_pairs(void)
{
    // TODO
    //sort pair[]
    //preferences
    int BfSwap[pair_count]; //紀錄每個pair的輸贏
    for (int i = 0; i < pair_count; i ++)
    {
        //算出每個pair內輸贏的差距
        BfSwap[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }
    //用bubble sort試試
    int SwapCounter = 1;
    while (SwapCounter != 0)
    {
        //Swap 由大排到小
        for (int i = pair_count; i > 0; i --)
        {
            SwapCounter = 0;
            for (int j = 0; j < i - 1; j ++)
            {
                if (BfSwap[j] < BfSwap[j + 1]) 
                {
                    pair temp = pairs[j];
                    pairs[j] = pairs[j + 1];
                    pairs[j + 1] = temp;
                    SwapCounter ++;

                    int temp1 =  BfSwap[j];
                    BfSwap[j] = BfSwap[j + 1];
                    BfSwap[j + 1] = temp1;    //不懂 為啥測資需要這三行才會過關?
                }
            }
        }
    }
    return;
}




bool thereiscycle(int front, int end, int start)
{
    //base case
    if (end == start)
    {
        return true;
    }
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i] == true)
        {
            if (thereiscycle(end, i, start) == true)
            {
                return true;
            }
        }
    }
    return false;

}


// Lock pairs into the candidate graph in order, without creating cycles
// 用二維矩陣之true false 來代表cycle graph
void lock_pairs(void)
{
    // TODO locked[i][j]
    for (int i = 0; i < pair_count; i ++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true; //建立 pointed graph
        if (thereiscycle(pairs[i].winner, pairs[i].loser, pairs[i].winner))//如果建下去後發現有cycle
        {
            locked[pairs[i].winner][pairs[i].loser] = false; //就不建
        }
        //printf("%i",pair_count);
        //printf("winner:%i, loser:%i\n", pairs[i].winner, pairs[i].loser);

    }
    //有cycle
    return;
}

// Print the winner of the election
// source 沒有人指向他 也是最後winner
//如何判斷是否cycle，拿掉最weak的 locked[j][i] 從weakest拿掉，直到有人完全沒有true的方式看看
void print_winner(void)
{
    // TODO
    //沒有cycle的狀況
    // TODO
    int checkwinner[candidate_count];
    for (int i = 0; i < candidate_count; i ++)
    {
        checkwinner[i] = 0;
    }

    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            if (locked[j][i] == false)
            {
                checkwinner[i]++;
            }
                
        }
        if (checkwinner[i] == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}