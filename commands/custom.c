#include "check.h"
#include "custom.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <errno.h> 

const userCustom defSettings = {
    .includeExtern = FALSE,
    .excludeSel = {
        [EXCLUDE_USB] = TRUE,
        [EXCLUDE_SSD] = FALSE,
        [EXCLUDE_HDD] = FALSE
    }
};

char cursorCheck(excludeOptions option) {
    if(option == TRUE) {
        return '*';
    }else {
        return '_';
    }
}

void listSettings(userCustom *settings) {
    printf("============ Current Settings ============\n");
    printf("[1] = Include Extern Devices: %c\n", cursorCheck(settings->includeExtern));
    printf("[2] = Exclude Selection:\n");
    printf("\t[USB] - %c\n\t[SSD] - %c\n\t[HDD] - %c\n", cursorCheck(settings->excludeSel[0]), cursorCheck(settings->excludeSel[1]), cursorCheck(settings->excludeSel[2]));
    printf("==========================================\n");
}

void useDefault(userCustom *settings) {
    *settings = defSettings;
}

int checkCustom(userCustom *settings) {
    FILE *custom = fopen("custom/custom.bin", "rb");

    if(custom == NULL) {
        switch(errno) {
            case ENOENT:
            return ENOENT;

            case EACCES:
            return EACCES;

            default:
            printf("custom is not available\n");
            return -1;
        }
    }

    if(fread(settings, sizeof(userCustom), 1, custom) != 1) {
        fclose(custom);
        return -1;
    }

    fclose(custom);

    return 0;
}

int configCustom(userCustom *settings) {
    char option, sub;
    
    do {
        system("cls");
        listSettings(settings);
        
        printf("Insert the number to change\n");
        option = getch();
        
        switch(option) {
            case '1':
            settings->includeExtern = !settings->includeExtern;
            break;
            
            case '2':
            printf("chose an sub option:\n");
            sub = getch();
            
            switch(sub) {
                case '1':
                settings->excludeSel[0] = !settings->excludeSel[0];
                break;
                
                case '2':
                settings->excludeSel[1] = !settings->excludeSel[1];
                break;
                
                case '3':
                settings->excludeSel[2] = !settings->excludeSel[2];
                break;
                
                case '4':
                return 0;
                
                default:
                printf("That's not valid!\n");
                
            }
            break;
            
            case '3':
            break;
            
            default:
            printf("That's not valid\n");
            break;
        }
    }while (option != '3');
    
    FILE *custom = fopen("custom/custom.bin", "wb");

    fwrite(settings, sizeof(userCustom), 1, custom);

    fclose(custom);
    
    return 0;
}