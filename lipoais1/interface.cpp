#include "interface.h"
#include "logic.h"
#include "tests.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>

// Проверка на существование файла
bool FileExists(const std::string& path) {
    std::ifstream f(path);
    return f.good();
}

// Попытка открыть файл на запись - если не получается, считаем его "только для чтения"
bool IsWritable(const std::string& path) {
    std::ofstream f(path, std::ios::app);
    bool ok = f.is_open();
    if (ok) f.close();
    return ok;
}

// Надёжный ввод y/n
char GetYesNoChoice(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера

        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') {
            return choice;
        }
        std::cout << "Пожалуйста, введите 'y' или 'n'.\n";
    }
}

// Проверка на txt-формат
bool HasTxtExtension(const std::string& filename) {
    if (filename.length() < 4) {
        return false;
    }

    std::string ext = filename.substr(filename.length() - 4);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == ".txt";
}

// Получение пути для сохранения результата
std::string GetOutputFilePath() {
    std::string path;
    while (true) {
        std::cout << "Введите путь к файлу для сохранения результата: ";
        std::getline(std::cin, path);
        if (path.empty()) {
            std::cout << "Путь не может быть пустым.\n";
            continue;
        }

        if (!HasTxtExtension(path)) {
            std::cout << "Файл должен иметь расширение .txt. Попробуйте снова.\n";
            continue;
        }

        if (FileExists(path)) {
            if (!IsWritable(path)) {
                std::cout << "Невозможно записать в файл. Укажите другой путь.\n";
                continue;
            }

            char choice = GetYesNoChoice("Файл уже существует. Перезаписать? (y/n): ");
            if (choice == 'y' || choice == 'Y') {
                return path;
            }
        }
        else {
            // Файл не существует — проверяем, можем ли создать его
            std::ofstream test(path);
            if (test.is_open()) {
                test.close();
                std::remove(path.c_str());
                return path;
            }
            else {
                std::cout << "Невозможно создать файл по указанному пути. Проверьте права и путь.\n";
                continue;
            }
        }
    }
}

int GetMaxLen() {
    int max_len;
    while (true) {
        std::cout << "Введите максимальную длину слова: ";
        if (std::cin >> max_len) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера
            return max_len;
        }
        else {
            std::cin.clear(); // сброс ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка
            std::cout << "Некорректный ввод. Пожалуйста, введите число.\n";
        }
    }
}

void ShowGreeting() {
    std::cout << "===============================================\n";
    std::cout << "Ивлев Максим Романович, группа 425\n";
    std::cout << "Вариант №6: Подсчитать количество слов длиной меньше заданного числа.\n";
    std::cout << "===============================================\n";
}

std::string ReadTextFromConsole() {
    std::cout << "Введите текст (одна строка):\n";
    std::string text;
    std::getline(std::cin, text);
    return text;
}

std::string ReadTextFromFile(const std::string& filename) {
    if (!HasTxtExtension(filename)) {
        throw std::runtime_error("Файл должен иметь расширение .txt: " + filename);
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
    }
    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    return content;
}

void SaveResultToFile(const std::string& filename,
    const std::string& input_text,
    int max_length,
    int result) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }
    file << "Исходный текст:\n" << input_text << "\n";
    file << "Максимальная длина слова: " << max_length << "\n";
    file << "Количество слов короче заданной длины: " << result << "\n";
    file.close();
}

void RunMenuLoop() {
    int choice;
    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Ввести текст с клавиатуры\n";
        std::cout << "2. Загрузить текст из файла\n";
        std::cout << "3. Запустить модульные тесты\n";
        std::cout << "4. Выйти\n";
        std::cout << "Выберите действие: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Попробуйте снова.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            std::string text = ReadTextFromConsole();
            int max_len = GetMaxLen();
            int result = CountShortWords(text, max_len);
            std::cout << "Результат: " << result << " слов(а)\n";

            char save = GetYesNoChoice("Сохранить результат в файл? (y/n): ");
            if (save == 'y' || save == 'Y') {
                std::string path = GetOutputFilePath();
                SaveResultToFile(path, text, max_len, result);
                std::cout << "Результат сохранён в файл: " << path << "\n";
            }
            break;
        }
        case 2: {
            std::string filename;
            std::cout << "Введите путь к файлу с текстом: ";
            std::getline(std::cin, filename);
            try {
                std::string text = ReadTextFromFile(filename);
                int max_len = GetMaxLen();
                int result = CountShortWords(text, max_len);
                std::cout << "Результат: " << result << " слов(а)\n";

                char save = GetYesNoChoice("Сохранить результат в файл? (y/n): ");
                if (save == 'y' || save == 'Y') {
                    std::string path = GetOutputFilePath();
                    SaveResultToFile(path, text, max_len, result);
                    std::cout << "Результат сохранён в файл: " << path << "\n";
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Ошибка: " << e.what() << "\n";
            }
            break;
        }
        case 3: {
            if (RunAllTests()) {
                std::cout << "Тестирование прошло успешно.\n";
            }
            break;
        }
        case 4:
            std::cout << "Завершение работы.\n";
            return;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}