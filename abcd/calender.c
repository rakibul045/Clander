#include <stdio.h>
#include <time.h>

int main() {
    // Get current time
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    // Extract year and month
    int year = local->tm_year + 1900;
    int month = local->tm_mon + 1;

    // Determine the number of days in the month
    int daysInMonth;
    switch(month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31;
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                daysInMonth = 29;
            else
                daysInMonth = 28;
            break;
        default:
            printf("Invalid month.\n");
            return 1;
    }

    // Print calendar header
    printf("  %d/%d\n", month, year);
    printf(" Su Mo Tu We Th Fr Sa\n");
    printf("=====================\n");

    // Get the day of the week the month starts on
    struct tm firstOfMonth = {0};
    firstOfMonth.tm_year = local->tm_year;
    firstOfMonth.tm_mon = local->tm_mon;
    firstOfMonth.tm_mday = 1;
    mktime(&firstOfMonth);

    // Print leading spaces
    for (int i = 0; i < firstOfMonth.tm_wday; i++) {
        printf("   ");
    }

    // Print days of the month
    for (int day = 1; day <= daysInMonth; day++) {
        printf("%3d", day);
        if ((firstOfMonth.tm_wday + day) % 7 == 0) {
            printf("\n");
        }
    }

    // Print newline if necessary
    if ((firstOfMonth.tm_wday + daysInMonth) % 7 != 0) {
        printf("\n");
    }

    return 0;
}
