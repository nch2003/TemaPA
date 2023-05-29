#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player Player;
typedef struct Team Team;
typedef struct PlayerNode PlayerNode;
typedef struct MatchNode MatchNode;
typedef struct MatchQueue MatchQueue;
typedef struct Stack Stack;

struct MatchNode
{
    Team *Team_1;
    Team *Team_2;
    MatchNode *next;
};

struct MatchQueue
{
    MatchNode *front, *rear;
};

struct Player
{
    char *firstName;
    char *secondName;
    int points;
};

struct PlayerNode
{
    Player player;
    PlayerNode *next;
};

struct Team
{
    PlayerNode *players;
    int numberOfPlayers;
    float points;
    char *teamName;
    Team *next;
};

struct Stack
{
    Team *team;
    Stack *next;
};

void insertPlayer(Team **team, char firstName[], char secondName[], int points);
void findLowestTeamPoints(Team **head);
int PowerOf2(int n);
void push(Stack **stack, Team *team);
Team *pop(Stack **stack);
void enqueue(MatchQueue *queue, Team *Team_1, Team *Team_2);
MatchNode *dequeue(MatchQueue *queue);
void proccesMatch(Team *Team_1, Team *Team_2, Stack **winnerStack, Stack **losersSack);
Team *Matches(Team *head, int numberOfTeams);
void printList(Team *head);
