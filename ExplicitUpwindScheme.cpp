#include <iostream>
#include "ExplicitUpwindScheme.h"

ExplicitUpwindScheme::ExplicitUpwindScheme(double xStart, double xEnd, double t, int spacePoints, double u, double cfl, std::ostream& stream)
	: AbstractScheme(stream, "Explicit Upwind Scheme", xStart, xEnd, t, spacePoints, u, cfl)
{

}

std::vector<double> ExplicitUpwindScheme::calculateIteration(double t)
{
	std::vector<double> newValues;

	newValues.push_back(left);

	for (auto i = 1; i < spacePoints; i++) {
		newValues.push_back(currentValues[i] - u * (deltaT / deltaX) * (currentValues[i] - currentValues[i - 1]));
	}

	newValues.push_back(right);

	currentValues = newValues;

	return currentValues;
}