#pragma once // Include guard

#include <iostream>

/**
* Static class for reading user input from the console
*
* The ConsoleReader class provides:
* \n-getInt function to safely retrieve an integer from the command line
* \n-getDouble function to safely retrieve a double from the command line
*/
class ConsoleReader
{
public:
	// Delete default member functions to emphasize that the class should only be used to access the static functions.
	ConsoleReader() = delete;
	~ConsoleReader() = delete;
	ConsoleReader(const ConsoleReader& that) = delete;
	ConsoleReader & operator=(const ConsoleReader&) = delete;

	/**
	* Static public method that returns an integer
	* It returns the read value from the console
	* @param name string - Used to output the actual name of the value to be retrieved
	* @return int - The retrieved value
	*/
	static int getInt(std::string name);

	/**
	* Static public method that returns a double
	* It returns the read value from the console
	* @param name string - Used to output the actual name of the value to be retrieved
	* @return double - The retrieved value
	*/
	static double getDouble(std::string name);
};

