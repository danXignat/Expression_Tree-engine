#include "Element.h"

const std::unordered_set<std::string> Element::s_unaries = { "sin", "cos", "tan", "cot",
                                                             "sqrt", "ln",
                                                             "-", "+" };

const std::unordered_set<std::string> Element::s_binaries = { "+", "-", "*", "/", "^" };

const std::unordered_set<std::string> Element::s_pharanthesis = { "(", ")",
                                                                  "[", "]",
                                                                  "{", "}" };

