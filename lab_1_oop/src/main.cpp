#include <iostream>
#include <limits>
#include <clocale>
#include "array_ops.h"

int main() {

    setlocale(LC_ALL, ".UTF-8");
    
    int* arr = nullptr;
    std::size_t size = 0;
    int i;

    while (true) {
        std::cout << "1. Создать массив\n";
        std::cout << "2. Напечатать\n";
        std::cout << "3. Вставить элемент\n";
        std::cout << "4. Удалить элемент\n";
        std::cout << "5. Изменить размер\n";
        std::cout << "6. Поиск k элемента\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите пункт: ";
        
        if (!(std::cin >> i)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //стримайз это размер потока ,лимитс для макс возможного числа 
            continue;
        };
        std::cout << "\n"; 

        switch (i) {
            case 1: {
                int new_size = 0;
                std::cout << "Введите размер массива: ";

                if (!(std::cin >> new_size) || new_size < 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка\n";
                    break;
                }

                int* new_arr = array_create(new_size);
                bool input_ok = true;

                for (int index = 0; index < new_size; index++) {
                    std::cout << "Введите значение элемента [" << index << "]: ";

                    if (!(std::cin >> new_arr[index])) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Ошибка\n";
                        input_ok = false;
                        break;
                    }
                }

                if (!input_ok) {
                    array_delete(new_arr);
                    break;
                }

                array_delete(arr);
                arr = new_arr;
                size = new_size;
                break;
            }
            case 2: {
                array_print(arr, size);
                break;
            }
            case 3: {
                std::size_t pos=0;
                int value;

                std::cout << "Введите позицию для добавления в массив: ";
                if (!(std::cin >> pos) || pos > size) {
                    std::cout << "Ошибка\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                std::cout << "Введите значение элемента: ";
                if (!(std::cin >> value)) {
                    std::cout << "Ошибка\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                arr = array_insert(arr, size, pos, value);
                std::cout << "Элемент добавлен\n";
                break;
            }
            case 4: {
                std::size_t pos = 0;
                std::cout << "Введите позицию для удаления: ";
                if (!(std::cin >> pos) || pos >= size) {
                    std::cout << "Ошибка\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                arr = array_remove(arr, size, pos);
                std::cout << "Элемент удален\n";
                break;
            }
            case 5:{
                int new_size = 0;
                std::cout << "Введите новый размер: ";
                if (!(std::cin >> new_size) || new_size < 0) {
                    std::cout << "Ошибка\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                arr = array_resize(arr, size, new_size);
                size = new_size;
                std::cout << "Размер массива изменен\n";
                break;
            }
            case 6: {
                std::size_t k = 0;
                std::cout << "Введите k: ";

                if (!(std::cin >> k)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка\n";
                    break;
                }

                if (arr == nullptr || size == 0 || k == 0 || k > size) {
                    std::cout << "Некорректное k или массив пуст\n";
                    break;
                }

                int result = array_kth_smallest(arr, size, k);
                std::cout << "Ответ: " << result << '\n';
                break;
            }
            case 0: {
                array_delete(arr);
                return 0;
                break;
            }
            default: {
                std::cout << "Нет такого пункта меню\n";
                break;
            }
        }
    }
    return 0;
}
