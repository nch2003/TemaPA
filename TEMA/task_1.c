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
    if(f == NULL)
    {
        printf("Fisierul nu a putut fi deschis");
        return;
    }
    Team *team = head;
    while(team != NULL)
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

int PowerOf2(int n)
{
    int number = 1;
    while(number * 2 < n)
        number = number * 2;

    return number;
}

void push(Stack **stack, Team *team)
{
    Stack *newStackNode = malloc(sizeof(Stack));
    newStackNode->team = team;
    newStackNode->next = *stack;
    *stack = newStackNode;
}

Team *pop(Stack **stack)
{
    if(*stack == NULL)
        return NULL;

    Team *team = (*stack)->team;
    Stack *temp = *stack;
    *stack = (*stack)->next;
    free(temp);

    return team;
}

void enqueue(MatchQueue *queue, Team *Team_1, Team *Team_2)
{
    MatchNode *newMatchNode = malloc(sizeof(MatchNode));
    newMatchNode->Team_1 = Team_1;
    newMatchNode->Team_2 = Team_2;
    newMatchNode->next = NULL;

    if(queue->rear == NULL)
    {
        queue->front = newMatchNode;
        queue->rear = newMatchNode;
    }
    else
    {
        queue->rear->next = newMatchNode;
        queue->rear = newMatchNode;
    }
}

MatchNode *dequeue(MatchQueue *queue)
{
    if(queue->front == NULL)
        return NULL;

    MatchNode *newMatchNode = queue->front;
    queue->front = queue->front->next;

    if(queue->front == NULL)
        queue->rear = NULL;

    return newMatchNode;
}

void proccesMatch(Team *Team_1, Team *Team_2, Stack **winnersStack, Stack **losersStack)
{
    if(Team_1->points >= Team_2->points)
    {
        push(winnersStack, Team_1);
        push(losersStack, Team_2);
        Team_1->points++;
    }
    else if(Team_1->points < Team_2->points)
    {
        push(winnersStack, Team_2);
        push(losersStack, Team_1);
        Team_2->points++;
    }
}

Team *Matches(Team *head, int numberOfTeams)
{
    MatchQueue matchQueue;
    matchQueue.front = NULL;
    matchQueue.rear = NULL;
    Stack *winnersStack = NULL;
    Stack *losersStack = NULL;
    Team *Team_1 = head;
    Team *Team_2 = head->next;
    Team *lastEightTeams = NULL;
    while(numberOfTeams != 1)
    {
        if(winnersStack == NULL)
        {
            while(Team_1 != NULL && Team_2 != NULL)
            {
                enqueue(&matchQueue, Team_1, Team_2);
                Team_1 = Team_2->next;
                if(Team_1 != NULL)
                    Team_2 = Team_1->next;
            }
        }
        else
        {
            while(winnersStack != NULL)
            {
                enqueue(&matchQueue, pop(&winnersStack), pop(&winnersStack));
            }
        }
        while(matchQueue.front != NULL)
        {
            MatchNode *currentMatch = matchQueue.front;
            dequeue(&matchQueue);
            proccesMatch(currentMatch->Team_1, currentMatch->Team_2, &winnersStack, &losersStack);
            free(currentMatch);
        }
        if(numberOfTeams == 16)
        {
            Stack *copy = winnersStack;
            int cnt = 0;
            while(copy != NULL && cnt < 8)
            {
                Team *team = copy->team;
                Team *newTeam = malloc(sizeof(Team));
                newTeam->numberOfPlayers = team->numberOfPlayers;
                newTeam->points = team->points;
                newTeam->teamName = strdup(team->teamName);
                newTeam->next = lastEightTeams;
                lastEightTeams = newTeam;
                copy = copy->next;
                cnt++;
            }
        }
        numberOfTeams/=2;
    }
    return lastEightTeams;
}

