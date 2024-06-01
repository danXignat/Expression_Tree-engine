#pragma once
#include <iostream>
#include <string>
#include <variant>

class Element_Interface {
public:
    virtual void printData() = 0;
    virtual std::variant<char, double, std::string> getData() const = 0;
    virtual std::string getAsString() const = 0;
};

class Operand_Interface : public Element_Interface {
public:
    virtual void printData() = 0;
    virtual std::variant<char, double, std::string> getData() const = 0;
    virtual std::string getAsString() const = 0;
};

class Operator_Interface : public Element_Interface {
public:
    virtual short priority() const = 0;
    virtual void printData() = 0;
    virtual std::variant<char, double, std::string> getData() const = 0;
    virtual std::string getAsString() const = 0;
};




