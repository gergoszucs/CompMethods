#pragma once // Include guard

#include "AbstractScheme.h"
#include "Matrix.h"

/**
* Implicit upwind scheme class derived from the Abstract scheme
* It overrides the default implementation of the approximator function
*/
class ImplicitUpwindScheme : public AbstractScheme
{
	Matrix L, U;

	void createLUDecomposition();
public:
	/**
	* Constructor for the Implicit Upwind scheme
	* @param xStart double - Beginning of the space dimension
	* @param xEnd double - End of the space dimension
	* @param t double - The timeframe until the calculations should be executed
	* @param spacePoints int - The number of intervals in the space dimension
	* @param u double - The velocity of the wave
	* @param file std::ostream& - The stream to write the results to (default value is std::cout)
	*/
	ImplicitUpwindScheme(double xStart, double xEnd, double t, int spacePoints, double u, double cfl, std::ostream& stream);
	
	/**
	* Override the pure virtual function to approximate using the Implicit Upwind scheme
	* It returns a vector of doubles containing the numerical values
	* @param double t - The current time frame
	* @return std::vector<double> - The calculated numerical values
	*/
	std::vector<double> calculateIteration(double t) override;

	/**
	* Virtual void function to approximate the current values at the given time frame
	* @param boundaryFunction std::function< double(double) > - The boundary function to start the calculations
	*/
	void evaluate(std::function< double(double) > boundaryFunction, std::ostream *stream = nullptr) override;
};

