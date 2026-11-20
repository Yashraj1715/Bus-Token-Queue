#include <stdio.h>
#include <string.h>
#include "project.h"

Token queueArr[MAX_TOKENS];
int front = 0;
int rear = -1;
int count = 0;
int nextToken = 1;

Token boardedStack[MAX_TOKENS];
int stackTop = -1;

static void enqueueToken(Token t)
{
    if (count >= MAX_TOKENS) {
        printf("Token queue is full.\n");
        return;
    }
    rear = (rear + 1) % MAX_TOKENS;
    queueArr[rear] = t;
    count++;
}

static void pushBoarded(Token t)
{
    if (stackTop >= MAX_TOKENS - 1) {
        return; /* stack full, extremely unlikely at this scale */
    }
    stackTop++;
    boardedStack[stackTop] = t;
}

static int popBoarded(Token *out)
{
    if (stackTop == -1) {
        return 0;
    }
    *out = boardedStack[stackTop];
    stackTop--;
    return 1;
}

void issueToken(void)
{
    Token t;

    t.tokenNo = nextToken;
    nextToken++;

    printf("Enter passenger name: ");
    fgets(t.passengerName, NAME_LEN, stdin);
    t.passengerName[strcspn(t.passengerName, "\n")] = '\0';

    strcpy(t.status, "Waiting");

    enqueueToken(t);
    addLog(t);

    printf("Token issued. Token number = %d\n", t.tokenNo);
}

void boardPassenger(void)
{
    Token candidate;

    while (count > 0) {
        candidate = queueArr[front];
        front = (front + 1) % MAX_TOKENS;
        count--;

        if (strcmp(candidate.status, "Cancelled") == 0) {
            continue; /* skip cancelled tokens automatically */
        }

        strcpy(candidate.status, "Boarded");
        updateLogStatus(candidate.tokenNo, "Boarded");
        pushBoarded(candidate);
        printf("Token %d (%s) has boarded.\n", candidate.tokenNo, candidate.passengerName);
        return;
    }

    printf("No passengers waiting to board.\n");
}

void cancelToken(void)
{
    int tokenNo, i, idx, found = 0;

    printf("Enter token number to cancel: ");
    if (scanf("%d", &tokenNo) != 1) {
        clearInputBuffer();
        printf("Invalid token number.\n");
        return;
    }
    clearInputBuffer();

    for (i = 0; i < count; i++) {
        idx = (front + i) % MAX_TOKENS;
        if (queueArr[idx].tokenNo == tokenNo && strcmp(queueArr[idx].status, "Waiting") == 0) {
            strcpy(queueArr[idx].status, "Cancelled");
            found = 1;
            break;
        }
    }

    if (found) {
        updateLogStatus(tokenNo, "Cancelled");
        printf("Token %d has been cancelled.\n", tokenNo);
    } else {
        printf("Token %d was not found in the waiting queue.\n", tokenNo);
    }
}

void undoBoarding(void)
{
    Token t;

    if (!popBoarded(&t)) {
        printf("Nothing to undo.\n");
        return;
    }

    strcpy(t.status, "Waiting");
    enqueueToken(t);
    updateLogStatus(t.tokenNo, "Waiting");

    printf("Token %d returned to the queue.\n", t.tokenNo);
}

void displayQueue(void)
{
    int i, idx;

    if (count == 0) {
        printf("\nNo tokens currently in the queue.\n");
        return;
    }

    printf("\nToken No  Passenger          Status\n");
    printf("--------------------------------------------\n");
    for (i = 0; i < count; i++) {
        idx = (front + i) % MAX_TOKENS;
        printf("%-9d %-18s %s\n", queueArr[idx].tokenNo, queueArr[idx].passengerName, queueArr[idx].status);
    }
}
