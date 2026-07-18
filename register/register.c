#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "check.h"

int reg(systemInfo *str) {
    time_t timeG;
    struct tm *timeInfo;

    time(&timeG);
    timeInfo = localtime(&timeG);

    char data[64];
    char arqName[50];

    strftime(data, sizeof(data), "%Y-%m-%d_%H-%M", timeInfo);

    snprintf(arqName, sizeof(arqName), "log_dat_%s.txt", data);
    
    FILE *fp = fopen(arqName, "a");

    if(fp == NULL) {
        return 1;
    }

    fprintf(fp, "===== %s =====\n", str->name);
    fprintf(fp, "Nome: %s\n", str->name);
    fprintf(fp, "SN: %s\n", str->SN);
    fprintf(fp, "CPU: %s\n", str->cpuName);
    fprintf(fp, "Memória: %s\n", str->memorySize);
    fprintf(fp, "SSD: %s\n", str->storageSizeSSD);
    fprintf(fp, "HDD: %s\n", str->storageSizeHDD);
    fprintf(fp, "GPU: %s\n", str->gpuName);

    fclose(fp);
    printf("Sucess...");
    return 0;
}