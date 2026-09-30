#pragma once
#include <cstddef>

int* array_create(std::size_t size); 
void array_print(const int* arr, std::size_t size);
int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value); 
int* array_remove(int* arr, std::size_t& size, std::size_t pos); 
int* array_resize(int* arr, std::size_t size, std::size_t new_size); 
void array_delete(int*& arr); 

int array_kth_smallest(int* arr, std::size_t size, std::size_t k);
