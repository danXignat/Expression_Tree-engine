#pragma once

#include "Interfaces.h"

class Pharanthesis : public Element_Interface {
private:
    char m_data;
    static inline const short s_priority = 0;

public:
    Pharanthesis()
        : m_data('\0') {}
    Pharanthesis(const std::string content)
        : m_data(content.front()) {}

    void printData() override {
        std::cout << m_data;
    }

    std::string getAsString() const {
        return std::string(1, m_data);
    }

    std::variant<char, double, std::string> getData() const {
        return m_data;
    }

    short priority() const {
        return s_priority;
    }

    bool isLeftBracket() const {
        return (m_data == '(' || m_data == '[' || m_data == '{');
    }

    bool isRightBracket() const {
        return (m_data == ')' || m_data == ']' || m_data == '}');
    }

    char operator() () const {
        return m_data;
    }

};
