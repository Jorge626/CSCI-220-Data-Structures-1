/*  Program: CSCI 220 Project 2
	Author: Jorge Aranda
	Class: CSCI 220
	Date: 10/14/2019
	Description: A calculator that returns expressions in postfix notation
	as well as evaluating the expression. Also throws error messages
	when given illegal expressions.

	I certify that the code below is my own work.

	Exception(s): Code to get complete number in expression
	do
	{
		currentNumber = 10 * currentNumber + (int)(infix[i] - '0');
		++i;
	} while (i < infix.length() && isOperand(infix[i]));
	--i;
*/

#include "Calculator.h"

int main()
{
	std::string userInput, sentinel = "0";
	std::cout << "Jorge Aranda's Calculator\nEnter 0 to exit the program.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	while (userInput != sentinel)
	{
		std::cout << "Enter an expression: ";
		std::getline(std::cin, userInput);
		if (userInput == "0")
			break;
		Calculator userExpression(userInput);
		if (userExpression.isLegal(userInput) == false)
			continue;
		else
		{
			std::cout << "Postfix expression: " << userExpression.postfix();
			std::cout << "\nResult: " << userExpression.eval() << "\n\n";
		}
	}

	std::cout << "Thanks for using my calculator!\n";

	system("pause");

	return 0;
}