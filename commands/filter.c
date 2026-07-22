#include <stdio.h>
#include <string.h>

#include "filter.h"
#include "check.h"

const int ssdSize[] = {
    128,
    256,
    430,
    512,
    1000
};
const int numOfTypesSSD = sizeof(ssdSize) / sizeof(ssdSize[0]);

const int hddSize[] = {
    120,
    240,
    400,
    500,
    750,
    1000
};
const int numOfTypesHDD = sizeof(hddSize) / sizeof(hddSize[0]);

const int memorySize[] = {
    2,
    4,
    8,
    10,
    12,
    16,
    20,
    24,
    32,
    64
};
const int numOfTypesMemory = sizeof(memorySize) / sizeof(memorySize[0]);

int memoryFilter(systemInfo *str) {
    for(int i = 0; i < numOfTypesMemory; i++) {
        if(str->memorySize < memorySize[i]) {
            str->memorySize = memorySize[i];
            return 0;
        }
    }
    return 1;
}

int storageFilter(int storageType, systemInfo *str) {
    switch(storageType) {
        case 1:
        if(str->storSSD[str->countSSD].size == 0) {
            return -1;
        }
        for(int i = 0; i < numOfTypesSSD; i++) {
            if(str->storSSD[str->countSSD].size < ssdSize[i]) {
                str->storSSD[str->countSSD].size = ssdSize[i];
                return 0;
            }
        }
        return 1;

        case 2:
        if(str->storHDD[str->countHDD].size == 0) {
            return -1;
        }
        for(int i = 0; i < numOfTypesHDD; i++) {
            if(str->storHDD[str->countHDD].size < hddSize[i]) {
                str->storHDD[str->countHDD].size = hddSize[i];
                return 0;
            }
        }
        return 1;

        default:
        return -1;
}
}