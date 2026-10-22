#include <iostream>
#include <limits>
#include <clocale>
#include "string_ops.h"

String read_string() {
    String text;
    char c;
    while (std::cin.get(c) && c != '\n') {
        text.push_back(c);
    }
    return text;
}

int main() {
    setlocale(LC_ALL, ".UTF-8");
    String text;
    int choice;

    while (true) {
        std::cout << "\n1. Ввести строку\n";
        std::cout << "2. Напечатать строку\n";
        std::cout << "3. Добавить символ\n";
        std::cout << "4. Добавить строку\n";
        std::cout << "5. Найти подстроку\n";
        std::cout << "6. Перенос по словам\n";
        std::cout << "7. Размер и емкость\n";
        std::cout << "8. Очистить строку\n";
        std::cout << "0. Выход\nВыберите пункт: ";

        if (!(std::cin >> choice)) {
            return 0;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::cout << "Введите строку: ";
                text = read_string();
                break;
            }
            case 2: {
                text.print(std::cout);
                std::cout << '\n';
                break;
            }
            case 3: {
                char c;
                std::cout << "Введите символ: ";
                std::cin.get(c);
                text.push_back(c);
                break;
            }
            case 4: {
                std::cout << "Введите добавляемую строку: ";
                text.append(read_string());
                break;
            }
            case 5: {
                std::cout << "Введите подстроку: ";
                std::size_t pos = text.find(read_string());
                if (pos == String::npos) {
                    std::cout << "Подстрока не найдена\n";
                } else {
                    std::cout << "Позиция: " << pos << '\n';
                }
                break;
            }
            case 6: {
                int width;
                std::cout << "Введите ширину строки: ";
                if (!(std::cin >> width)) {
                    return 0;
                }
                if (width <= 0) {
                    std::cout << "Ширина должна быть положительной\n";
                    break;
                }
                text.wrap(width).print(std::cout);
                std::cout << '\n';
                break;
            }
            case 7: {
                std::cout << "Размер: " << text.size() << '\n';
                std::cout << "Емкость: " << text.capacity() << '\n';
                break;
            }
            case 8: {
                text.clear();
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                std::cout << "Нет такого пункта меню\n";
                break;
            }
        }
    }
}
