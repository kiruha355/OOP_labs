#include <iostream>
#include <algorithm>
#include "array_ops.h"


int* array_create(std::size_t size){
    if (size == 0) {
    return nullptr;
    }
    int* arr = new int[size];
    return arr;
}

void array_print(const int* arr, std::size_t size){
    if (arr == nullptr || size == 0) {
        std::cout << "Массив пуст\n";
        return;
    }
    for (std::size_t siz=0;siz<size;siz++){
        std::cout<<arr[siz]<<" ";
    }
    std::cout << "\n";
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value) {
    if ((arr == nullptr && size != 0) || pos > size) {
        return arr;
    }
    int* new_arr = new int[size+1];
    for (std::size_t i = 0; i < pos; i++) {
        new_arr[i] = arr[i];
    }
    new_arr[pos] = value;
    for (std::size_t j = pos; j < size; j++) {
        new_arr[j + 1] = arr[j];
    }

    delete[] arr;
    arr=nullptr;
    size++;

    return new_arr;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos){
    if (arr == nullptr || size == 0 || pos >= size) {
        return arr;
    }
    if (size == 1) {
        delete[] arr;
        size = 0;
        return nullptr;
    }
    int* new_arr = new int[size-1];
    for (std::size_t i=0;i<pos;i++){
        new_arr[i]=arr[i];
    }
    for (std::size_t i=pos+1; i< size; i++) {
    new_arr[i - 1] = arr[i];
}
    delete[] arr;
    arr=nullptr;
    size--;
    return new_arr;
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size) {
    if (arr == nullptr && size != 0) {
        return arr;
    }

    if (size == new_size) {
        return arr;
    }

    if (new_size == 0) {
        delete[] arr;
        return nullptr;
    }
    int* new_arr = new int[new_size]();

    if (arr != nullptr) {
        std::size_t neww = std::min(size, new_size);
        for (std::size_t i = 0; i < neww; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr=nullptr;
    }

    return new_arr;
}

void array_delete(int*& arr){
    delete[] arr;
    arr=nullptr;
}


int partition(int* arr, int left, int right) {
    int pivot = arr[left + (right - left) / 2];
    int i = left;
    int j = right;

    while (true) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i >= j) {
            return j;
        }

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;

        i++;
        j--;
    }
}

void quick_sort_range(int* arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int j = partition(arr, left, right);

    quick_sort_range(arr, left, j);
    quick_sort_range(arr, j + 1, right);
}

void quick_sort(int* arr, std::size_t size) {
    if (arr == nullptr || size < 2) {
        return;
    }

    int right = size - 1;
    quick_sort_range(arr, 0, right);
}



int array_kth_smallest(int* arr, std::size_t size, std::size_t k){
    if (arr == nullptr || size == 0 || k == 0 || k > size) {
        return 0;
    }

    int* sorted_arr = new int[size];
    for (std::size_t i = 0; i < size; ++i) {
        sorted_arr[i] = arr[i];
    }

    quick_sort(sorted_arr, size);

    int result = sorted_arr[k - 1];
    delete[] sorted_arr;
    return result;
}

