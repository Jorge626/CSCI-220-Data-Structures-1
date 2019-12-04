#pragma once

#include "SearchTree.h"
#include "Entry.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

class AVLTree
{
public:
	typedef typename SearchTree< Entry<std::string, std::string, std::string> > ST;
	typedef typename SearchTree< Entry<std::string, std::string, std::string> >::Iterator Iterator;

	AVLTree() { }
	AVLTree(std::string fileName)
	{
		std::ifstream entryFile;
		entryFile.open(fileName);
		if (entryFile.fail())
		{
			std::cout << "Error: File not found\n";
			exit(1);
		}
		else
		{
			std::string line, countyCode, countyPopulation, countyName;
			std::stringstream ss(line);

			while (std::getline(entryFile, line))
			{
				std::stringstream ss(line);
				std::getline(ss, countyCode, ',');
				std::getline(ss, countyPopulation, ',');
				std::getline(ss, countyName, '\t');
				insertRecord(countyCode, countyPopulation, countyName);
			}
		}
		entryFile.close();
	}

	Iterator searchForRecord(std::string countyCode)
	{
		Iterator record = Tree.find(countyCode);
		return record;
	}

	Iterator insertRecord(std::string countyCode, std::string countyPopulation, std::string countyName)
	{
		Iterator record = Tree.insert(countyCode, countyName, countyPopulation);;
		return record;
	}

	void eraseRecord(std::string countyCode)
	{
		Tree.erase(countyCode);
	}

	void listAllRecords()
	{
		Iterator tempIterator = Tree.begin();
		for (tempIterator; tempIterator != Tree.end(); ++tempIterator)
		{
			std::cout << (*tempIterator).countyCode() << " " << (*tempIterator).countyName() << " " << (*tempIterator).countyPopulation() << "\n";
		}
	}

	void printRecord(Iterator record)
	{
		if ((*record).countyCode() == "")
			std::cout << "Error: No information found\n";
		else
			std::cout << "The record is:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nCounty Code: " << (*record).countyCode() << "\nCounty Population: " << (*record).countyName() << "\nCounty Name: " << (*record).countyPopulation() << "\n";
	}

protected:
	ST Tree;
	Iterator iterator = Tree.begin();
};
