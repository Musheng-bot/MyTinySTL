//
// Created by meish on 25-6-4.
//
#include "String.h"

#include <cstring>

namespace sdf {
    void strcpy(char *dest, const char *src) {

        const char *p = src;
        while (*p != '\0') {
            *dest = *p;
            dest++;
            p++;
        }
        *dest = '\0';
    }

    void strncpy(char *dest, const char *src, size_t n) {
        const char *p = src;
        int i = 0;
        while (*p != '\0' && i < n) {
            *dest = *p;
            dest++;
            p++;
            ++i;
        }
        *dest = '\0';
    }

    CMPFlag strcmp(const char *s1, const char *s2) {
        for (; *s1 != '\0' && *s2 != '\0'; s1++, s2++) {
            if (*s1 < *s2) {
                return LESS;
            }
            if (*s1 > *s2) {
                return GREATER;
            }
        }
        if (*s1 == '\0' && *s2 == '\0') {
            return EQUAL;
        }
        if (*s2 == '\0') {
            return GREATER;
        }
        return LESS;
    }

    String::String() :
        data_(new char[1]),
        size_(0),
        capacity_(0)
    {
        *data_ = '\0';
    }

    String::String(const String &other) :
        data_(new char[other.capacity_ + 1]),
        size_(other.size_),
        capacity_(other.capacity_)
    {
        strncpy(data_, other.data_, other.size_);
    }

    String::String(const char *other) :
        data_(new char[std::strlen(other) + 1]),
        size_(static_cast<int>(strlen(other))),
        capacity_(size_)
    {
        strncpy(data_, other, size_);
    }

