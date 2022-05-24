/*  Program: CSCI 220 Project 3
	Author: Jorge Aranda
	Class: CSCI 220
	Date: 11/3/2019
	Description: A text editor program that uses iterators and node list
	data structure to implement. It supports features such as moving the 
	cursor left and right, inserting and removing words and characters,
	getting the current position of the cursor, as well as going to a
	specific position and displaying the string and number of characters
	in the string.

	I certify that the code below is my own work.

	Exception(s): NodeList ADT given in code fragments
*/


#include "NodeList.h"

int menu();

int main()
{
	int choice;
	std::string startingString;
	std::cout << "Enter a starting string: ";
	std::getline(std::cin, startingString);
	NodeList list (startingString);
	NodeList::Iterator iterator(list.end());
	std::cout << "Editing document...\n";
	std::cout << "'>' will be used to indicate the cursor\n\n";

	do 
	{
		choice = menu();
		switch (choice)
		{
		case 1:
		{
			if (iterator == list.begin())
				std::cout << "Cursor is at the beginning (ignored)\n";
			else
				--iterator;
			list.print(iterator, list);
			break;
		}
		case 2:
		{
			if (iterator == list.end())
				std::cout << "Cursor is at the end (ignored)\n";
			else
				++iterator;
			list.print(iterator, list);
			break;
		}
		case 3:
		{
			char insertChar;
			std::cout << "Enter a character: ";
			std::cin >> insertChar;
			list.insert(iterator, insertChar);
			list.print(iterator, list);
			break;
		}
		case 4:
		{
			if (list.isAtEnd(iterator) == true)
			{
				std::cout << "Cursor is at the end (ignored)\n";
				break;
			}
			NodeList::Iterator tempIterator = iterator;
			++iterator;
			list.erase(tempIterator);
			list.print(iterator, list);
			break;
		}
		case 5:
		{
			std::cout << "Current Position: " << list.atIndex(iterator, list) << "\n";
			break;
		}
		case 6:
		{
			int position;
			std::cout << "Enter a position: ";
			std::cin >> position;
			list.indexOf(position, iterator);
			list.print(iterator, list);
			break;
		}
		case 7:
		{
			std::cin.ignore();
			std::string wordToAdd;
			std::cout << "Insert word to add: ";
			std::getline(std::cin, wordToAdd);
			for (std::string::size_type i = 0; i < wordToAdd.length(); i++)
			{
				list.insert(iterator, wordToAdd[i]);
			}
			list.insert(iterator, ' ');
			list.print(iterator, list);
			break;
		}
		case 8:
		{
			if (list.isAtEnd(iterator) == true)
			{
				std::cout << "Cursor is at the end (ignored)\n";
				break;
			}
			else if (*iterator == ' ')
			{
				std::cout << "Error: Cursor is not at the beginning of\na word!\n";
				break;
			}
			do
			{
				NodeList::Iterator tempIterator = iterator;
				++iterator;
				list.erase(tempIterator);
			} while (*iterator != ' ');
			NodeList::Iterator tempIterator = iterator;
			++iterator;
			list.erase(tempIterator);
			list.print(iterator, list);
			break;
		}
		case 9:
		{
			list.print(iterator, list);
			std::cout << "Length: " << list.size() << "\n";
			break;
		}
		case 10:
		{
			std::cout << "Thank you for using my editor program!\n";
			break;
		}
		default:
			std::cout << "Please enter a valid option";
			break;
		}
		std::cout << "\n";
	} while (choice != 10);
	system("pause");
	return 0;
}
int menu()
{
	int choice;
	std::cout << "Editing Menu\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "1) Move left\n";
	std::cout << "2) Move right\n";
	std::cout << "3) Insert character\n";
	std::cout << "4) Delete character\n";
	std::cout << "5) Get current position\n";
	std::cout << "6) Go to position\n";
	std::cout << "7) Add word\n";
	std::cout << "8) Delete word\n";
	std::cout << "9) Display\n";
	std::cout << "10) Quit\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "Please enter any choice: ";
	std::cin >> choice;
	return choice;
}
