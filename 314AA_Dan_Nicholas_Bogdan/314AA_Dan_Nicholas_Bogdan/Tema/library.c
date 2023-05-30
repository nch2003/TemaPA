
#include "library.h"

void insertPlayer(Team **team, char firstName[], char secondName[], int points)
{
    PlayerNode *newPlayerNode = malloc(sizeof(PlayerNode));
    newPlayerNode->player.firstName = strdup(firstName);
    newPlayerNode->player.secondName = strdup(secondName);
    newPlayerNode->player.points = points;
    newPlayerNode->next = (*team)->players;
    (*team)->players = newPlayerNode;
}

void printList(Team *head, FILE *out)
{

    Team *team = head;
    while (team != NULL)
    {
        fputs(team->teamName, out);
        fputs("\n", out);
        team = team->next;
    }
}
void findLowestTeamPoints(Team **head)
{
    Team *lowestTeam = *head;
    lowestTeam->points = (*head)->points;
    Team *current = *head;
    while (current != NULL)
    {
        if (current->points < lowestTeam->points)
        {
            lowestTeam = current;
            lowestTeam->points = current->points;
        }
        current = current->next;
    }
    if (*head == lowestTeam)
        *head = lowestTeam->next;
    else
    {
        Team *prev = *head;
        while (prev->next != lowestTeam)
            prev = prev->next;

        prev->next = lowestTeam->next;
    }
    free(lowestTeam);
}

int PowerOf2(int n)
{
    int number = 1;
    while (number * 2 <= n)
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
    if (*stack == NULL)
        return NULL;

    Team *team = (*stack)->team;
    // Stack *temp = (*stack);
    *stack = (*stack)->next;
    // free(temp);

    return team;
}

void enqueue(MatchQueue *queue, Team *Team_1, Team *Team_2)
{
    MatchNode *newMatchNode = malloc(sizeof(MatchNode));
    newMatchNode->Team_1 = Team_1;
    newMatchNode->Team_2 = Team_2;
    newMatchNode->next = NULL;

    if (queue->rear == NULL)
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
    if (queue->front == NULL)
        return NULL;

    MatchNode *newMatchNode = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    return newMatchNode;
}

void proccesMatch(Team *Team_1, Team *Team_2, Stack **winnersStack, Stack **losersStack)
{
    if (Team_1->points > Team_2->points)
    {
        push(winnersStack, Team_1);
        push(losersStack, Team_2);
        Team_1->points++;
    }
    else if (Team_1->points <= Team_2->points)
    {
        push(winnersStack, Team_2);
        push(losersStack, Team_1);
        Team_2->points++;
    }
    /*else if(Team_1->points == Team_2->points)
    {
        push(winnersStack, Team_2);
        push(winnersStack, Team_1);
        Team_2->points++;
    }*/
}

Team *Matches(Team *head, int numberOfTeams, FILE *out)
{

    MatchQueue matchQueue;
    matchQueue.front = NULL;
    matchQueue.rear = NULL;
    Stack *winnersStack = NULL;
    Stack *losersStack = NULL;
    Team *Team_1 = head;
    Team *Team_2 = head->next;
    Team *lastEightTeams = NULL;
    int i = 1;
    while (numberOfTeams != 1)
    {

        fprintf(out, "\n--- ROUND NO:%d\n", i);
        if (winnersStack == NULL)
        {
            while (Team_1 != NULL && Team_2 != NULL)
            {
                enqueue(&matchQueue, Team_1, Team_2);
                Team_1 = Team_2->next;
                if (Team_1 != NULL)
                    Team_2 = Team_1->next;
            }
        }
        else
        {
            while (winnersStack != NULL)
            {
                Team_1 = pop(&winnersStack);
                Team_2 = pop(&winnersStack);
                enqueue(&matchQueue, Team_1, Team_2);
            }
        }
        while (matchQueue.front != NULL)
        {
            MatchNode *currentMatch = matchQueue.front;

            fprintf(out, "%-33s-%33s\n", currentMatch->Team_1->teamName, currentMatch->Team_2->teamName);
            dequeue(&matchQueue);
            proccesMatch(currentMatch->Team_1, currentMatch->Team_2, &winnersStack, &losersStack);
            free(currentMatch);
        }
        if (numberOfTeams == 16)
        {
            Stack *copy = winnersStack;
            int cnt = 0;
            while (copy != NULL && cnt < 8)
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
        fprintf(out, "\nWINNERS OF ROUND NO:%d\n", i);
        Stack *current = winnersStack;
        while (current != NULL)
        {
            fprintf(out, "%-33s -  %.2f\n", current->team->teamName, current->team->points);
            pop(&current);
        }
        i++;
        numberOfTeams /= 2;
    }
    return lastEightTeams;
}

BST *createBSTNode(Team *team)
{
    BST *newNode = malloc(sizeof(BST));
    newNode->team = team;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BST *insertBSTNode(BST *root, Team *team)
{
    if (root == NULL)
        return createBSTNode(team);

    int res = 0;
    if (team->points < root->team->points)
        res = -1;
    else if (team->points > root->team->points)
        res = 1;
    else
    {
        res = strcmp(team->teamName, root->team->teamName);
        if (res == 0)
            res = -1;
    }

    if (res < 0)
        root->left = insertBSTNode(root->left, team);
    else
        root->right = insertBSTNode(root->right, team);

    return root;
}
void Display(BST *root, FILE *out)
{

    if (root == NULL)
        return;

    Display(root->right, out);
    fprintf(out, "%-33s -  %.2f\n", root->team->teamName, root->team->points);
    Display(root->left, out);
}
