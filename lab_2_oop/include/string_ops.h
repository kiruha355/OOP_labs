#pragma once
#include <cstddef>
#include <iosfwd>

class String {
private:
    char* data_;
    std::size_t size_;
    std::size_t capacity_;

public:
    String();
    String(const char* text);
    String(const String& other);
    String(String&& other) noexcept;
    String& operator=(String other);
    ~String();

    void swap(String& other) noexcept;
    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;
    const char* c_str() const;
    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;
    void clear();
    void push_back(char c);
    void append(const String& other);
    std::size_t find(const String& substr) const;
    void print(std::ostream& out) const;
    String wrap(std::size_t width) const;

    static constexpr std::size_t npos = static_cast<std::size_t>(-1);
};
