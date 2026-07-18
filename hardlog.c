#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#include "shellCommand.h"
#include "check.h"

int main() {
    systemInfo str;

    checkName(&str);
    printf("Nome: %s", str.name);

    system("pause");
    return 0;
}