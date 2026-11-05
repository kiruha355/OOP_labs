#ifndef LAB_3_OOP_PHONE_OPS_H
#define LAB_3_OOP_PHONE_OPS_H

#include <cstddef>
#include <iosfwd>

class PhoneNumber {
private:
    char* digits_;

public:
    PhoneNumber();
    PhoneNumber(const char* text);
    PhoneNumber(const PhoneNumber& other);
    PhoneNumber(PhoneNumber&& other) noexcept;
    PhoneNumber& operator=(const PhoneNumber& other);
    PhoneNumber& operator=(PhoneNumber&& other) noexcept;
    ~PhoneNumber();

    void swap(PhoneNumber& other) noexcept;
    const char* c_str() const;
    bool operator==(const PhoneNumber& other) const;

    friend std::ostream& operator<<(std::ostream& out, const PhoneNumber& number);
};

class PhoneNumberSet {
private:
    PhoneNumber* data_;
    std::size_t size_;
    std::size_t capacity_;

    void reserve(std::size_t new_capacity);

public:
    PhoneNumberSet();
    PhoneNumberSet(const PhoneNumberSet& other);
    PhoneNumberSet(PhoneNumberSet&& other) noexcept;
    PhoneNumberSet& operator=(const PhoneNumberSet& other);
    PhoneNumberSet& operator=(PhoneNumberSet&& other) noexcept;
    ~PhoneNumberSet();

    void swap(PhoneNumberSet& other) noexcept;
    bool add(const PhoneNumber& number);
    bool remove(const PhoneNumber& number);
    bool contains(const PhoneNumber& number) const;
    bool operator()(const PhoneNumber& number) const;

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    PhoneNumberSet& operator+=(const PhoneNumber& number);
    PhoneNumberSet& operator-=(const PhoneNumber& number);
    PhoneNumberSet operator|(const PhoneNumberSet& other) const;
    PhoneNumberSet operator&(const PhoneNumberSet& other) const;
    PhoneNumberSet operator-(const PhoneNumberSet& other) const;
    bool operator==(const PhoneNumberSet& other) const;
    bool operator!=(const PhoneNumberSet& other) const;

    friend std::ostream& operator<<(std::ostream& out, const PhoneNumberSet& numbers);
};

#endif
