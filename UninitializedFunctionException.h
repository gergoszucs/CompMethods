#pragma once // Include guard

#include <stdexcept>

/**
* Custom runtime exception class to handle uninitialized functions in the schemes
* It overrides the default implementation of the what function to produce the error message
*/
class UninitializedFunctionException : public std::runtime_error
{
public:
	/**
	* Constructor for the exception that will call the base class's constuctor to produce the error message
	*/
	UninitializedFunctionException();
};

