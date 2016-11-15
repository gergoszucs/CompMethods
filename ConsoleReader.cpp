#include "ConsoleReader.h"

#include <string>
#include <limits>

int ConsoleReader::getInt(std::string name)
{
	std::string line;
	int num = 0;

	std::cout << "Please enter a positive integer value for " << name << ": ";

	while (!(std::cin >> num) || num <= 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Try again: ";
	}

	return num;
}

double ConsoleReader::getDouble(std::string name)
{
	std::string line;
	double num;

	std::cout << "Please enter a positive double value for " << name << ": ";

	while (!(std::cin >> num) || num <= 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Try again: ";
	}

	return num;
}