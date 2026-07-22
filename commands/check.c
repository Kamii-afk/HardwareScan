#include "shellCommand.h"
#include "check.h"
#include "filter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
        return 1;
    }

    while(fgets(str->SN, sizeof(str->SN), fp) != NULL) {
        str->SN[strcspn(str->SN, "\r\n")] = '\0';

        if(strstr(str->SN, "Serial") != NULL || strstr(str->SN, "Number") != NULL) {
            continue;
        }

        if(strstr(str->SN, "---") != NULL) {
            continue;
        }

        if(strlen(str->SN) > 0) {
            break;
        }
    }

    pclose(fp);
    return 0;
}

int checkCPU(systemInfo *str) {
    FILE *fp = popen(CPU_NAME, "r");

    if(fp == NULL) {
        strcpy(str->cpuName, "Can't read");
        return 1;
    }

    while(fgets(str->cpuName, sizeof(str->cpuName), fp) != NULL) {
        str->cpuName[strcspn(str->cpuName, "\r\n")] = '\0';

        if(strstr(str->cpuName, "Name") != NULL) {
            continue;
        }

        if(strstr(str->cpuName, "---") != NULL) {
            continue;
        }

        if(strlen(str->cpuName) > 0) {
            break;
        }
    }

    pclose(fp);
    return 0;
}

int checkMemory(systemInfo *str) {
    FILE *fp = popen(MEMORY_SIZE, "r");
    char buffer[64] = {0};

    if(fp == NULL) {
        return 1;
    }

    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if(strlen(buffer) > 0) break;
    }

    pclose(fp);
    
    unsigned long long bytesValue = strtoull(buffer, NULL, 10);
    str->memorySize = (float)bytesValue / (1024 * 1024 * 1024);
    memoryFilter(str);

    return 0;
}

int checkNameSSD(systemInfo *str) {
    FILE *fp = popen(SSD_NAME, "r");
    char buffer[64] = {0};
    str->countSSD = 0;

    if(fp == NULL) {
        return 1;
    }

    while(fgets(buffer, sizeof(buffer), fp)) {
        if(str->countSSD >=MAX_STORAGE) {
            break;
        }

        buffer[strcspn(buffer, "\n\r")] = '\0';

        if(strstr(buffer, "FriendlyName") != NULL) {
            continue;
        }

        if(strstr(buffer, "---") != NULL) {
            continue;
        }

        if(strlen(buffer) == 0) {
            continue;
        }

        strcpy(str->storSSD[str->countSSD].name, buffer);
        str->countSSD++;
    }

    pclose(fp);
    return 0;
}

int checkStorageSSD(systemInfo *str) {
    FILE *fp = popen(SSD_SIZE, "r");
    char buffer[64] = {0};
    str->countSSD = 0;

    if(fp == NULL) {
        return 1;
    }

    while(fgets(buffer, sizeof(buffer), fp)) {
        if(str->countSSD >= MAX_STORAGE) {
            break;
        }
        
        buffer[strcspn(buffer, "\n\r")] = '\0';

        if(strstr(buffer, "Size") != NULL) {
            continue;
        }

        if(strstr(buffer, "---") != NULL) {
            continue;
        }

        if(strlen(buffer) == 0) {
            continue;
        }

        unsigned long long bytesSize = strtoull(buffer, NULL, 10);
        str->storSSD[str->countSSD].size = (float)bytesSize / (1024 * 1024 * 1024);
        storageFilter(1, str);
        str->countSSD++;
    }

    pclose(fp);
    return 0;
}

int checkNameHDD(systemInfo *str) {
    FILE *fp = popen(HDD_NAME, "r");
    char buffer[64] = {0};
    str->countHDD = 0;

    if(fp == NULL) {
        return 1;
    }

    while(fgets(buffer, sizeof(buffer), fp)) {
        if(str->countHDD >=MAX_STORAGE) {
            break;
        }

        buffer[strcspn(buffer, "\n\r")] = '\0';

        if(strstr(buffer, "FriendlyName") != NULL) {
            continue;
        }

        if(strstr(buffer, "---") != NULL) {
            continue;
        }

        if(strlen(buffer) == 0) {
            continue;
        }

        strcpy(str->storHDD[str->countHDD].name, buffer);
        str->countHDD++;
    }

    pclose(fp);
    return 0;
}

