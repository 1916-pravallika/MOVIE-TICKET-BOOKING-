#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Ticket {
    int ticketNumber;
    char movieName[50];
    float ticketPrice;
    struct Ticket *next;
} Ticket;
Ticket* createTicket(int ticketNumber, char movieName[], float ticketPrice);
void bookTicket(Ticket **head, int ticketNumber, char movieName[], float ticketPrice);
void cancelTicket(Ticket **head, int ticketNumber);
void displayTickets(Ticket *head);
void refundAmount(Ticket **head, int ticketNumber);
int main() {
    Ticket *ticketList = NULL;
    int choice, ticketNumber;
    char movieName[50];
    float ticketPrice;
   do {
        printf("\n1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Display Tickets\n");
        printf("4. Refund Ticket\n");
        printf("5. Exit\n"); 
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter ticket number: ");
                scanf("%d", &ticketNumber);
                printf("Enter movie name: ");
                scanf("%s", movieName);
                scanf("%f", &ticketPrice);
bookTicket(&ticketList, ticketNumber, movieName, ticketPrice);
                break;
            case 2:
                printf("Enter ticket number to cancel: ");
                scanf("%d", &ticketNumber);
                cancelTicket(&ticketList, ticketNumber);
                break;
            case 3:
                displayTickets(ticketList);
                break;
            case 4:
                printf("Enter ticket number to refund: ");
                scanf("%d", &ticketNumber);
                refundAmount(&ticketList, ticketNumber); // Provide the ticketList and ticketNumber
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);
    return 0;
}
Ticket* createTicket(int ticketNumber, char movieName[], float ticketPrice) {
    Ticket *newTicket = (Ticket*)malloc(sizeof(Ticket));
    newTicket->ticketNumber = ticketNumber;
    strcpy(newTicket->movieName, movieName);
    newTicket->ticketPrice = ticketPrice;
newTicket->next = NULL;
    return newTicket;
}
void bookTicket(Ticket **head, int ticketNumber, char movieName[], float ticketPrice) {
    Ticket *newTicket = createTicket(ticketNumber, movieName, ticketPrice);
    if (*head == NULL) {
        *head = newTicket;
    } else {
        Ticket *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTicket;
    }
    printf("Ticket booked successfully!\n");
}
void cancelTicket(Ticket **head, int ticketNumber) {
    Ticket *prev = NULL;
    Ticket *temp = *head;
    while (temp != NULL && temp->ticketNumber != ticketNumber) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Ticket not found.\n");
        return;
    }
    if (prev == NULL) {
        *head = temp->next;
    } else
 {
    prev->next = temp->next;
    }
       free(temp);
    printf("Ticket cancelled successfully!\n");
}
void displayTickets(Ticket *head) {
    if (head == NULL) {
        printf("No tickets booked.\n");
        return;
    }
    printf("Ticket Number\tMovie Name\tTicket Price\n");
    while (head != NULL) {
        printf("%d\t\t%s\t\t%.2f\n", head->ticketNumber, head->movieName, head->ticketPrice);
        head = head->next;
    }
}
void refundAmount(Ticket **head, int ticketNumber) {
    Ticket *temp = *head;
    Ticket *prev = NULL;
    while (temp != NULL && temp->ticketNumber != ticketNumber) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Ticket not found.\n");
        return;
    }
    float refundedAmount = temp->ticketPrice;
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Ticket with ticket number %d refunded successfully. Refunded amount: %.2f\n", ticketNumber, refundedAmount);
}
