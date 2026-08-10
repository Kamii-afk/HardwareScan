#ifndef CUSTOM_H
#define CUSTOM_H

#define TRUE 1
#define FALSE 0

typedef enum {
    EXCLUDE_USB,
    EXCLUDE_SSD,
    EXCLUDE_HDD
}excludeOptions;

typedef struct {
    int includeExtern;
    int excludeSel[3];
}userCustom;

extern const userCustom defSettings;

char cursorCheck(excludeOptions option);
void listSettings(userCustom *settings);
void useDefault(userCustom *settings);
int checkCustom(userCustom *settings);
int configCustom(userCustom *settings);

#endif