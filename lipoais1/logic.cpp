#include "logic.h"
#include <sstream>
#include <cctype>

std::vector<std::string> SplitIntoWords(const std::string& text) {
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
        // Удаление знаков препинания
        word.erase(
            std::remove_if(word.begin(), word.end(),
                [](unsigned char c) { return std::ispunct(c); }),
            word.end()
        );
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    return words;
}

int CountShortWords(const std::string& text, int max_length) {
    const std::vector<std::string> words = SplitIntoWords(text);
    int count = 0;
    for (const auto& word : words) {
        if (static_cast<int>(word.length()) < max_length + 1) {
            ++count;
        }
    }
    return count;
}