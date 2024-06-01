#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <variant>
#include <sstream>
#include <fstream>

#include "Interfaces.h"
#include "Constant.h"
#include "Variable.h"
#include "Unary.h"
#include "Binary.h"
#include "Pharanthesis.h"

class Element {
private:
    Element_Interface* m_data;

public:
    static const std::unordered_set<std::string> s_unaries;
    static const std::unordered_set<std::string> s_binaries;
    static const std::unordered_set<std::string> s_pharanthesis;

private:
    bool isDouble(const std::string& str) const {
        std::istringstream iss(str);
        double value;
        iss >> std::noskipws >> value;
        return iss.eof() && !iss.fail();
    }
    bool isUnaryOperator(const std::string& str) const {
        return s_unaries.contains(str);
    }
    bool isBinaryOperator(const std::string& str) const {
        return s_binaries.contains(str);
    }
    bool isPharanthesis(const std::string& str) const {
        return s_pharanthesis.contains(str);
    }

    Element_Interface* factory(const std::string& expression) {
        if (isDouble(expression)        ) return new Constant(expression);
        if (isBinaryOperator(expression)) return new Binary(expression);
        if (isUnaryOperator(expression) ) return new Unary(expression);
        if (isPharanthesis(expression)  ) return new Pharanthesis(expression);
                                          return new Variable(expression);
    }
    Element_Interface* factory(const Element& other) {
        if (other.isUnary())
            return new Unary(other.getAsString());
        if (other.isBinary())
            return new Binary(other.getAsString());
        if (other.isConstant())
            return new Constant(other.getAsString());
        if (other.isVariable())
            return new Variable(other.getAsString());

        return new Pharanthesis(other.getAsString());
    }
public:
    //Constructor, rule of three
    Element()
        :   m_data(nullptr) {}

    Element(const std::string& expr)
        :   m_data(factory(expr)) {}

    Element(Element_Interface* el_ptr) 
        :   m_data(el_ptr) {}

    Element(const Element& other) 
        : m_data(factory(other)) {}

    ~Element() { delete m_data; }

    Element& operator=(const Element& other) {
        delete m_data;

        m_data = factory(other);

        return *this;
    }

    //Getters
    void print() {
        m_data->printData();
    }
    std::variant<char, double, std::string> getData() const {
        return m_data->getData();
    }
    std::string getAsString() const {
        return m_data->getAsString();
    }
    short priority() const {
        if (this->isOperator())
            return dynamic_cast<Operator_Interface*>(m_data)->priority();
        if (this->isPharanthesis())
            return dynamic_cast<Pharanthesis*>(m_data)->priority();

        throw std::runtime_error("Not operator nor parathesis");
    }

    //checkers
    bool isOperator() const {
        if (dynamic_cast<Operator_Interface*>(m_data))
            return true;
        return false;
    }
    bool isUnary() const {
        if (dynamic_cast<Unary*>(m_data))
            return true;
        return false;
    }
    bool isBinary() const {
        if (dynamic_cast<Binary*>(m_data))
            return true;
        return false;
    }

    bool isOperand() const {
        if (dynamic_cast<Operand_Interface*>(m_data))
            return true;
        return false;
    }
    bool isConstant() const {
        if (dynamic_cast<Constant*>(m_data))
            return true;
        return false;
    }
    bool isVariable() const {
        if (dynamic_cast<Variable*>(m_data))
            return true;
        return false;
    }

    bool isPharanthesis() const {
        if (dynamic_cast<Pharanthesis*>(m_data))
            return true;
        return false;
    }
    bool isLeftBracket() const {
        Pharanthesis* ph = dynamic_cast<Pharanthesis*>(m_data);

        return ph ? ph->isLeftBracket() : false;
    }
    bool isRightbracket() const {
        Pharanthesis* ph = dynamic_cast<Pharanthesis*>(m_data);

        return ph ? ph->isRightBracket() : false;
    }

    // Overloads
    double operator()() const {
        return (*dynamic_cast<Constant*>(m_data)) ();
    }
    double operator()(const Element& first) const {
        auto firstEl = *dynamic_cast<Constant*>(first.m_data);

        return (*dynamic_cast<Unary*>(m_data)) (firstEl);
    }
    double operator()(const Element& first, const Element& second) const {
        auto firstEl = *dynamic_cast<Constant*>(first.m_data);
        auto secondEl = *dynamic_cast<Constant*>(second.m_data);

        return (*dynamic_cast<Binary*>(m_data)) (firstEl, secondEl);
    }

    friend std::ostream& operator<<(std::ostream& os, const Element& other) {
        auto var = other.getData();

        std::visit([&os](const auto& arg) {
            os << arg << ' ';
            }, var);

        return os;
    }
};

