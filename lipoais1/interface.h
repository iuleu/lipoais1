#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

void ShowGreeting();
void RunMenuLoop();
std::string ReadTextFromConsole();
std::string ReadTextFromFile(const std::string& filename);
std::string GetOutputFilePath();
void SaveResultToFile(const std::string& filename,
    const std::string& input_text,
    int max_length,
    int result);

#endif