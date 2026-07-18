#include "shellCommand.h"
#include "check.h"

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

    return 0;
}

int checkStorageSSD(systemInfo *str) {
    FILE *fp = popen(SSD_SIZE, "r");
    char buffer[64] = {0};

    if(fp == NULL) {
        return 1;
    }

    while(fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n\r")] = '\0';

        if(strstr(buffer, "Size") != NULL) {
            continue;
        }

        if(strstr(buffer, "---") != NULL) {
            continue;
        }

        if(strlen(buffer) > 0) {
            break;
        }
    }

    unsigned long long bytesSize = strtoull(buffer, NULL, 10);
    str->storageSizeSSD = (float)bytesSize / (1024 * 1024 * 1024);

    pclose(fp);
    return 0;
}

int checkStorageHDD(systemInfo *str) {
    FILE *fp = popen(HDD_SIZE, "r");
    char buffer[64] = {0};

    if(fp == NULL) {
        return 1;
    }

    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\n\r")] = '\0';

        if(strstr(buffer, "Size") != NULL) {
            continue;
        }

        if(strstr(buffer, "---") != NULL) {
            continue;
        }

        if(strlen(buffer) > 0) {
            break;
        }
    }

    unsigned long long byteSize = strtoull(buffer, NULL, 10);
    str->storageSizeHDD = (float)byteSize / (1024 * 1024 * 1024);

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

void autoScan(systemInfo *str) {
    int timesTry = 0;

    while(checkName(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
        checkName(str);
    }
    timesTry = 0;
    while(checkSN(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
        checkSN(str);
    }
    timesTry = 0;
    while(checkMemory(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
        checkMemory(str);
    }
    timesTry = 0;
    while(checkStorageSSD(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
        checkStorageSSD(str);
    }
    timesTry = 0;
    while(checkStorageHDD(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
        checkStorageHDD(str);
    }
    timesTry = 0;
    while(checkGPU(str) != 0 && timesTry < 3) {
        timesTry++;
        Sleep(200);
        checkGPU(str);
    }
}