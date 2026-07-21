#include <stdio.h>
#include <time.h>
#include <string.h>
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
    FILE *bin = fopen("data.bin", "ab");

    if(fp == NULL || bin == NULL) {
        if(fp) fclose(fp);
        if(bin) fclose(bin);
        return 1;
    }

    fprintf(fp, "========================================\n");
    fprintf(fp, "===== %s =====\n", str->name);
    fprintf(fp, "Name: %s\n", str->name);
    fprintf(fp, "SN: %s\n", str->SN);
    fprintf(fp, "CPU: %s\n", str->cpuName);
    fprintf(fp, "RAM: %.2f\n", str->memorySize);
    for(int i = 0; i < str->countSSD; i++) {
        fprintf(fp, "SSD [%d]: \n   Name: %s\n   Size: %.2fGB\n", i, str->storSSD[i].name, str->storSSD[i].size);
    }
    for(int i = 0; i < str->countHDD; i++) {
        fprintf(fp, "HDD [%d]: \n   Name: %s\n   Size: %.2fGB\n", i, str->storHDD[i].name, str->storHDD[i].size);
    }
    fprintf(fp, "GPU: %s\n", str->gpuName);
    fprintf(fp, "Screen: \n");
    fprintf(fp, "Obs: \n");
    fprintf(fp, "\n");

    fwrite(str, sizeof(*str), 1, bin);

    fclose(bin);
    fclose(fp);
    return 0;
}

int manualReg(systemInfo *str) {
    printf("Name: ");
    fgets(str->name, sizeof(str->name), stdin);
    str->name[strcspn(str->name, "\n")] = '\0';
    printf("SN: ");
    fgets(str->SN, sizeof(str->SN), stdin);
    str->SN[strcspn(str->SN, "\n")] = '\0';
    printf("CPU: ");
    fgets(str->cpuName, sizeof(str->cpuName), stdin);
    str->cpuName[strcspn(str->cpuName, "\n")] = '\0';
    printf("RAM: ");
    scanf("%f", &str->memorySize);
    getchar();
    printf("Count SSD: ");
    scanf("%d", &str->countSSD);
    getchar();
    for(int i = 0; i < str->countSSD; i++) {
        strcpy(str->storSSD[i].name, "");
        printf("SSD [%d]: ", i);
        scanf("%f", &str->storSSD[i].size);
        getchar();
    }
    printf("Count HDD: ");
    scanf("%d", &str->countHDD);
    getchar();
    for(int i = 0; i < str->countHDD; i++) {
        strcpy(str->storHDD[i].name, "");
        printf("HDD [%d]: ", i);
        scanf("%f", &str->storHDD[i].size);
        getchar();
    }
    printf("GPU: ");
    fgets(str->gpuName, sizeof(str->gpuName), stdin);
    str->gpuName[strcspn(str->gpuName, "\n")] = '\0';

    reg(str);
    return 0;
}