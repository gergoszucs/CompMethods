#pragma once // Include guard

#include "Matrix.h"

/**
* Static class for LU factorisation of a matrix
*
* The LUfactorisation  class provides:
* \n-luFact function to create the L and U matrices
* \n-luSolve function to solve the LUx = b equation
*/
class LUFactorisation
{
public:
	// Delete default member functions to emphasize that the class should only be used to access the static functions.
	LUFactorisation() = delete;
	~LUFactorisation() = delete;
	LUFactorisation(const LUFactorisation& that) = delete;
	LUFactorisation & operator=(const LUFactorisation&) = delete;

	/**
	* Static public method
	* It creates the L and U matrices which are passed by reference
	* @param a Matrix - The matrix to be factored
	* @param l Matrix - The lower diagonal matrix
	* @param u Matrix - The upper diagonal matrix
	* @param n int - Used to output the actual name of the value to be retrieved
	*/
	static void luFact(const Matrix& a, Matrix& l, Matrix& u, int n);

	/**
	* Static public method
	* It calculates the x vector using the LUx = b equation
	* @param l Matrix - The matrix to be factored
	* @param u Matrix - The lower diagonal matrix
	* @param b std::vector<double> - The vector with the previous values
	* @param n int - The size of the vector
	* @param x std::vector<double> - The result vector
	*/
	static void luSolve(const Matrix& l, const Matrix& u, const std::vector<double>& b, int n, std::vector<double>& x);
};

