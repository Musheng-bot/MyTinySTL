//
// Created by meish on 25-5-27.
//

#ifndef STRING_H
#define STRING_H

#include <iostream>

namespace sdf {
    void strcpy(char *dest, const char *src);
    void strncpy(char *dest, const char *src, size_t n);
    enum CMPFlag {
        EQUAL = 0, LESS = -1, GREATER = 1
    };
    CMPFlag strcmp(const char *s1, const char *s2);

    class String {
        public:
            class Iterator;
            static constexpr int npos = -1;

            String();
            ~String();
            String(const String& other);
            String(const char* other);
            String(String&& other) noexcept;
            String& operator = (String&& other) noexcept;
            String& operator=(const String& other);
            String& operator=(const char* other);
            bool operator==(const String& other) const;
            bool operator==(const char* other) const;
            bool operator!=(const String& other) const;
            bool operator!=(const char* other) const;
            bool operator<(const String& other) const;
            bool operator<(const char* other) const;
            bool operator>(const String& other) const;
            bool operator>(const char* other) const;
            bool operator<=(const String& other) const;
            bool operator<=(const char* other) const;
            bool operator>=(const String& other) const;
            bool operator>=(const char* other) const;
            String& operator+=(const String& other);
            String& operator+=(const char* other);
            String& operator+=(char other);
            String operator+(const char* other) const;
            String operator+(char other) const;
            String operator+(const String& other) const;

            char &operator[](int index);
            const char* c_str() const;
            const char& operator[](int index) const;
            friend std::ostream &operator<<(std::ostream &os, const String &str);
            friend std::istream &operator>>(std::istream &is, String &str);

            String substr(int start, int end) const;
            void replace(char find, char replace);
            int find(char find) const;
            int find(const String& find) const;
            [[nodiscard]] bool isEmpty() const;
            [[nodiscard]] int size() const;
            void toLower();
            void toUpper();
            void trim();
            void clear();
            void concat(const String& other);
            bool startsWith(const String& other) const;
            bool endsWith(const String& other) const;

            Iterator begin() const;
            Iterator end() const;

            class Iterator {
                public:
                    explicit Iterator(char *p);
                    Iterator(const Iterator& other);
                    Iterator& operator++();
                    Iterator& operator--();
                    bool operator==(const Iterator& other) const;
                    bool operator!=(const Iterator& other) const;
                    char &operator*() const;
                    char *operator->() const;

                private:
                    char *val_;
            };


        private:
            char* data_;
            int size_;
            int capacity_;

            void expand(int new_capacity);

    };

} // sdf

#endif //STRING_H
