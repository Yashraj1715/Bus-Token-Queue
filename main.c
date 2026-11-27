#include <stdio.h>
#include "project.h"

int main(void)
{
    int choice;

    loadData();

    do {
        printf("\n===== Bus / Shuttle Token Queue =====\n");
        printf("1. Issue a new token\n");
        printf("2. Board next passenger\n");
        printf("3. Undo last boarding\n");
        printf("4. Cancel a token\n");
        printf("5. Search a token by number\n");
        printf("6. Display current queue\n");
        printf("7. Sort & display boarding log by name (Insertion Sort)\n");
        printf("8. Display statistics\n");
        printf("9. Save and exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = 0;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: issueToken(); break;
            case 2: boardPassenger(); break;
            case 3: undoBoarding(); break;
            case 4: cancelToken(); break;
            case 5: searchToken(); break;
            case 6: displayQueue(); break;
            case 7: sortLogByName(); break;
            case 8: displayStatistics(); break;
            case 9: saveData(); printf("Goodbye!\n"); break;
            default: printf("Invalid choice, please try again.\n");
        }
    } while (choice != 9);

    freeLog();
    return 0;
}

void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}
