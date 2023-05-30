#include "library.h"

int main(int argc, char *argv[])
{

    FILE *g = fopen(argv[1], "rt");
    if (g == NULL)
    {
        printf("Fisierul nu a putut fi deschis");
        exit(1);
    }
    int c[5];
    fscanf(g, "%d%d%d%d%d", &c[0], &c[1], &c[2], &c[3], &c[4]);
    // printf("%d %d %d %d %d\n", c[0], c[1], c[2], c[3], c[4]);

    FILE *f = fopen(argv[2], "rt");
    if (f == NULL)
    {
        printf("Fisierul nu a putut fi deschis");
        exit(1);
    }
    FILE *out = fopen(argv[3], "wt");
    if (f == NULL)
    {
        printf("Fisierul nu a putut fi deschis");
        exit(1);
    }

    Team *head = NULL;
    int numberOfTeams;
    fscanf(f, "%d", &numberOfTeams);
    if (c[0] == 1)
    {
        for (int i = 0; i < numberOfTeams; i++)
        {
            int numberOfPlayers;
            char teamName[100];
            fscanf(f, "%d %[^\n]", &numberOfPlayers, teamName);
            float teamPoints = 0;
            Team *newTeam = malloc(sizeof(Team));
            newTeam->numberOfPlayers = numberOfPlayers;
            newTeam->points = teamPoints;
            newTeam->teamName = strdup(teamName);
            newTeam->teamName[strcspn(newTeam->teamName, "\r\n")] = '\0';
            if (newTeam->teamName[strlen(newTeam->teamName) - 1] == ' ')
                newTeam->teamName[strlen(newTeam->teamName) - 1] = '\0';
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
    }

    int wantedNumber = PowerOf2(numberOfTeams);
    int copyNumberOfTeams = numberOfTeams;
    if (c[1] == 1)
    {
        while (copyNumberOfTeams > wantedNumber)
        {
            findLowestTeamPoints(&head);
            copyNumberOfTeams--;
        }
    }

    printList(head, out);

    Team *lastEightTeams;
    if (c[2] == 1)
    {
        lastEightTeams = Matches(head, wantedNumber, out);
    }
    if (c[3] == 1)
    {
        BST *bst = NULL;
        Team *copyLastEightMatches = lastEightTeams;

        while (copyLastEightMatches != NULL)
        {

            bst = insertBSTNode(bst, copyLastEightMatches);
            copyLastEightMatches = copyLastEightMatches->next;
        }
        fprintf(out, "\nTOP 8 TEAMS:\n");
        Display(bst, out);
    }
    fclose(g);
    fclose(f);
    fclose(out);
    return 0;
}
