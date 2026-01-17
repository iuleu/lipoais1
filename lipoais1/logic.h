#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <vector>

int CountShortWords(const std::string& text, int max_length);
std::vector<std::string> SplitIntoWords(const std::string& text);

#endif