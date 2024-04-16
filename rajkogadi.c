#include <stdio.h>
#include <stdbool.h>// header file to perform functions

#define NUM_SEATS 32 // integer  constant for number of seat

typedef struct seat {
    int seatNumber;// declaring a structure  and using typedef to make own name of datatype
    bool isOccupied;
    int ticketNumber;
} Seat;

void displaymenu();
void viewSeatAvailability(Seat seats[]);// function prototypying
void bookSeat(Seat seats[]);
void cancelSeat(Seat seats[]);
void saveData(Seat seats[]);

int main() {
    Seat seats[NUM_SEATS];// array of structure
    int choice;

    FILE *file = fopen("sb.txt", "rb"); // Open file for reading in binary mode

    if (file == NULL) {// if file doent open or certain problem exists creating new file with all seats availanble
        for (int i = 0; i < NUM_SEATS; i++) {
            seats[i].seatNumber = i + 1;
            seats[i].isOccupied = false;
            seats[i].ticketNumber = 0;
        }
    } else {
        fread(seats, sizeof(Seat), NUM_SEATS, file); // Read data from file
        fclose(file); // closing file
    }

    do {
        displaymenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewSeatAvailability(seats); // passing array to function which is pass by reference
                break;
            case 2:
                bookSeat(seats);
                break;
            case 3:
                cancelSeat(seats);
                break;
            case 4:
                saveData(seats);
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);// a loop for bus ticket information which only ends if user presses 4

    return 0;// end of main function
}

void displaymenu() {
    printf("************************************************************************\n\t\t WELCOME TO RAJ TRAVELS\n");
    printf("1. View Seat Availability\n");
void viewSeatAvailability(Seat seats[]) ; // function to display the menu for booking ticket
    printf("2. Book a Seat\n");
    printf("3. Cancel Seat Reservation\n");
    printf("4. Exit\n");
}

void viewSeatAvailability(Seat seats[]) {
    printf("\nSeat Availability:\n");// function that checks wether the seat is available or not with ticket number of booked seats
    for (int i = 0; i < NUM_SEATS; i++) {
        if (seats[i].isOccupied==true) {// boolen value compared to check wether seat is available or not
            printf("Seat %d: Occupied (Ticket #: %d)\n", seats[i].seatNumber, seats[i].ticketNumber);
        } else {
            printf("Seat %d: Available\n", seats[i].seatNumber);
        }
    }
}

void bookSeat(Seat seats[]) {// function to book seat
    int seatNum;

    printf("\nEnter the seat number to book (1-%d): ", NUM_SEATS);
    scanf("%d", &seatNum);

    if (seatNum < 1 || seatNum > NUM_SEATS) {// seat available is only 32 so user cancel book any extra seat
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[seatNum - 1].isOccupied==true) {
        printf("Sorry, the seat is already occupied.\n");
    } else {
        seats[seatNum - 1].isOccupied = true;
        seats[seatNum - 1].ticketNumber = seatNum;// Assuming ticket number is seat number for simplicity
        printf("Seat %d booked successfully. Ticket #: %d\n", seatNum, seatNum);
    }
    saveData(seats);// saves changes of book seat by passing array to saveData function
}

void cancelSeat(Seat seats[]) {//function to cancel seat
    int seatNum;
    
    printf("\nEnter the seat number to cancel reservation: ");
    scanf("%d", &seatNum);

    if (seatNum < 1 || seatNum > NUM_SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[seatNum - 1].isOccupied==true) { // here if seat is already booked i.e boolen is true then the if statement works and makes boolen false i.e cancel sea
        seats[seatNum - 1].isOccupied = false;
        seats[seatNum - 1].ticketNumber = 0;
        printf("Reservation for seat %d cancelled.\n", seatNum);
    } else {
        printf("Seat %d is not occupied.\n", seatNum);
    }
    saveData(seats);// saves changes of cancel seat by passing array to saveData function
}

void saveData(Seat seats[]) {// function to save data that is added or changed by user
    FILE *file = fopen("sb.txt", "wb"); // Open file for writing in binary mode

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(seats, sizeof(Seat), NUM_SEATS, file); // Write data to file
    fclose(file);
}
