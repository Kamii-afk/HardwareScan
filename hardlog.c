#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#include "shellCommand.h"
#include "check.h"
#include "searchall.h"
#include "register.h"

//Model for user settings
/* typedef struct {
    int includeExtern;
    int excludeOptins;
}customConfig;
customConfig custom; */

void checkPath(char *exePath) {
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    char *last = strrchr(exePath, '\\');

    if(last != NULL) {
        *last = '\0';
    }

    SetCurrentDirectoryA(exePath);
}

//TODO aply this custom setings on user interface
/* void profileConfig() {
    FILE *config = fopen("../custom.config.bin", "rb");
    if(config == NULL) {
        return 1;
    }

    fread(&custom, sizeof(customConfig), 1, config);
} */

int main() {
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    systemInfo str = {0};
    char option;
    char exePath[MAX_PATH];

    checkPath(exePath);
    
    do {
        printf("===================\n");
        printf("   HardwareScan\n");
        printf("===================\n");
        printf("Select an option:\n");
    
        printf("[1] - AutoScan\n");
        printf("[2] - Manual Register\n");
        printf("[3] - Search\n");
        printf("[4] - Exit\n");
    
        option = getch();

        switch(option) {
            case '1':
            system("cls");
            autoScan(&str);
            reg(&str);
            system("pause");
            return 0;

            case '2':
            system("cls");
            manualReg(&str);
            system("pause");
            return 0;
            
            case '3':
            {
            char searchType;
            char search[50];

            system("cls");
            printf("Type of Search:\n");
            printf("[1] - Name\n[2] - SN\n[3] - CPU\n[4] - GPU\n[5] - Exit\n");
            searchType = getch();
            printf("Search: ");
            fgets(search, sizeof(search), stdin);
            search[strcspn(search, "\n")] = '\0';

            switch(searchType) {
                case '1':
                searchAll(search, SEARCH_NAME);
                break;

                case '2':
                searchAll(search, SEARCH_SN);
                break;

                case '3':
                searchAll(search, SEARCH_CPU);
                break;

                case '4':
                searchAll(search, SEARCH_GPU);
                break;

                case '5':
                return 0;

                default:
                printf("Can't find this option\n");
                break;
            }
            system("pause");
            system("cls");
            }
            break;
            
            case '4':
            return 0;

            default:
            printf("That's not valid, please try again\n");
            system("pause");
            system("cls");
            break;
        }
    }while (option != '4');
    
    return 0;
}