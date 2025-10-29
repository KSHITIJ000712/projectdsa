#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5     // Number of rows in stadium
#define COLS 10    // Number of seats per row
#define TOTAL_SEATS (ROWS * COLS)

typedef struct {
    int seatNumber;
    int isBooked;          // 0 = empty, 1 = booked
    char name[50];
} Seat;

Seat stadium[ROWS][COLS];
char stadiumName[100];
char matchName[100];

// Function to initialize all seats
void initializeSeats() {
    int count = 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            stadium[i][j].seatNumber = count++;
            stadium[i][j].isBooked = 0;
            strcpy(stadium[i][j].name, "EMPTY");
        }
    }
}

// Function to display seating layout
void displaySeats() {
    printf("\n------------------------------------------------------\n");
    printf("🏟️  STADIUM: %s\n", stadiumName);
    printf("⚽ MATCH: %s\n", matchName);
    printf("------------------------------------------------------\n");
    printf("Seat Layout (O = Empty | X = Booked)\n\n");

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (stadium[i][j].isBooked)
                printf("[X] ");
            else
                printf("[O] ");
        }
        printf("\n");
    }
}

// Function to count empty seats
int countEmptySeats() {
    int empty = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (!stadium[i][j].isBooked)
                empty++;
        }
    }
    return empty;
}

// Function to book a seat
void bookSeat() {
    int seatNo;
    char name[50];
    printf("\nEnter seat number to book (1 - %d): ", TOTAL_SEATS);
    scanf("%d", &seatNo);

    if (seatNo < 1 || seatNo > TOTAL_SEATS) {
        printf("Invalid seat number!\n");
        return;
    }

    int row = (seatNo - 1) / COLS;
    int col = (seatNo - 1) % COLS;

    if (stadium[row][col].isBooked) {
        printf("Seat %d is already booked by %s!\n", seatNo, stadium[row][col].name);
    } else {
        printf("Enter your name: ");
        scanf("%s", name);
        stadium[row][col].isBooked = 1;
        strcpy(stadium[row][col].name, name);
        printf("✅ Seat %d booked successfully by %s!\n", seatNo, name);
    }
}

// Function to cancel a booking
void cancelBooking() {
    int seatNo;
    printf("\nEnter seat number to cancel (1 - %d): ", TOTAL_SEATS);
    scanf("%d", &seatNo);

    if (seatNo < 1 || seatNo > TOTAL_SEATS) {
        printf("Invalid seat number!\n");
        return;
    }

    int row = (seatNo - 1) / COLS;
    int col = (seatNo - 1) % COLS;

    if (!stadium[row][col].isBooked) {
        printf("Seat %d is already empty!\n", seatNo);
    } else {
        printf("Booking for seat %d (Name: %s) is cancelled.\n", seatNo, stadium[row][col].name);
        stadium[row][col].isBooked = 0;
        strcpy(stadium[row][col].name, "EMPTY");
    }
}

// Function to show booking summary
void showSummary() {
    int booked = TOTAL_SEATS - countEmptySeats();
    printf("\n---------- STADIUM SUMMARY ----------\n");
    printf("🏟️  Stadium Name     : %s\n", stadiumName);
    printf("⚽ Match              : %s\n", matchName);
    printf("Total Seats          : %d\n", TOTAL_SEATS);
    printf("Booked Seats         : %d\n", booked);
    printf("Available Seats      : %d\n", countEmptySeats());
    printf("------------------------------------\n");
}

// Main menu
int main() {
    int choice;

    // Take match and stadium name from user
    printf("Enter Stadium Name: ");
    fgets(stadiumName, sizeof(stadiumName), stdin);
    stadiumName[strcspn(stadiumName, "\n")] = '\0';  // remove newline

    printf("Enter Match Name: ");
    fgets(matchName, sizeof(matchName), stdin);
    matchName[strcspn(matchName, "\n")] = '\0';

    initializeSeats();

    do {
        printf("\n=========== FOOTBALL STADIUM TICKET BOOKING SYSTEM ===========\n");
        printf("🏟️  Stadium: %s | ⚽ Match: %s\n", stadiumName, matchName);
        printf("---------------------------------------------------------------\n");
        printf("1. Display Stadium Seats\n");
        printf("2. Book a Seat\n");
        printf("3. Cancel a Booking\n");
        printf("4. Show Booking Summary\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySeats();
                break;
            case 2:
                bookSeat();
                break;
            case 3:
                cancelBooking();
                break;
            case 4:
                showSummary();
                break;
            case 5:
                printf("Thank you for using the Football Stadium Booking System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}