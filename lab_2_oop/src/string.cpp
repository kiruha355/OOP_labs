#include "string_ops.h"
#include <ostream>
#include <utility>

String::String() : data_(new char[2]{'\0'}), size_(0), capacity_(1) {
}

String::String(const char* text) : String() {
    for (std::size_t i = 0; text[i] != '\0'; i++) {
        push_back(text[i]);
    }
}

String::String(const String& other) : String(other.c_str()) {
}

String::String(String&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

String& String::operator=(String other) {
    swap(other);
    return *this;
}

String::~String() {
    delete[] data_;
}

void String::swap(String& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

std::size_t String::size() const {
    return size_;
}

std::size_t String::capacity() const {
    return capacity_;
}

bool String::empty() const {
    return size_ == 0;
}

const char* String::c_str() const {
    return data_ == nullptr ? "" : data_;
}

char& String::operator[](std::size_t pos) {
    return data_[pos];
}

const char& String::operator[](std::size_t pos) const {
    return data_[pos];
}

void String::clear() {
    size_ = 0;
    if (data_ != nullptr) {
        data_[0] = '\0';
    }
}

void String::push_back(char c) {
    if (size_ == capacity_) {
        std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        char* new_data = new char[new_capacity + 1];
        for (std::size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
    data_[size_] = c;
    size_++;
    data_[size_] = '\0';
}

void String::append(const String& other) {
    std::size_t length = other.size_;
    for (std::size_t i = 0; i < length; i++) {
        push_back(other[i]);
    }
}

std::size_t String::find(const String& substr) const {
    if (substr.size_ > size_) {
        return npos;
    }
    for (std::size_t i = 0; i <= size_ - substr.size_; i++) {
        std::size_t j = 0;
        while (j < substr.size_ && data_[i + j] == substr[j]) {
            j++;
        }
        if (j == substr.size_) {
            return i;
        }
    }
    return npos;
}

void String::print(std::ostream& out) const {
    out << c_str();
}

String String::wrap(std::size_t width) const {
    String result;
    std::size_t line_size = 0;
    std::size_t i = 0;

    while (i < size_) {
        if (data_[i] == '\n') {
            result.push_back('\n');
            line_size = 0;
            i++;
        } else if (data_[i] == ' ' || data_[i] == '\t' || data_[i] == '\r') {
            i++;
        } else {
            std::size_t start = i;
            while (i < size_ && data_[i] != ' ' && data_[i] != '\t'
                && data_[i] != '\r' && data_[i] != '\n') {
                i++;
            }
            std::size_t word_size = i - start;
            if (line_size != 0) {
                if (line_size + 1 + word_size > width) {
                    result.push_back('\n');
                    line_size = 0;
                } else {
                    result.push_back(' ');
                    line_size++;
                }
            }
            for (std::size_t j = start; j < i; j++) {
                result.push_back(data_[j]);
            }
            line_size += word_size;
        }
    }
    return result;
}
