#include "shellCommand.h"
#include "check.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkName(systemInfo *str) {
    FILE *fp = popen(SYSTEM_NAME, "r");

    if(fp == NULL) {
        strcpy(str->name, "Can t read name");
        return 1;
    }

    while (fgets(str->name, sizeof(str->name), fp) != NULL) {
        str->name[strcspn(str->name, "\r\n")] = '\0';

        if(strstr(str->name, "Model") != NULL) {
            continue;
        }

        if(strstr(str->name, "---") != 0) {
            continue;
        }

        if(strlen(str->name) > 0) {
            break;
        }
    }

    pclose(fp);
    return 0;
}

int checkSN(systemInfo *str) {
    FILE *fp = popen(SN_ID, "r");

    if(fp == NULL) {
        strcpy(str->SN, "Can't read");
        str->SN[sizeof(str->SN) - 1];
        return 1;
    }

    fgets(str->SN, sizeof(str->SN), fp);

    pclose(fp);
    return 0;
}