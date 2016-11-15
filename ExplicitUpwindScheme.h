#pragma once // Include guard

#include "AbstractScheme.h"

/**
* Explicit upwind scheme class derived from the Abstract scheme
* It overrides the default implementation of the approximator function
*/
class ExplicitUpwindScheme : public AbstractScheme
{
public:
	/**
	* Constructor for the Explicit Upwind scheme
	* @param xStart double - Beginning of the space dimension
	* @param xEnd double - End of the space dimension
	* @param t double - The timeframe until the calculations should be executed
	* @param spacePoints int - The number of intervals in the space dimension
	* @param u double - The velocity of the wave
	* @param file std::ostream& - The stream to write the results to (default value is std::cout)
	*/
	ExplicitUpwindScheme(double xStart, double xEnd, double t, int spacePoints, double u, double cfl, std::ostream& stream);
	
	/**
	* Override the pure virtual function to approximate using the Explicit Upwind scheme
	* It returns a vector of doubles containing the numerical values
	* @param double t - The current time frame
	* @return std::vector<double> - The calculated numerical values
	*/
	std::vector<double> calculateIteration(double t) override;
};