    String::String(String &&other) noexcept {
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    String & String::operator=(String &&other) noexcept {
        delete [] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        return *this;
    }

    String::~String() {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }

    String & String::operator=(const String &other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new char[other.capacity_ + 1];
        strncpy(data_, other.data_, size_);
        return *this;
    }

    String & String::operator=(const char *other) {
        delete[] data_;
        size_ = static_cast<int>(strlen(other));
        capacity_ = size_;
        data_ = new char[capacity_ + 1];
        strncpy(data_, other, size_);
        return *this;
    }

    bool String::operator==(const String &other) const {
        return strcmp(data_, other.data_) == EQUAL;
    }

    bool String::operator==(const char *other) const {
        return strcmp(data_, other) == EQUAL;
    }

    bool String::operator!=(const String &other) const {
        return strcmp(data_, other.data_) != EQUAL;
    }

    bool String::operator!=(const char *other) const {
        return strcmp(data_, other) != EQUAL;
    }

    bool String::operator<(const String &other) const {
        return strcmp(data_, other.data_) == LESS;
    }

    bool String::operator<(const char *other) const {
        return strcmp(data_, other) == LESS;
    }

    bool String::operator>(const String &other) const {
        return strcmp(data_, other.data_) == GREATER;
    }

    bool String::operator>(const char *other) const {
        return strcmp(data_, other) == GREATER;
    }

    bool String::operator<=(const String &other) const {
        return strcmp(data_, other.data_) != GREATER;
    }

    bool String::operator<=(const char *other) const {
        return strcmp(data_, other) != GREATER;
    }

    bool String::operator>=(const String &other) const {
        return strcmp(data_, other.data_) != LESS;
    }

    bool String::operator>=(const char *other) const {
        return strcmp(data_, other) != LESS;
    }

    String & String::operator+=(const String &other) {
        if (this->size_ + other.size_ > this->capacity_) {
            expand(2 * (size_ + other.size_));
        }
        strncpy(data_ + size_, other.data_, other.size_);
        size_ += other.size_;
        return *this;
    }

    String & String::operator+=(const char *other) {
        int len = static_cast<int>(strlen(other));
        if (this->size_ + len > this->capacity_) {
            expand(2 * (size_ + len));
        }
        strncpy(data_ + size_, other, len);
        size_ += len;
        return *this;
    }

    String & String::operator+=(const char other) {
        if (this->size_ + 1 > this->capacity_) {
            expand(2 * size_ + 1);
        }
        data_[size_] = other;
        data_[size_ + 1] = '\0';
        ++size_;
        return *this;
    }

    String String::operator+(const char *other) const {
        return String(*this) += other;
    }

    String String::operator+(char other) const {
        return String(*this) += other;
    }

    String String::operator+(const String &other) const {
        return String(*this) += other;
    }

    char & String::operator[](int index) {
        return data_[index];
    }

    const char * String::c_str() const {
        return data_;
    }

    const char & String::operator[](int index) const {
        return data_[index];
    }

    String String::substr(int start, int end) const {
        String result;
        if (start > end || end < 0) {
            return result;
        }
        if (end >= size_) {
            end = size_ - 1;
        }
        for (int i = start; i <= end; i++) {
            result += data_[i];
        }
        return result;
    }

    void String::replace(const char find, const char replace) {
        for (int i = 0; i < size_; i++) {
            if (data_[i] == find) {
                data_[i] = replace;
            }
        }
    }

    int String::find(const char find) const {
        for (int i = 0; i < size_; i++) {
            if (data_[i] == find) {
                return i;
            }
        }
        return npos;
    }

    int String::find(const String& find) const {
        for (int i = 0; i < size_; i++) {
            if (data_[i] == find.data_[0]) {
                int j = 1;
                for (; j < find.size_; j++) {
                    if (data_[i+j] != find.data_[j]) {
                        break;
                    }
                }
                if (j == find.size_) {
                    return i;
                }
            }
        }
        return npos;
    }

    bool String::isEmpty() const {
        return size_ == 0;
    }

    int String::size() const {
        return size_;
    }

    void String::toLower() {
        for (int i = 0; i < size_; i++) {
            if (data_[i] >= 'A' && data_[i] <= 'Z') {
                data_[i] -= 'A' - 'a';
            }
        }
    }
    void String::toUpper() {
        for (int i = 0; i < size_; i++) {
            if (data_[i] >= 'a' && data_[i] <= 'z') {
                data_[i] += 'A' - 'a';
            }
        }
    }

    void String::trim() {
        int i = 0, j = size_ - 1;
        for (; i < size_; i++) {
            if (data_[i] != ' ') {
                break;
            }
        }
        if (i == size_) {
            this->clear();
        }
        for (; j >= 0; j++) {
            if (data_[i] != ' ') {
                break;
            }
        }
        *this = this->substr(i, j);
    }

    void String::clear() {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
        data_ = new char[1];
        *data_ = '\0';
    }

    void String::concat(const String &other) {
        *this += other;
    }

    bool String::startsWith(const String &other) const {
        if (size_ < other.size_) {
            return false;
        }
        for (int i = 0; i < other.size_; i++) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    bool String::endsWith(const String &other) const {
        if (size_ < other.size_) {
            return false;
        }
        for (int i = 0; i < other.size_; i++) {
            if (data_[size_ - 1 - i] != other.data_[other.size_ - 1 - i]) {
                return false;
            }
        }
        return true;
    }

    String::Iterator String::begin() const {
        return Iterator(data_);
    }

    String::Iterator String::end() const {
        return Iterator(data_ + size_);
    }

    String::Iterator::Iterator(char *p) :
        val_(p)
    {
    }

    String::Iterator::Iterator(const Iterator &other) {
        val_ = other.val_;
    }

    String::Iterator & String::Iterator::operator++() {
        ++val_;
        return *this;
    }

    String::Iterator & String::Iterator::operator--() {
        --val_;
        return *this;
    }

    bool String::Iterator::operator==(const Iterator &other) const {
        return val_ == other.val_;
    }

    bool String::Iterator::operator!=(const Iterator &other) const {
        return val_ != other.val_;
    }

    char & String::Iterator::operator*() const {
        return *val_;
    }

    char * String::Iterator::operator->() const {
        return val_;
    }

    void String::expand(int new_capacity) {
        char *new_data = new char[new_capacity + 1];
        strncpy(new_data, data_, size_);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    std::ostream & operator<<(std::ostream &os, const String &str) {
        return os << str.data_;
    }

    std::istream & operator>>(std::istream &is, String &str) {
        String temp;
        char ch;
        while (is.get(ch)) {
            if (ch == '\0' || ch == '\n' || ch == '\r' || ch == '\t' || ch == ' ') {
                break;
            }
            temp += ch;
        }
        str = std::move(temp);
        return is;
    }
}
