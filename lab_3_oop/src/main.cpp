#include <clocale>
#include <iostream>
#include <limits>
#include "phone_ops.h"

void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool read_phone_number(PhoneNumber& number) {
    char text[256];
    std::cout << "Введите телефон: ";
    if (!std::cin.getline(text, sizeof(text))) {
        if (!std::cin.eof()) {
            clear_input();
            std::cout << "Неккоректный номер\n";
        }
        return false;
    }

    number = PhoneNumber(text);
    return true;
}

int main() {
    setlocale(LC_ALL, ".UTF-8");
    PhoneNumberSet first;
    PhoneNumberSet second;
    bool use_first = true;

    while (true) {
        PhoneNumberSet& active = use_first ? first : second;
        std::cout << "\nТекущее множество: " << (use_first ? "A" : "B") << '\n';
        std::cout << "1. Переключить множество A / B\n";
        std::cout << "2. Добавить телефон\n";
        std::cout << "3. Удалить телефон\n";
        std::cout << "4. Проверить наличие телефона\n";
        std::cout << "5. Напечатать множества\n";
        std::cout << "6. Операции над множествами\n";
        std::cout << "0. Выход\nВыберите пункт: ";

        int choice;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                return 0;
            }
            clear_input();
            std::cout << "Ошибка ввода\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                use_first = !use_first;
                break;
            }
            case 2: {
                PhoneNumber number;
                if (read_phone_number(number)) {
                    std::cout << (active.add(number)
                        ? "Телефон добавлен\n" : "Такой телефон уже есть\n");
                }
                break;
            }
            case 3: {
                PhoneNumber number;
                if (read_phone_number(number)) {
                    std::cout << (active.remove(number)
                        ? "Телефон удален\n" : "Телефон не найден\n");
                }
                break;
            }
            case 4: {
                PhoneNumber number;
                if (read_phone_number(number)) {
                    std::cout << (active(number)
                        ? "Телефон есть в множестве\n" : "Телефон не найден\n");
                }
                break;
            }
            case 5: {
                std::cout << "A = " << first << '\n';
                std::cout << "B = " << second << '\n';
                std::cout << "Размер A: " << first.size() << '\n';
                std::cout << "Размер B: " << second.size() << '\n';
                break;
            }
            case 6: {
                std::cout << "A | B = " << (first | second) << '\n';
                std::cout << "A & B = " << (first & second) << '\n';
                std::cout << "A - B = " << (first - second) << '\n';
                std::cout << "B - A = " << (second - first) << '\n';
                std::cout << (first == second
                    ? "Множества равны\n" : "Множества не равны\n");
                break;
            }
            case 0: {
                return 0;
            }
        }
    }
}
