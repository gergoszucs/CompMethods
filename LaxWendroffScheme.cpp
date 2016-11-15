#include <iostream>
#include "LaxWendroffScheme.h"

LaxWendroffScheme::LaxWendroffScheme(double xStart, double xEnd, double t, int spacePoints, double u, double cfl, std::ostream& stream)
	: AbstractScheme(stream, "Lax-Wendroff Scheme", xStart, xEnd, t, spacePoints, u, cfl)
{

}

// Define the pure virtual function of the base class
std::vector<double> LaxWendroffScheme::calculateIteration(double t)
{
	std::vector<double> newValues;

	newValues.push_back(left);

	for (auto i = 1; i < spacePoints; i++) {
		newValues.push_back(currentValues[i] - u * deltaT * ((currentValues[i+1] - currentValues[i-1]) / (2 * deltaX)) 
			+ 0.5 * std::pow(u, 2) * std::pow(deltaT, 2) * ((currentValues[i+1] - 2 * currentValues[i] + currentValues[i-1]) / std::pow(deltaX, 2)));
	}

	newValues.push_back(right);

	currentValues = newValues;

	return currentValues;
}