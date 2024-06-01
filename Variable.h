#pragma once
#include <iostream>
#include <string>
#include <variant>

#include "Interfaces.h"

class Variable : public Operand_Interface {
private:
    char m_data;

public:
    Variable()
        : m_data('\0') {}
    Variable(const std::string content)
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

    char operator() () const {
        return m_data;
    }
};
