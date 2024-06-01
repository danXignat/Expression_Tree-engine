#include "Expression_Tree.h"

int main()
{
	Expression_Tree tree("x^3+x(x*x+x^2)");
	tree.print();
}