int checkStorageHDD(systemInfo *str) {
    FILE *fp = popen(HDD_SIZE, "r");
    char buffer[64] = {0};
    str->countHDD = 0;

    if(fp == NULL) {
        return 1;
    }

    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        if(str->countHDD >= MAX_STORAGE) {
            break;
        }
        
        buffer[strcspn(buffer, "\n\r")] = '\0';

        if(strstr(buffer, "Size") != NULL) {
            continue;
        }

        if(strstr(buffer, "---") != NULL) {
            continue;
        }

        if(strlen(buffer) == 0) {
            continue;
        }

        unsigned long long byteSize = strtoull(buffer, NULL, 10);
        str->storHDD[str->countHDD].size = (float)byteSize / (1024 * 1024 * 1024);
        storageFilter(2, str);
        str->countHDD++;
    }

    pclose(fp);
    return 0;
}

int checkGPU(systemInfo *str) {
    FILE *fp = popen(GPU_NAME, "r");

    if(fp == NULL) {
        strcpy(str->gpuName, "Can't read");
        return 1;
    }

    while(fgets(str->gpuName, sizeof(str->gpuName), fp)) {
        str->gpuName[strcspn(str->gpuName, "\n\r")] = '\0';

        if(strstr(str->gpuName, "Name") != NULL) {
            continue;
        }

        if(strstr(str->gpuName, "---") != NULL) {
            continue;
        }

        if(strlen(str->gpuName) > 0) {
            break;
        }
    }

    pclose(fp);
    return 0;
}

void progressBar(const char *name, int current, int t) {
    const int width = 35;

    float progress = (float)current / t;
    int pos = progress * width;

    printf("\r%-18s [", name);

    for(int i = 0; i < width; i++) {
        printf(i < pos ? "█" : "*");
    }

    printf("] %3d%%", (int)(progress * 100));

    fflush(stdout);
}

void autoScan(systemInfo *str) {
    int timesTry = 0;
    const int scanLength = 7;

    progressBar("Initializing...", 0, scanLength);
    while(checkName(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
    }
    progressBar("Name", 1, scanLength);
    timesTry = 0;

    while(checkSN(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
    }
    progressBar("SN", 2, scanLength);
    timesTry = 0;

    while(checkCPU(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
    }
    progressBar("CPU", 3, scanLength);
    timesTry = 0;

    while(checkMemory(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
    }
    progressBar("Memory", 4, scanLength);
    timesTry = 0;
    
    while(checkNameSSD(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
    }
    progressBar("SSD Name", 5, scanLength);
    timesTry = 0;

    while(checkStorageSSD(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
    }
    progressBar("SSD Size", 5, scanLength);
    timesTry = 0;

    while(checkNameHDD(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
    }
    progressBar("HDD Name", 6, scanLength);
    timesTry = 0;

    while(checkStorageHDD(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
    }
    progressBar("HDD Size", 6, scanLength);
    timesTry = 0;

    while(checkGPU(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
    }
    progressBar("GPU", 7, scanLength);
    printf("\n");
}

void printStruct(systemInfo *str) {
    printf("========================================\n");
    printf("===== %s =====\n", str->name);
    printf("Name: %s\n", str->name);
    printf("SN: %s\n", str->SN);
    printf("CPU: %s\n", str->cpuName);
    printf("RAM: %.2f\n", str->memorySize);
    for(int i = 0; i < str->countSSD;i++) {
        printf("SSD[%d]: \n   Name: %s\n   Size: %.2f\n", i, str->storSSD[i].name, str->storSSD[i].size);
    }
    for(int i = 0; i < str->countHDD; i++) {
        printf("HDD[%d]: \n   Name: %s\n   Size: %.2f\n", i, str->storHDD[i].name, str->storHDD[i].size);
    }
    printf("GPU: %s\n", str->gpuName);
}