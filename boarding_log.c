#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

LogNode *logHead = NULL;
LogNode *logTail = NULL;

void addLog(Token t)
{
    LogNode *newNode = (LogNode *) malloc(sizeof(LogNode));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = t;
    newNode->next = NULL;

    if (logHead == NULL) {
        logHead = newNode;
        logTail = newNode;
    } else {
        logTail->next = newNode;
        logTail = newNode;
    }
}

void updateLogStatus(int tokenNo, const char *status)
{
    LogNode *current = logHead;

    while (current != NULL) {
        if (current->data.tokenNo == tokenNo) {
            strcpy(current->data.status, status);
            return;
        }
        current = current->next;
    }
}

/* linear search through the boarding log by token number */
void searchToken(void)
{
    int tokenNo;
    LogNode *current = logHead;

    printf("Enter token number to search: ");
    if (scanf("%d", &tokenNo) != 1) {
        clearInputBuffer();
        printf("Invalid token number.\n");
        return;
    }
    clearInputBuffer();

    while (current != NULL) {
        if (current->data.tokenNo == tokenNo) {
            printf("\nToken No   : %d\n", current->data.tokenNo);
            printf("Passenger  : %s\n", current->data.passengerName);
            printf("Status     : %s\n", current->data.status);
            return;
        }
        current = current->next;
    }
    printf("Token %d was not found.\n", tokenNo);
}

/* recursive function to count every token ever issued */
int countLogs(LogNode *node)
{
    if (node == NULL) {
        return 0;
    }
    return 1 + countLogs(node->next);
}

void freeLog(void)
{
    LogNode *current = logHead;
    LogNode *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    logHead = NULL;
    logTail = NULL;
}
