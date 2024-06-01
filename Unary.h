#pragma once
#include <iostream>
#include <string>
#include <variant>

#include "Interfaces.h"
#include "Constant.h"

class Unary : public Operator_Interface {
public:
    std::string m_data;
    static inline const short s_priority = 4;

    Unary() {}
    Unary(std::string content)
        : m_data(content) {}

    void printData() override {
        std::cout << m_data;
    }

    std::variant<char, double, std::string> getData() const {
        return m_data;
    }

    std::string getAsString() const {
        return m_data;
    }

    short priority() const override {
        return s_priority;
    }

    double operator()(const Constant& x) const {
        if (m_data == "sin") return sin(x());
        if (m_data == "cos") return cos(x());
        if (m_data == "tan") return tan(x());
        if (m_data == "cot") return 1.0 / tan(x());
        return double();
    }
};
