#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player Player;
typedef struct Team Team;
typedef struct PlayerNode PlayerNode;

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

void insertPlayer(Team **team, char firstName[], char secondName[], int points);
void printList(Team *head);
void findLowestTeamPoints(Team **head);
