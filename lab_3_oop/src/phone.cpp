#include "phone_ops.h"
#include <cstring>
#include <ostream>
#include <utility>

PhoneNumber::PhoneNumber() : digits_(nullptr) {
}

PhoneNumber::PhoneNumber(const char* text) : PhoneNumber() {
    if (text == nullptr) {
        return;
    }

    std::size_t count = 0;
    for (std::size_t i = 0; text[i] != '\0'; i++) {
        if (text[i] >= '0' && text[i] <= '9') {
            count++;
        }
    }

    digits_ = new char[count + 1];
    std::size_t pos = 0;
    for (std::size_t i = 0; text[i] != '\0'; i++) {
        if (text[i] >= '0' && text[i] <= '9') {
            digits_[pos] = text[i];
            pos++;
        }
    }
    digits_[pos] = '\0';
}

PhoneNumber::PhoneNumber(const PhoneNumber& other) : PhoneNumber(other.c_str()) {
}

PhoneNumber::PhoneNumber(PhoneNumber&& other) noexcept : digits_(other.digits_) {
    other.digits_ = nullptr;
}

PhoneNumber& PhoneNumber::operator=(const PhoneNumber& other) {
    if (this != &other) {
        PhoneNumber copy(other);
        swap(copy);
    }
    return *this;
}

PhoneNumber& PhoneNumber::operator=(PhoneNumber&& other) noexcept {
    if (this != &other) {
        delete[] digits_;
        digits_ = other.digits_;
        other.digits_ = nullptr;
    }
    return *this;
}

PhoneNumber::~PhoneNumber() {
    delete[] digits_;
}

void PhoneNumber::swap(PhoneNumber& other) noexcept {
    std::swap(digits_, other.digits_);
}

const char* PhoneNumber::c_str() const {
    return digits_ == nullptr ? "" : digits_;
}

bool PhoneNumber::operator==(const PhoneNumber& other) const {
    return std::strcmp(c_str(), other.c_str()) == 0;
}

std::ostream& operator<<(std::ostream& out, const PhoneNumber& number) {
    return out << number.c_str();
}

PhoneNumberSet::PhoneNumberSet() : data_(nullptr), size_(0), capacity_(0) {
}

PhoneNumberSet::PhoneNumberSet(const PhoneNumberSet& other) : PhoneNumberSet() {
    PhoneNumberSet copy;
    copy.reserve(other.capacity_);
    for (std::size_t i = 0; i < other.size_; i++) {
        copy.data_[i] = other.data_[i];
    }
    copy.size_ = other.size_;
    swap(copy);
}

PhoneNumberSet::PhoneNumberSet(PhoneNumberSet&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

PhoneNumberSet& PhoneNumberSet::operator=(const PhoneNumberSet& other) {
    if (this != &other) {
        PhoneNumberSet copy(other);
        swap(copy);
    }
    return *this;
}

PhoneNumberSet& PhoneNumberSet::operator=(PhoneNumberSet&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

PhoneNumberSet::~PhoneNumberSet() {
    delete[] data_;
}

void PhoneNumberSet::swap(PhoneNumberSet& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void PhoneNumberSet::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }

    PhoneNumberSet copy;
    copy.data_ = new PhoneNumber[new_capacity];
    copy.capacity_ = new_capacity;
    for (std::size_t i = 0; i < size_; i++) {
        copy.data_[i] = data_[i];
    }
    copy.size_ = size_;
    swap(copy);
}

bool PhoneNumberSet::add(const PhoneNumber& number) {
    if (contains(number)) {
        return false;
    }
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_] = number;
    size_++;
    return true;
}

bool PhoneNumberSet::remove(const PhoneNumber& number) {
    for (std::size_t i = 0; i < size_; i++) {
        if (data_[i] == number) {
            if (i != size_ - 1) {
                data_[i] = std::move(data_[size_ - 1]);
            }
            data_[size_ - 1] = PhoneNumber();
            size_--;
            return true;
        }
    }
    return false;
}

bool PhoneNumberSet::contains(const PhoneNumber& number) const {
    for (std::size_t i = 0; i < size_; i++) {
        if (data_[i] == number) {
            return true;
        }
    }
    return false;
}

bool PhoneNumberSet::operator()(const PhoneNumber& number) const {
    return contains(number);
}

std::size_t PhoneNumberSet::size() const {
    return size_;
}

std::size_t PhoneNumberSet::capacity() const {
    return capacity_;
}

bool PhoneNumberSet::empty() const {
    return size_ == 0;
}

PhoneNumberSet& PhoneNumberSet::operator+=(const PhoneNumber& number) {
    add(number);
    return *this;
}

PhoneNumberSet& PhoneNumberSet::operator-=(const PhoneNumber& number) {
    remove(number);
    return *this;
}

PhoneNumberSet PhoneNumberSet::operator|(const PhoneNumberSet& other) const {
    PhoneNumberSet result(*this);
    for (std::size_t i = 0; i < other.size_; i++) {
        result.add(other.data_[i]);
    }
    return result;
}

PhoneNumberSet PhoneNumberSet::operator&(const PhoneNumberSet& other) const {
    PhoneNumberSet result;
    for (std::size_t i = 0; i < size_; i++) {
        if (other.contains(data_[i])) {
            result.add(data_[i]);
        }
    }
    return result;
}

PhoneNumberSet PhoneNumberSet::operator-(const PhoneNumberSet& other) const {
    PhoneNumberSet result;
    for (std::size_t i = 0; i < size_; i++) {
        bool found = false;
        for (std::size_t j = 0; j < other.size_; j++) {
            if (data_[i] == other.data_[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            result.add(data_[i]);
        }
    }
    return result;
}

bool PhoneNumberSet::operator==(const PhoneNumberSet& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (std::size_t i = 0; i < size_; i++) {
        if (!other.contains(data_[i])) {
            return false;
        }
    }
    return true;
}

bool PhoneNumberSet::operator!=(const PhoneNumberSet& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PhoneNumberSet& numbers) {
    out << "{ ";
    for (std::size_t i = 0; i < numbers.size_; i++) {
        if (i != 0) {
            out << ", ";
        }
        out << numbers.data_[i];
    }
    return out << (numbers.empty() ? "}" : " }");
}
