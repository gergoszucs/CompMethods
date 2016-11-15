#ifndef VECTORNORMS_H // Old style inclue guard to support the .tpp template file inclusion
#define VECTORNORMS_H

#include <vector>

/**
* Static class for calculating different kind of vector norms
* Only arithmetic types are allowed
*
* The VectorNorms class provides:
* \n-inifiniteNorm function to retrieve the maximum element from the vector
* \n-pNorm function to calculate the n-th norm of a vector
*/
template <typename T>
class VectorNorms
{
	// Restrict the template parameter to arithmetic values only
	static_assert(std::is_arithmetic<T>::value, "VectorNorms template type must be an arithmetic value");
public:
	// Delete default member functions to emphasize that the class should only be used to access the static functions
	VectorNorms() = delete;
	~VectorNorms() = delete;
	VectorNorms(const VectorNorms& that) = delete;
	VectorNorms & operator=(const VectorNorms&) = delete;

	/**
	* Static public method that returns a value of type T
	* It returns the element with the highest value from the vector
	* @param values vector<T> - Contains the actual values
	* @return T - The retrieved value
	*/
	static T infiniteNorm(std::vector<T>* values);

	/**
	* Static public method that returns a double
	* It returns the n-th norm of the vector
	* @param values vector<T> - Contains the actual values
	* @param p int - The number of the norm to be calculated
	* @return double - The calculated value of the n-th norm
	*/
	static double pNorm(std::vector<T>* values, int p);
};

// Include the cpp file (which is actually renamned to .tpp) so the Linker will be able to generate the class for different types
// This is the conventional way to implement template classes in C++
#include "VectorNorms.tpp" 

#endif // VECTORNORMS_H