#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "check.h"
#include "searchall.h"

int searchAll(const char *value, searchTypes type) {
    FILE *bin = fopen("data/data.bin", "rb");
    systemInfo temp;

    while(fread(&temp, sizeof(systemInfo), 1, bin) == 1) {
        switch(type) {
            case SEARCH_NAME:
            if(strstr(temp.name, value)) {
                printStruct(&temp);
            }
            break;

            case SEARCH_SN:
            if(strcmp(temp.SN, value) == 0) {
                printStruct(&temp);
            }
            break;

            case SEARCH_CPU:
            if(strstr(temp.cpuName, value)) {
                printStruct(&temp);
            }
            break;

            case SEARCH_GPU:
            if(strstr(temp.gpuName, value)) {
                printStruct(&temp);
            }
            break;
        }
    }

    fclose(bin);
    return 0;
}