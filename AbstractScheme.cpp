#include <iterator>
#include <string>
#include <fstream>
#include <iomanip>
#include "AbstractScheme.h"
#include "VectorNorms.h"
#include "UninitializedFunctionException.h"

AbstractScheme::AbstractScheme(std::ostream& _stream, std::string _name, double _xStart, double _xEnd, double _t, int _spacePoints, double _u, double _cfl)
	: stream(_stream), name(_name), xStart(_xStart), xEnd(_xEnd), t(_t), spacePoints(_spacePoints), u(_u), cfl(_cfl)
{
	calculateDeltas();
}

AbstractScheme::~AbstractScheme()
{

}

void AbstractScheme::calculateDeltas()
{
	deltaX = (fabs(xStart) + fabs(xEnd)) / (spacePoints);
	deltaT = (cfl * deltaX) / u;
}

void AbstractScheme::boundaryCondition(std::function< double(double) > boundaryFunction)
{
	currentValues.clear();

	currentValues.push_back(left);

	for (auto i = xStart + deltaX; i < xEnd; i += deltaX) {
		currentValues.push_back(boundaryFunction(i));
	}

	currentValues.push_back(right);
}

std::vector<double> AbstractScheme::calculateAnalytical(double t)
{
	std::vector<double> analyticalValues;

	for (auto i = xStart; i <= xEnd; i += deltaX) {
		analyticalValues.push_back(analyticalFunction(i, t));
	}

	return analyticalValues;
}

void AbstractScheme::evaluate(std::function< double(double) > boundaryFunction, std::ostream *_stream)
{
	if (analyticalFunction == nullptr) {
		throw UninitializedFunctionException();
	}

	std::vector<double> analytical, numerical, difference;

	boundaryCondition(boundaryFunction);

	// Write the user defined result's to the result.txt
	if (_stream == nullptr) {
		stream << "\n-----------------------\n" << name << "\n-----------------------\n\n";
	}
	
	for (auto i = deltaT; i <= t; i += deltaT) {
		analytical = calculateAnalytical(i);
		numerical = calculateIteration(i);

		std::transform(analytical.begin(), analytical.end(), numerical.begin(), std::back_inserter(difference), [](double a, double b) { return fabs(a - b); });

		if (i >= t - deltaT) {
			writeToStream(difference, analytical, numerical, i, _stream);
		}

		difference.clear();
	}
}

void AbstractScheme::writeToStream(std::vector<double>& difference, std::vector<double>& analytical, std::vector<double>& numerical, double time, std::ostream *_stream)
{
	// Write the user defined result's to the userresult.txt
	if (_stream == nullptr) {
		stream << "t = " << time << std::endl;
		stream << "infinite norm is " << VectorNorms<double>::infiniteNorm(&difference) << std::endl;
		stream << "1st norm is " << VectorNorms<double>::pNorm(&difference, 1) << std::endl;
		stream << "2nd norm is " << VectorNorms<double>::pNorm(&difference, 2) << std::endl << std::endl;
	}
	else
	{
		*_stream << "infinite " << VectorNorms<double>::infiniteNorm(&difference) << std::endl;
		*_stream << "1st " << VectorNorms<double>::pNorm(&difference, 1) << std::endl;
		*_stream << "2nd " << VectorNorms<double>::pNorm(&difference, 2) << std::endl << std::endl;
		*_stream << "grid, Analytical, Numerical" << std::endl;
	}

	auto x = xStart;

	for (auto i = 0; i < analytical.size(); i++) {
		if (_stream != nullptr) {
			*_stream << x << ", " << analytical[i] << ", " << numerical[i] << std::endl;
		}

		x += deltaX;
	}
}

void AbstractScheme::setFunction(std::function<double(double, double)> function, int _left, int _right)
{
	analyticalFunction = function;
	left = _left;
	right = _right;
}

void AbstractScheme::calculateAllVariations(std::string functionName, std::function< double(double) > boundaryFunction) 
{
	std::ofstream stream;

	spacePoints = 100, t = 5, cfl = 0.5;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 0.99;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 1.01;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 1.99;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	t = 10, cfl = 0.5;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 0.99;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 1.01;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 1.99;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	spacePoints = 200, t = 5, cfl = 0.5;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 0.99;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 1.01;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 1.99;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	spacePoints = 400, t = 5, cfl = 0.5;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 0.99;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 1.01;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();

	cfl = 1.99;
	calculateDeltas();
	stream.open("results/" + name + " " + functionName + " " + std::to_string(spacePoints) + " " + std::to_string((int)t) + " " + std::to_string(cfl).substr(0, 4) + ".txt");
	evaluate(boundaryFunction, &stream);
	stream.close();
}