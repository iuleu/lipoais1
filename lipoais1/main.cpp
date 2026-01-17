#include "interface.h"
#include <iostream>
#include <locale>

int main() {
    setlocale(LC_ALL, "");
    ShowGreeting();
    RunMenuLoop();
    return 0;
}