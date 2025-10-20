#include <stdio.h>
#include "MS2401_fun.h"

Port LAN[MAX_HOSTS][2];  
void connector() {
    printf("\nInitializing LAN...\n");
    for (int i = 0; i < MAX_HOSTS; i++) {
        LAN[i][IN].buffer = EMPTY;
        LAN[i][IN].busy = 0;
        LAN[i][OUT].buffer = EMPTY;
        LAN[i][OUT].busy = 0;
    }
    printf("All ports initialized (empty).\n");
}

void LAN_func() {
    printf("\n--- LAN Port Status ---\n");
    printf("Host\tIN_Buffer\tOUT_Buffer\n");
    for (int i = 0; i < MAX_HOSTS; i++) {
        char hostName = 'A' + i;
        printf("%c\t%d\t\t%d\n",
               hostName,
               LAN[i][IN].buffer,
               LAN[i][OUT].buffer);
    }
}

void LLL() {
    char src, dest;
    int data;

    printf("\nEnter source host (A-Z): ");
    scanf(" %c", &src);
    printf("Enter destination host (A-Z): ");
    scanf(" %c", &dest);
    printf("Enter data (integer): ");
    scanf("%d", &data);

    int s = src - 'A';
    int d = dest - 'A';

    if (LAN[s][OUT].busy) {
        printf("Source host %c's OUT port is busy!\n", src);
        return;
    }

    LAN[s][OUT].buffer = data;
    LAN[s][OUT].busy = 1;

    printf("Host %c sends data %d to host %c...\n", src, data, dest);

    if (LAN[d][IN].busy) {
        printf("Destination host %c's IN port is busy! Collision detected.\n", dest);
        LAN[s][OUT].buffer = EMPTY;
        LAN[s][OUT].busy = 0;
        return;
    }

    LAN[d][IN].buffer = LAN[s][OUT].buffer;
    LAN[d][IN].busy = 1;

    LAN[s][OUT].buffer = EMPTY;
    LAN[s][OUT].busy = 0;

    printf("Data successfully transferred to host %c's IN port.\n", dest);
}

void test_program() {
    printf("\n--- Checking Received Data ---\n");
    for (int i = 0; i < MAX_HOSTS; i++) {
        if (LAN[i][IN].busy) {
            char hostName = 'A' + i;
            printf("Host %c received data: %d\n", hostName, LAN[i][IN].buffer);
            LAN[i][IN].buffer = EMPTY;
            LAN[i][IN].busy = 0;
        }
    }
    printf("All IN buffers cleared.\n");
}

void scheduler() {
    int choice;
    connector();

    do {
        printf("LAN Simulator Menu\n");
        printf("1. Show LAN Status\n");
        printf("2. Send Data (LLL)\n");
        printf("3. Test Received Data\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                LAN_func();
                break;
            case 2:
                LLL();
                break;
            case 3:
                test_program();
                break;
            case 4:
                printf("Exiting simulation.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 4);
}

