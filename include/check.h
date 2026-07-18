#ifndef CHECK_H
#define CHECK_H

#define NAME_SIZE 50
#define SN_SIZE 30
#define CPU_SIZE 30
#define GPU_SIZE 30

typedef struct{
    char name[NAME_SIZE];
    char SN[SN_SIZE];
    char cpuName[CPU_SIZE];
    float memorySize;
    float storageSizeSSD;
    float storageSizeHDD;
    char gpuName[GPU_SIZE];
}systemInfo;

int checkName(systemInfo *str);
int checkSN(systemInfo *str);
int checkMemory(systemInfo *str);
int checkStorageSSD(systemInfo *str);
int checkStorageHDD(systemInfo *str);
int checkGPU(systemInfo *str);

void autoScan(systemInfo *str);

#endif