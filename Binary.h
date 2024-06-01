#pragma once
#include <iostream>
#include <string>
#include <variant>
#include <cmath>

#include "Interfaces.h"
#include "Constant.h"

class Binary : public Operator_Interface {
private:
    char m_data;
    short m_priority;

private:
    void setPriority() {
        switch (m_data)
        {
        case '+':
            m_priority = 1;
            break;
        case '-':
            m_priority = 1;
            break;
        case '*':
            m_priority = 2;
            break;
        case '/':
            m_priority = 2;
            break;
        case '^':
            m_priority = 3;
            break;
        default:
            break;
        }
    }
public:

    Binary()
        : m_data('\0'), m_priority(short()) {}
    Binary(std::string content)
        : m_data(content.front()) {
        setPriority();
    }

    void printData() override {
        std::cout << m_data;
    }

    std::variant<char, double, std::string> getData() const {
        return m_data;
    }

    std::string getAsString() const {
        return std::string(1, m_data);
    }

    short priority() const override{
        return m_priority;
    }

    double operator()(const Constant& x, const Constant& y) const {
        switch (m_data) {
        case '+': return x() + y();
        case '-': return x() - y();
        case '*': return x() * y();
        case '/': return x() / y();
        default: return std::pow(x(), y());
        }
    }
};