#ifndef PROJECT_H
#define PROJECT_H

#define MAX_TOKENS 50
#define NAME_LEN 50
#define DATA_FILE "token_queue.txt"

typedef struct Token {
    int tokenNo;
    char passengerName[NAME_LEN];
    char status[12];   /* "Waiting", "Boarded", or "Cancelled" */
} Token;

/* singly linked list node - permanent boarding log */
typedef struct LogNode {
    Token data;
    struct LogNode *next;
} LogNode;

/* ---- shared global data ---- */
extern Token queueArr[MAX_TOKENS];   /* defined in circular_queue.c - the circular queue */
extern int front;
extern int rear;
extern int count;
extern int nextToken;
extern Token boardedStack[MAX_TOKENS]; /* defined in circular_queue.c - undo stack */
extern int stackTop;
extern LogNode *logHead;             /* defined in boarding_log.c */
extern LogNode *logTail;

/* ---------------- circular_queue.c : Circular Queue (array) + undo Stack (array) ---------------- */
void issueToken(void);
void boardPassenger(void);
void cancelToken(void);
void undoBoarding(void);
void displayQueue(void);

/* ---------------- boarding_log.c : linked list + linear search + recursion ---------------- */
void addLog(Token t);
void updateLogStatus(int tokenNo, const char *status);
void searchToken(void);
int countLogs(LogNode *node);
void freeLog(void);

/* ---------------- sort_stats.c : Insertion Sort, statistics, file I/O ---------------- */
void sortLogByName(void);
void displayStatistics(void);
void saveData(void);
void loadData(void);

/* ---------------- main.c ---------------- */
void clearInputBuffer(void);

#endif
