#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

#include "shellCommand.h"
#include "check.h"
#include "register.h"

int main() {
    systemInfo str;
    char option;

    printf("===================\n");
    printf("   HardwareScan\n");
    printf("===================\n");
    printf("Select an option:\n");

    printf("[1] - AutoScan\n");
    printf("[2] - Manual Register\n");
    printf("[3] - Empty option\n");
    printf("[4] - Exit\n");

    option = getch();

    while(1) {
        switch(option) {
            case '1':
            autoScan(&str);
            reg(&str);
            return 0;

            case '2':
            return 0;
            
            case '3':
            return 0;
            
            case '4':
            printf("Canceled...\n");
            system("pause");
            return 0;

            default:
            printf("That's not valid, please try again\n");
            break;
        }
    }
    system("pause");
    return 0;
}