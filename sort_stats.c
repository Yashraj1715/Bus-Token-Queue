#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

void sortLogByName(void)
{
    Token temp[MAX_TOKENS * 4];
    int total = countLogs(logHead);
    int i, j;
    Token key;
    LogNode *current = logHead;

    if (total == 0) {
        printf("\nNo tokens have been issued yet.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        temp[i] = current->data;
        current = current->next;
    }

    for (i = 1; i < total; i++) {
        key = temp[i];
        j = i - 1;
        while (j >= 0 && strcmp(temp[j].passengerName, key.passengerName) > 0) {
            temp[j + 1] = temp[j];
            j--;
        }
        temp[j + 1] = key;
    }

    printf("\nBoarding log sorted by passenger name (Insertion Sort):\n");
    printf("Token No  Passenger          Status\n");
    printf("--------------------------------------------\n");
    for (i = 0; i < total; i++) {
        printf("%-9d %-18s %s\n", temp[i].tokenNo, temp[i].passengerName, temp[i].status);
    }
}

void displayStatistics(void)
{
    printf("\n--- Token Queue Statistics ---\n");
    printf("Tokens currently waiting : %d\n", count);
    printf("Next token number to be issued : %d\n", nextToken);
    printf("Total tokens issued today (recursive count) : %d\n", countLogs(logHead));
}

void saveData(void)
{
    FILE *fp = fopen(DATA_FILE, "w");
    int i, idx, logCount;
    LogNode *current;

    if (fp == NULL) {
        printf("Could not save data.\n");
        return;
    }

    fprintf(fp, "%d\n", nextToken);
    fprintf(fp, "QUEUE %d\n", count);
    for (i = 0; i < count; i++) {
        idx = (front + i) % MAX_TOKENS;
        fprintf(fp, "Q|%d|%s|%s\n", queueArr[idx].tokenNo, queueArr[idx].passengerName, queueArr[idx].status);
    }

    logCount = countLogs(logHead);
    fprintf(fp, "LOG %d\n", logCount);
    for (current = logHead; current != NULL; current = current->next) {
        fprintf(fp, "L|%d|%s|%s\n", current->data.tokenNo, current->data.passengerName, current->data.status);
    }

    fclose(fp);
    printf("Data saved to %s\n", DATA_FILE);
}

void loadData(void)
{
    FILE *fp = fopen(DATA_FILE, "r");
    char line[300];
    char *token;
    int n, i;

    if (fp == NULL) {
        return; /* no saved data yet */
    }

    if (fgets(line, sizeof(line), fp) != NULL) {
        nextToken = atoi(line);
    }

    if (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "QUEUE %d", &n);
        front = 0;
        count = n;
        rear = n - 1;
        for (i = 0; i < n && fgets(line, sizeof(line), fp) != NULL; i++) {
            line[strcspn(line, "\n")] = '\0';
            token = strtok(line, "|"); /* "Q" marker */
            token = strtok(NULL, "|"); queueArr[i].tokenNo = atoi(token);
            token = strtok(NULL, "|"); strcpy(queueArr[i].passengerName, token);
            token = strtok(NULL, "|"); strcpy(queueArr[i].status, token);
        }
    }

    if (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "LOG %d", &n);
        for (i = 0; i < n && fgets(line, sizeof(line), fp) != NULL; i++) {
            Token t;
            line[strcspn(line, "\n")] = '\0';
            token = strtok(line, "|"); /* "L" marker */
            token = strtok(NULL, "|"); t.tokenNo = atoi(token);
            token = strtok(NULL, "|"); strcpy(t.passengerName, token);
            token = strtok(NULL, "|"); strcpy(t.status, token);
            addLog(t);
        }
    }

    fclose(fp);
}
