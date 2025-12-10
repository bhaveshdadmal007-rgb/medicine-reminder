#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_MEDICINES 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int dosage;  
    int hour;       
    int minute;      
} Medicine;

Medicine schedule[MAX_MEDICINES];
int medicineCount = 0;

void addMedicine();
void displaySchedule();
void checkReminders();
void clearInputBuffer();

int main() {
    int choice;

    printf("--- Welcome to the Medicine Reminder System ---\n");

    do {
        printf("\nMain Menu:\n");
        printf("1. Add Medicine\n");
        printf("2. View Schedule\n");
        printf("3. Check for Active Reminders (Current Time)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addMedicine();
                break;
            case 2:
                displaySchedule();
                break;
            case 3:
                checkReminders();
                break;
            case 4:
                printf("Exiting... Stay healthy!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void addMedicine() {
    if (medicineCount >= MAX_MEDICINES) {
        printf("Error: Schedule is full!\n");
        return;
    }

    Medicine newMed;

    printf("\n--- Add New Medicine ---\n");
    printf("Enter Medicine Name: ");
    fgets(newMed.name, NAME_LEN, stdin);
    newMed.name[strcspn(newMed.name, "\n")] = 0;

    printf("Enter Dosage (number of pills/units): ");
    scanf("%d", &newMed.dosage);

    printf("Enter Reminder Time (Hour 0-23): ");
    scanf("%d", &newMed.hour);

    printf("Enter Reminder Time (Minute 0-59): ");
    scanf("%d", &newMed.minute);
    
    if (newMed.hour < 0 || newMed.hour > 23 || newMed.minute < 0 || newMed.minute > 59) {
        printf("Invalid time entered! Medicine not added.\n");
        return;
    }

    schedule[medicineCount] = newMed;
    medicineCount++;
    printf("Medicine added successfully!\n");
}

void displaySchedule() {
    if (medicineCount == 0) {
        printf("\nNo medicines in the schedule.\n");
        return;
    }

    printf("\n--- Daily Medicine Schedule ---\n");
    printf("%-20s | %-10s | %-10s\n", "Medicine Name", "Dosage", "Time");
    printf("----------------------------------------------------\n");
    
    for (int i = 0; i < medicineCount; i++) {
        printf("%-20s | %-10d | %02d:%02d\n", 
               schedule[i].name, 
               schedule[i].dosage, 
               schedule[i].hour, 
               schedule[i].minute);
    }
}

void checkReminders() {
    time_t now;
    struct tm *local;
    int reminderFound = 0;

    time(&now);
    local = localtime(&now);

    printf("\n--- Checking Reminders ---\n");
    printf("Current System Time: %02d:%02d\n", local->tm_hour, local->tm_min);

    for (int i = 0; i < medicineCount; i++) {

        if (local->tm_hour == schedule[i].hour && local->tm_min == schedule[i].minute) {
            printf("\n>>> ALARM! Take your medicine: %s (Dosage: %d) <<<\n", 
                   schedule[i].name, schedule[i].dosage);
            reminderFound = 1;
        }
    }

    if (!reminderFound) {
        printf("No medicines scheduled for exactly this minute.\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}