#pragma once
#include <iostream>
#include <string>
#include <variant>

#include "Interfaces.h"

class Constant : public Operand_Interface {
public:
    double m_data;

    Constant()
        : m_data(double()) {}
    Constant(std::string content)
        : m_data(std::stod(content)) {}

    void printData() override {
        std::cout << m_data;
    }

    std::string getAsString() const {
        return std::to_string(m_data);
    }

    std::variant<char, double, std::string> getData() const {
        return m_data;
    }

    double operator()() const {
        return m_data;
    }
};