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

    strftime(data, sizeof(data), "%Y-%m-%d", timeInfo);

    snprintf(arqName, sizeof(arqName), "log_dat_%s.txt", data);
    
    FILE *fp = fopen(arqName, "a");

    if(fp == NULL) {
        return 1;
    }

    fprintf(fp, "========================================\n");
    fprintf(fp, "===== %s =====\n", str->name);
    fprintf(fp, "Name: %s\n", str->name);
    fprintf(fp, "SN: %s\n", str->SN);
    fprintf(fp, "CPU: %s\n", str->cpuName);
    fprintf(fp, "RAM: %.2f\n", str->memorySize);
    fprintf(fp, "SSD: %.2f\n", str->storageSizeSSD);
    fprintf(fp, "HDD: %.2f\n", str->storageSizeHDD);
    fprintf(fp, "GPU: %s\n", str->gpuName);
    fprintf(fp, "Screen: \n");
    fprintf(fp, "Obs: \n");
    fprintf(fp, "\n");

    fclose(fp);
    return 0;
}