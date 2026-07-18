#ifndef CHECK_H
#define CHECK_H

#define NAME_SIZE 50
#define SN_SIZE 30
#define CPU_SIZE 30
#define MEMORY_TAM 10
#define STORAGE_SIZE 10
#define GPU_SIZE 30

typedef struct{
    char name[NAME_SIZE];
    char SN[SN_SIZE];
    char cpuName[CPU_SIZE];
    char memorySize[MEMORY_TAM];
    char storageSize[STORAGE_SIZE];
    char gpuName[GPU_SIZE];
}systemInfo;

int checkName(systemInfo *str);

#endif