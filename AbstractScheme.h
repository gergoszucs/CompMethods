#pragma once // Include guard

#include <vector>
#include <functional>

/*! \mainpage Linear advection equation solver
*
* \section intro_sec Introduction
*
* The purpose of this application is to solve different numerical problems
* using multiple schemes for approximation. All schemes will be evaluated for both problem sets
* and the results will be written to the results.txt file. The user is able to specify the most 
* important values to customize the calculations, but the program is not intended to
* be changed externally. To solve new problems or change the predefined values one must
* modify the source code internally.
*/

/**
* Abstract class representing a generic numerical scheme
* \nThe common function for the schemes are implemented here
*
* The AbstractScheme class provides:
* \n-calculateIteration function, the interface for the exact schemes
* \n-evaluate function to resolves the schemes
* \n-setFunction procedure to change the analytical function and the boundary values
*/
class AbstractScheme
{
	/**
	* Private method that calculates the value of deltaX and deltaT based on the user's input
	*/
	void calculateDeltas();

	/**
	* Private method that calculates the boundary values for a scheme
	* @param boundaryFunction std::function< double(double) > - Lambda function used to calculate the boundary values
	*/
	void boundaryCondition(std::function< double(double) > boundaryFunction);

	/**
	* Private method that calculates the analytical values for a function at the given time frame
	* It returns a vector of doubles containing the exact solution
	* @param double t - The current time frame
	* @return std::vector<double> - The calculated analytical values
	*/
	std::vector<double> calculateAnalytical(double t);

	/**
	* Private method that outputs the results to the given stream
	* The constructors for the exact schemes have an optional stream parameter, if it is not supplied
	* the default value will be used which is std::cout
	* @param difference vector<double> - Contains the error values
	* @param time double - The current time frame
	*/
	void writeToStream(std::vector<double>& difference, std::vector<double>& analytical, std::vector<double>& numerical, double time, std::ostream *_stream);

protected:
	std::string name;
	std::ostream& stream;
	std::vector<double> currentValues;
	int spacePoints, boundary, left, right;
	double xStart, xEnd, deltaX, t, deltaT, u, cfl;
	std::function< double(double , double) > analyticalFunction;

public:
	/**
	* Constructor to provide a common creation procedure for the schemes
	* @param file std::ostream& - The stream to write the results to (default value is std::cout)
	* @param name std::string - The name of the scheme
	* @param xStart double - Beginning of the space dimension
	* @param xEnd double - End of the space dimension
	* @param t double - The timeframe until the calculations should be executed
	* @param spacePoints int - The number of intervals in the space dimension
	* @param u double - The velocity of the wave
	*/
	AbstractScheme(std::ostream& stream, std::string name, double xStart, double xEnd, double t, int spacePoints, double u, double cfl);

	/**
	* Virtual destructor to allow the deletion of derived classes through a pointer to the base class
	*/
	virtual ~AbstractScheme();

	/**
	* Pure virtual function to approximate the current values at the given time frame
	* @param u double - The velocity of the wave
	* @return std::vector<double> - The calculated analytical values
	*/
	virtual std::vector<double> calculateIteration(double t) = 0;

	/**
	* Virtual void function to approximate the current values at the given time frame
	* @param boundaryFunction std::function< double(double) > - The boundary function to start the calculations
	*/
	virtual void evaluate(std::function< double(double) > boundaryFunction, std::ostream *stream = nullptr);

	/**
	* Void function to calculate all variatons according to the input parameters
	* @param functionName string - The name of the currently evaluated function
	*/
	void calculateAllVariations(std::string functionName, std::function< double(double) > boundaryFunction);
	
	/**
	* Void function to change the analytical function and the boundary values for a scheme
	* @param analytical std::function< double(double) > - The boundary function to start the calculations
	* @param left int - The left boundary value
	* @param right int - The right boundary value
	*/
	void setFunction(std::function< double(double, double) > analytical, int left, int right);
};