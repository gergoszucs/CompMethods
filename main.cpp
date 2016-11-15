#include <iostream>
#include <stdio.h>
#include <math.h> 
#include <memory>
#include <fstream>
#include "ExplicitUpwindScheme.h"
#include "ImplicitUpwindScheme.h"
#include "LaxWendroffScheme.h"
#include "RichtmyerScheme.h"
#include "ConsoleReader.h"
#include "UninitializedFunctionException.h"
#include "VectorNorms.h"

// Function prototype
auto sgn(double) -> int;
auto evaluateScheme(std::shared_ptr<AbstractScheme>) -> void;

auto main() -> int
{
	// Pre-defined values for the calculations
	auto x_start = -50.0, x_end = 50.0, u = 1.75;

	// Ask the user for the missing parameters
	auto space_points = ConsoleReader::getInt("number of space points");
	auto t = ConsoleReader::getDouble("time");
	auto cfl = ConsoleReader::getDouble("CFL");

	remove("userresults.txt");
	std::ofstream file;
	file.open("userresults.txt", std::ios_base::app);

	// Calculate the values for the first problem using different schemes
	std::shared_ptr<AbstractScheme> scheme(new ExplicitUpwindScheme(x_start, x_end, t, space_points, u, cfl, file));
	evaluateScheme(scheme);

	scheme = std::make_shared<ImplicitUpwindScheme>(x_start, x_end, t, space_points, u, cfl, file);
	evaluateScheme(scheme);

	scheme = std::make_shared<LaxWendroffScheme>(x_start, x_end, t, space_points, u, cfl, file);
	evaluateScheme(scheme);

	scheme = std::make_shared<RichtmyerScheme>(x_start, x_end, t, space_points, u, cfl, file);
	evaluateScheme(scheme);

	file.close();

	system("pause");
}

auto evaluateScheme(std::shared_ptr<AbstractScheme> scheme) -> void
{
	try {
		// Calculate what the user asked for
		scheme->setFunction([](double x, double t) {return 0.5 * (sgn(x - 1.75 * t) + 1); }, 0, 1);
		scheme->evaluate([](double x) {return 0.5 * (sgn(x) + 1); });

		scheme->setFunction([](double x, double t) {return 0.5 * std::exp(-std::pow(x - 1.75 * t, 2)); }, 0, 0);
		scheme->evaluate([](double x) {return 0.5 * std::exp(-std::pow(x, 2)); });

		// Calculate all the possibilities and write the results into files
		scheme->calculateAllVariations("exp", [](double x) {return 0.5 * std::exp(-std::pow(x, 2)); });
		scheme->setFunction([](double x, double t) {return 0.5 * (sgn(x - 1.75 * t) + 1); }, 0, 1);
		scheme->calculateAllVariations("sgn", [](double x) {return 0.5 * (sgn(x) + 1); });
	}
	catch (UninitializedFunctionException ufe)
	{
		std::cerr << ufe.what() << std::endl;
	}
}

auto sgn(double value) -> int
{
	return (value > 0) - (value < 0);
}