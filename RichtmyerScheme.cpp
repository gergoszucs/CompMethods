#include <iostream>
#include "RichtmyerScheme.h"

RichtmyerScheme::RichtmyerScheme(double xStart, double xEnd, double t, int spacePoints, double u, double cfl, std::ostream& stream)
	: AbstractScheme(stream, "Richtmyer Scheme", xStart, xEnd, t, spacePoints, u, cfl)
{

}

// Define the pure virtual function of the base class
std::vector<double> RichtmyerScheme::calculateIteration(double t)
{
	std::vector<double> newValues;
	double prev, next;

	newValues.push_back(left);
	newValues.push_back(left);

	for (auto i = 2; i < spacePoints - 1; i++) {
		next = 0.5 * (currentValues[i + 2] + currentValues[i]) - (u * deltaT / (4 * deltaX) * (currentValues[i + 2] - currentValues[i]));
		prev = 0.5 * (currentValues[i] + currentValues[i - 2]) - (u * deltaT / (4 * deltaX) * (currentValues[i] - currentValues[i - 2]));

		newValues.push_back(currentValues[i] - u * deltaT / (2 * deltaX) * (next - prev));
	}

	newValues.push_back(right);
	newValues.push_back(right);

	currentValues = newValues;

	return currentValues;
}