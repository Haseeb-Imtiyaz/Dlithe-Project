#include <stdio.h>
#include <stdlib.h>
struct Bill {
    int id;
    int day;
    int month;
    int year;
    double unitsConsumed;
    double totalBill;
};

double calculateBill(double units) {
    #define ELECTRICITY_RATE 0.10
    return units * ELECTRICITY_RATE;
}

void addBill(struct Bill bills[], int *billCount) {
    if (*billCount < 100) { // Assuming a maximum of 100 bills
        struct Bill newBill;
        printf("Enter the date (day month year): ");
        scanf("%d %d %d", &newBill.day, &newBill.month, &newBill.year);
        printf("Enter the units of electricity consumed: ");
        scanf("%lf", &newBill.unitsConsumed);
        newBill.totalBill = calculateBill(newBill.unitsConsumed);
        newBill.id = *billCount + 1;
        bills[*billCount] = newBill;
        (*billCount)++;
        printf("Bill added successfully.\n");
    } else {
        printf("Maximum number of bills reached.\n");
    }
}

void displayBills(struct Bill bills[], int billCount) {
    printf("Bills:\n");
    printf("ID  Date        Units Consumed  Total Bill\n");
    for (int i = 0; i < billCount; i++) {
        printf("%-3d %02d/%02d/%04d   %.2lf            $%.2lf\n", bills[i].id, bills[i].day, bills[i].month, bills[i].year, bills[i].unitsConsumed, bills[i].totalBill);
    }
}

void deleteBill(struct Bill bills[], int *billCount, int idToDelete) {
    int found = 0;
    for (int i = 0; i < *billCount; i++) {
        if (bills[i].id == idToDelete) {
            found = 1;
            // Shift remaining bills to fill the gap
            for (int j = i; j < *billCount - 1; j++) {
                bills[j] = bills[j + 1];
            }
            (*billCount)--;
            printf("Bill with ID %d deleted successfully.\n", idToDelete);
            break;
        }
    }
    if (!found) {
        printf("Bill with ID %d not found.\n", idToDelete);
    }
}

int main() {
    struct Bill bills[100]; // Array to store bill records
    int billCount = 0;

    int choice;
    do {
        printf("\nElectricity Billing System Menu:\n");
        printf("1. Add a new bill\n");
        printf("2. Display all bills\n");
        printf("3. Delete a bill\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBill(bills, &billCount);
                break;
            case 2:
                displayBills(bills, billCount);
                break;
            case 3:
                {
                    int idToDelete;
                    printf("Enter the ID of the bill to delete: ");
                    scanf("%d", &idToDelete);
                    deleteBill(bills, &billCount, idToDelete);
                }
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}