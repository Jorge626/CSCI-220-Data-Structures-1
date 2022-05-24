#pragma once
#include <string>
#include <iostream>
#include <math.h>
#include "Stack.h"


class Calculator
{
private:
	std::string infix;
	Stack <char> operands;
	Stack <int> operators;

public: 
	Calculator() { std::string infix = ""; }
	Calculator(std::string userExpr) { infix = userExpr; }

	bool isLegal(std::string infix)
	{
		bool legal = true;
		int parenthesisCount = 0;
		try 
		{
			for (size_t i = 0; i < infix.length(); i++)
			{
				switch (infix[i])
				{
				case '(': parenthesisCount++; break;
				case ')': parenthesisCount--; break;
				default: break;
				}
			}
			if (parenthesisCount != 0)
			{
				legal = false;
				throw 0;
			}
		}
		catch (...)
		{
			std::cout << "Error: Unmatched Parenthesis!\n\n";
		}
		try 
		{
			for (size_t i = 0; i < infix.length(); i++)
			{
				switch (infix[i])
				{
				case '.': legal = false; throw 1; break;
				default: break;
				}
			}
		}
		catch (...)
		{
			std::cout << "Error: Operands must be integers!\n\n";
		}
		return legal;
	}

	bool isOperand(char number)
	{
		if (number >= '0' && number <= '9')
			return true;
		else
			return false;
	}

	bool isOperator(char op)
	{
		if (op == '+' || op == '-' || op == '*' || op == '/' || op == '(' || op == ')' ||op == '[' || op == ']' || op == '{' || op == '}' || op == '^')
			return true;
		else
			return false;
	}

	bool isSpace(char character)
	{
		if (character == ' ' || character == '\r' || character == '\n')
			return true;
		else
			return false;
	}

	int precedence(char character)
	{
		if (character == '^')
			return 3;
		else if (character == '*' || character == '/')
			return 2;
		else if (character == '+' || character == '-')
			return 1;
		else if (character == '(' || character == ')' || character == '[' || character == ']' || character == '{' || character == '}')
			return 0;
		else 
			return -1;
	}

	int operate(int valueOne, int valueTwo, char op)
	{
		switch (op) 
		{
		case '+': return valueOne + valueTwo; break;
		case '-': return valueOne - valueTwo; break;
		case '*': return valueOne * valueTwo; break;
		case '/': return valueOne / valueTwo; break;
		case '^': return (int)pow(valueOne, valueTwo); break;
		}
	}

	std::string postfix()
	{
		std::string post;

		for (size_t i = 0; i < infix.length(); i++)
		{
			if (isOperand(infix[i]) == true)
			{
				int currentNumber = 0;
				do
				{
					currentNumber = 10 * currentNumber + (int)(infix[i] - '0');
					++i;
				} while (i < infix.length() && isOperand(infix[i]));
				post = post + std::to_string(currentNumber) + " ";
				--i;
			}

			else if (infix[i] == '(')
				operators.push(infix[i]);
			
			else if (infix[i] == ')')
			{
				while (operators.top() != '(')
				{
					post.push_back(operators.pop());
					post = post + " ";
				}
				operators.pop();
			}

			else if (isSpace(infix[i]) == true)
				continue;

			else if (isOperator(infix[i]) == true)
			{
				if (operators.empty() == true || precedence(infix[i]) >= precedence(operators.top()))
				{
					operators.push(infix[i]);
				}
				else
				{
					post.push_back(operators.pop());
					post = post + " ";
					operators.push(infix[i]);
				}
			}
		} 

		while (operators.empty() != true)
		{
			if (operators.top() == '(')
				operators.pop();
			else
			{
				post.push_back(operators.pop());
				post = post + " ";
			}
		}

		return post;
	}

	int eval()
	{
		int finalAnswer;
		for (size_t i = 0; i < infix.length(); i++)
		{
			if (isOperand(infix[i]) == true)
			{
				int currentNumber = 0;
				do 
				{
					currentNumber = 10 * currentNumber + (int)(infix[i] - '0');
					++i;
				} while (i < infix.length() && isOperand(infix[i]));
				operands.push(currentNumber);
				--i;
			}

			else if (infix[i] == '(')
				operators.push(infix[i]);
			
			else if (infix[i] == ')')
			{
				while (operators.top() != '(')
				{
					int valueOne = operands.pop();
					int valueTwo = operands.pop();
					char op = operators.pop();
					operands.push(operate(valueTwo,valueOne,op));
				}
				operators.pop();
			}

			else if (isSpace(infix[i]) == true)
				continue;

			else if (isOperator(infix[i]) == true)
			{
				if (operators.empty() == true || precedence(infix[i]) >= precedence(operators.top()))
				{
					operators.push(infix[i]);
				}
				else
				{
					int valueTwo = operands.pop();
					int valueOne = operands.pop();
					char op = operators.pop();
					operands.push(operate(valueOne, valueTwo, op));
					operators.push(infix[i]);
				}
			}
		}
		finalAnswer = operands.top();

		while (operators.empty() != true)
		{
			int valueTwo = operands.pop();
			int valueOne = operands.pop();
			char op = operators.pop();
			operands.push(operate(valueOne, valueTwo, op));
			finalAnswer = operate(valueOne, valueTwo, op);
		}

		return finalAnswer;
	}
	
	void setExpr(std::string infixExpr)
	{
		infix = infixExpr;
	}

	std::string getExpr()
	{
		return infix;
	}
};