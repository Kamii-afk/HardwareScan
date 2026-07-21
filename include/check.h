#ifndef CHECK_H
#define CHECK_H

#define NAME_SIZE 50
#define SN_SIZE 30
#define CPU_SIZE 50
#define GPU_SIZE 30
#define MAX_STORAGE 5

typedef struct{
    char name[NAME_SIZE];
    float size;
}storage;

typedef struct{
    char name[NAME_SIZE];
    char SN[SN_SIZE];
    char cpuName[CPU_SIZE];
    float memorySize;
    storage storSSD[MAX_STORAGE];
    int countSSD;
    storage storHDD[2];
    int countHDD;
    char gpuName[GPU_SIZE];
}systemInfo;

int checkName(systemInfo *str);
int checkSN(systemInfo *str);
int checkMemory(systemInfo *str);
int checkNameSSD(systemInfo *str);
int checkStorageSSD(systemInfo *str);
int checkNameHDD(systemInfo *str);
int checkStorageHDD(systemInfo *str);
int checkGPU(systemInfo *str);

void progressBar(const char *name, int current, int t);
void autoScan(systemInfo *str);
void printStruct(systemInfo *str);

#endif