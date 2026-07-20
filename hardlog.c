#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#include "shellCommand.h"
#include "check.h"
#include "register.h"

void checkPath(char *exePath) {
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    char *last = strrchr(exePath, '\\');

    if(last != NULL) {
        *last = '\0';
    }

    SetCurrentDirectoryA(exePath);
}

int main() {
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    systemInfo str = {0};
    char option;
    char exePath[MAX_PATH];
    char file[50];

    checkPath(exePath);

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
            system("cls");
            autoScan(&str);
            reg(&str);
            system("pause");
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