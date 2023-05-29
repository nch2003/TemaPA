#include "task_1.h"

void insertPlayer(Team **team, char firstName[], char secondName[], int points)
{
    PlayerNode *newPlayerNode = malloc(sizeof(PlayerNode));
    newPlayerNode->player.firstName = strdup(firstName);
    newPlayerNode->player.secondName = strdup(secondName);
    newPlayerNode->player.points = points;
    newPlayerNode->next = (*team)->players;
    (*team)->players = newPlayerNode;
}

void printList(Team *head)
{
    FILE *f = fopen("r.out", "w");
    if (f == NULL)
    {
        printf("Fisierul nu a putut fi deschis");
        return;
    }
    Team *team = head;
    while (team != NULL)
    {
        fputs(team->teamName, f);
        fputs("\n", f);
        team = team->next;
    }
    fclose(f);
}
void findLowestTeamPoints(Team **head)
{
    Team *lowestTeam = *head;
    lowestTeam->points = (*head)->points;
    Team *current = *head;
    while(current != NULL)
    {
        if(current->points < lowestTeam->points)
        {
            lowestTeam = current;
            lowestTeam->points = current->points;
        }
        current = current->next;
    }
    if(*head == lowestTeam)
        *head = lowestTeam->next;
    else
    {
        Team *prev = *head;
        while(prev->next != lowestTeam)
            prev = prev->next;

        prev->next = lowestTeam->next;
    }
    free(lowestTeam);
}
/*
int PowerOf2(int n)
{
    int number = 0;
    for(int i = n; i >= 1; i--)
    {
        if()
    }*/
