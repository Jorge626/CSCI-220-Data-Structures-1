#include "AVLTree.h"

int menu();

int main()
{
	int choice;
	std::string fileName = "C:\\Users\\UserName\\Desktop\\p4small.txt";
	AVLTree tree(fileName);

	do {
		choice = menu();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		switch (choice)
		{
		case 1:
		{
			std::cin.ignore();
			std::string record;
			std::cout << "Enter the county's code: ";
			std::getline(std::cin, record);
			tree.printRecord(tree.searchForRecord(record));
			break;
		}
		case 2:
		{
			std::cin.ignore();
			std::string countyCode, countyPopulation, countyName;
			std::cout << "Please enter a code for the county: ";
			std::getline(std::cin, countyCode);
			std::cout << "Please enter the population for the county: ";
			std::getline(std::cin, countyPopulation);
			std::cout << "Please enter a name for the county: ";
			std::getline(std::cin, countyName);
			tree.insertRecord(countyCode, countyName, countyPopulation);
			break;
		}
		case 3:
		{
			std::cin.ignore();
			std::string countyCode;
			std::cout << "Enter the county code to delete: ";
			std::getline(std::cin, countyCode);
			tree.eraseRecord(countyCode);
			break;
		}
		case 4:
		{
			tree.listAllRecords();
			break;
		}
		case 5:
		{
			std::cout << "Thank you for using my program!\n";
			break;
		}
		default:
			break;
		}
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	} while (choice != 6);

	system("pause");
	return 0;
}

int menu()
{
	int choice;
	std::cout << "           Menu\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "1) Search for a record\n";
	std::cout << "2) Insert a record\n";
	std::cout << "3) Delete a record\n";
	std::cout << "4) List all records\n";
	std::cout << "5) Exit\n";
	std::cout << "Please enter any choice: ";
	std::cin >> choice;
	return choice;
}
