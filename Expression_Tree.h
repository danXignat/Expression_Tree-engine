#pragma once
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <iostream>

#include "Element.h"
#include "Parser.h"

class Expression_Tree {
private:
	using Vector = Parser::Vector;
	using Tree_Matrix = std::vector<std::vector<std::string>>;


	struct Node {
		Element data;
		Node*  left;
		Node* right;

		Node(const Element& data)
			: data(data),
			  left(nullptr), right(nullptr) {}
	};

	Parser parser;
	std::string m_expression;
	Node* m_root;

private:

public:
	Expression_Tree()
		: m_root(nullptr) {}

	Expression_Tree(const std::string& expression)
		: m_expression(expression)
	{
		Vector polish = parser.getPolish(expression);
		std::stack<Node*> stack;

		for (const auto& el : polish) {
			if (el.isOperand()) {
				stack.push(new Node(el));
			}
			else {
				Node* newNode = new Node(el);

				newNode->right = stack.top(), stack.pop();
				if (el.isBinary())
					newNode->left = stack.top(), stack.pop();

				stack.push(newNode);
			}
		}
		
		m_root = stack.top(), stack.pop();
	}

	Tree_Matrix& bfs() const {
		Tree_Matrix levels;

		std::queue<Node*> queue;
		queue.push(m_root);

		while (!queue.empty()) {
			size_t levelSize = queue.size();
			std::vector<std::string> level;

			for (size_t i = 0; i < levelSize; i++) {
				Node* frontNode = queue.front(); queue.pop();
				std::cout << (frontNode->data) << ' ';
				level.emplace_back( frontNode->data.getAsString() );

				if (frontNode-> left) queue.push(frontNode-> left);
				if (frontNode->right) queue.push(frontNode->right);
			}
			std::cout << std::endl;
			levels.emplace_back(level);
		}

		return levels;
	}



	void printSubtree(Node* root, const std::string& prefix)
	{
		if (!root)
		{
			return;
		}

		bool hasLeft = (root->left != nullptr);
		bool hasRight = (root->right != nullptr);

		if (!hasLeft && !hasRight)
		{
			return;
		}

		std::cout << prefix;
		std::cout << ((hasLeft && hasRight) ? "├── " : "");
		std::cout << ((!hasLeft && hasRight) ? "└── " : "");

		if (hasRight)
		{
			bool printStrand = (hasLeft && hasRight && (root->right->right != nullptr || root->right->left != nullptr));
			std::string newPrefix = prefix + (printStrand ? "│   " : "    ");
			std::cout << (root->right->data) << std::endl;
			printSubtree(root->right, newPrefix);
		}

		if (hasLeft)
		{
			std::cout << (hasRight ? prefix : "") << "└── " << (root->left->data) << std::endl;
			printSubtree(root->left, prefix + "    ");
		}
	}

	void print() {
		if (m_root == NULL)
		{
			return;
		}

		std::cout << (m_root->data) << std::endl;
		printSubtree(m_root, "");
		std::cout << std::endl;
	}
};
