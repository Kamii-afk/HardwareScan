#ifndef FILTER_H
#define FILTER_H

#include "check.h"

extern const int memorySize[];
extern const int numOfTypesMemory;
extern const int ssdSize[];
extern const int numOfTypesSSD;
extern const int hddSize[];
extern const int numOfTypesHDD;

int memoryFilter(systemInfo *str);
int storageFilter(int storageType, systemInfo *str);

#endif