#include <iostream>
#include "ImplicitUpwindScheme.h"
#include "LUFactorisation.h"

ImplicitUpwindScheme::ImplicitUpwindScheme(double xStart, double xEnd, double t, int spacePoints, double u, double cfl, std::ostream& stream)
	: AbstractScheme(stream, "Implicit Upwind Scheme", xStart, xEnd, t, spacePoints, u, cfl)
{

}

// Define the pure virtual function of the base class
std::vector<double> ImplicitUpwindScheme::calculateIteration(double t)
{
	std::vector<double> newValues(spacePoints + 1);

	LUFactorisation::luSolve(L, U, newValues, spacePoints + 1, currentValues);

	newValues[0] = left;
	newValues[1] = newValues[1] + cfl;
	newValues[spacePoints] = right;

	currentValues = newValues;

	return currentValues;
}

// Define the pure virtual function of the base class
void ImplicitUpwindScheme::createLUDecomposition()
{
	L = Matrix(spacePoints + 1, spacePoints + 1);
	U = Matrix(spacePoints + 1, spacePoints + 1);
	Matrix A = Matrix(spacePoints + 1, spacePoints + 1);
	
	auto cfl = (deltaT * u) / deltaX;

	for (auto i = 0; i <= spacePoints; i++) {
		for (auto j = 0; j <= spacePoints; j++) {
			if (i == j) {
				A[i][j] = 1 + cfl;
			}
			/*else if (i + 1 == j) {
				A[i][j] = 0.5 * cfl;
			}*/
			else if (i - 1 == j) {
				A[i][j] = - cfl;
			}
			else {
				A[i][j] = 0;
			}
		}
	}

	LUFactorisation::luFact(A, L, U, spacePoints + 1);
}

void ImplicitUpwindScheme::evaluate(std::function< double(double) > boundaryFunction, std::ostream *stream)
{
	createLUDecomposition();
	AbstractScheme::evaluate(boundaryFunction, stream);
}