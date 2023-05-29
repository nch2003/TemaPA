#include "task_1.h"

int main(int argc, char *argv[])
{
    FILE *f = fopen("d.in", "r");
    if (f == NULL)
    {
        printf("Fisierul nu a putut fi deschis");
        exit(1);
    }
    Team *head = NULL;
    PlayerNode *Player = NULL;
    int numberOfTeams;
    fscanf(f, "%d", &numberOfTeams);
    for (int i = 0; i < numberOfTeams; i++)
    {
        int numberOfPlayers;
        char teamName[100];
        fscanf(f, "%d%[^\n]", &numberOfPlayers, teamName);
        float teamPoints = 0;
        Team *newTeam = malloc(sizeof(Team));
        newTeam->numberOfPlayers = numberOfPlayers;
        newTeam->points = teamPoints;
        newTeam->teamName = strdup(teamName);
        newTeam->next = head;
        head = newTeam;
        for (int j = 0; j < numberOfPlayers; j++)
        {
            char firstName[100], secondName[100];
            int points;
            fscanf(f, "%s%s%d", firstName, secondName, &points);
            teamPoints += points;
            insertPlayer(&head, firstName, secondName, points);
        }
        newTeam->points = teamPoints / numberOfPlayers;

    }

    int wantedNumber = PowerOf2(numberOfTeams);
    int copyNumberOfTeams = numberOfTeams;
    while(copyNumberOfTeams > wantedNumber)
    {
        findLowestTeamPoints(&head);
        copyNumberOfTeams--;
    }
    Team *lastEightTeams = Matches(head, wantedNumber);


}
