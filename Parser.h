#pragma once
#include <vector>
#include <string>
#include <stack>

#include "Element.h"

class Parser {
public:
	using Vector = std::vector<Element>;

private:
	bool isReady(const std::string& token, const char& curr) {
		if (isdigit(token.back()) && !isdigit(curr))
			return true;

		if (Element::s_binaries.contains(token))
			return true;

		if (Element::s_unaries.contains(token))
			return true;

		if (Element::s_pharanthesis.contains(token))
			return true;

		if (isalpha(token.back()) && !isalpha(curr))
			return true;

		return false;
	}

	bool isUnary(const std::string& token, const Vector& parser) {
		if (Element::s_unaries.contains(token)) {
			if (parser.empty())
				return true;

			if (parser.back().isOperator())
				return true;

			if (parser.back().getAsString() == "(")
				return true;
		}

		return false;
	}

	bool isHiddenMultiplication(const Element& prev, const Element& curr) {
		if (prev.isOperand() && curr.isOperand())
			return true;

		if (prev.isOperand() && curr.getAsString() == "(")
			return true;

		if (prev.isOperand() && curr.isUnary())
			return true;

		if (prev.getAsString() == ")" && curr.getAsString() == "(")
			return true;

		return false;
	}

	short priorityComparator(const Element& first, const Element& second) {
		if (first.priority() < second.priority()) {
			return -1;
		}

		if (first.priority() > second.priority()) {
			return 1;
		}

		return 0;
	}
public:
	Vector getParser(const std::string& expression) {
		Vector parser;

		std::string token;
		for (const char& ch : expression) {
			if (ch == ' ')
				continue;

			if (!token.empty() && isReady(token, ch)) {

				if (!parser.empty() && isHiddenMultiplication(parser.back(), token))
					parser.emplace_back("*");

				if (isUnary(token, parser))
					parser.emplace_back(new Unary(token));
				else
					parser.emplace_back(token);

				token.clear();
			}

			token += ch;
		}

		parser.emplace_back(token);

		return parser;
	}
	Vector getPolish(const std::string& expression) {
		std::stack<Element> op;

		Vector parser = this->getParser(expression);
		Vector polish;

		for (const auto& el : parser) {
			if (el.isOperand()) {
				polish.push_back(el);
			}
			else if (el.isLeftBracket()) {
				op.push(el);
			}
			else if (el.isRightbracket()) {
				while (!op.top().isLeftBracket()) {
					polish.push_back(op.top());
					op.pop();
				}
				op.pop();
			}
			else {
				if (op.empty()) {
					op.push(el);
					continue;
				}

				switch (priorityComparator(el, op.top())) {
				case -1:
					while (!op.empty() && !op.top().isLeftBracket()) {
						polish.push_back(op.top());
						op.pop();
					}
					op.push(el);
					break;
				
				case 0:
					polish.push_back(op.top());
					op.pop();
					op.push(el);
					break;
				
				case 1:
					op.push(el);
					break;
				}
			}
		}
		while (!op.empty()) {
			polish.push_back(op.top());
			op.pop();
		}
		
		return polish;
	}

	Parser() = default;
	~Parser() = default;
};