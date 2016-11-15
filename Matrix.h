#pragma once

#include <vector> //we use Vector in Matrix code

/**
*  A matrix class for data storage of a 2D array of doubles
*  \n The implementation is derived from the standard container vector std::vector
*  \n We use private inheritance to base our vector upon the library version whilst
*  \nallowing usto expose only those base class functions we wish to use - in this
*  \ncase the array access operator []
*
* The Matrix class provides:
* \n-basic constructors for creating a matrix object from other matrix object,
* \nor by creating empty matrix of a given size,
* \n-input and oput operation via >> and << operators using keyboard or file
* \n-basic operations like access via [] operator, assignment and comparision
*/
class Matrix : private std::vector<std::vector<double> > {
	typedef std::vector<std::vector<double> > vec;
public:
	using vec::operator[];  // make the array access operator public within Matrix

	/**
	* Default constructor.  Intialize an empty Matrix object
	* @see Matrix(int Nrows, int Ncols)
	* @see Matrix(const Matrix& m)
	*/
	Matrix();

	/**
	* Alternate constructor.
	* build a matrix Nrows by Ncols
	* @see Matrix()
	* @see Matrix(const Matrix& m)
	* @exception invalid_argument ("matrix size negative or zero")
	*/
	Matrix(int Nrows /**< int. number of rows in matrix */, int Ncols /**< int. number of columns in matrix  */);

	/**
	* Copy constructor.
	* build a matrix from another matrix
	* @see Matrix()
	* @see Matrix(int Nrows, int Ncols)
	*/
	Matrix(const Matrix& m /**< Matrix&. matrix to copy from  */);

	/**
	* Normal public get method.
	* get the number of rows
	* @see int getNcols()const
	* @return int. number of rows in matrix
	*/
	int getNrows() const; // get the number of rows

	/**
	* Normal public get method.
	* get the number of columns
	* @see int getNrows()const
	* @return int. number of columns in matrix
	*/
	int getNcols() const; // get the number of cols

	/**
	* Overloaded assignment operator
	* @see operator==(const Matrix& m)const
	* @return Matrix&. the matrix on the left of the assignment
	*/
	Matrix& operator=(const Matrix& m /**< Matrix&. Matrix to assign from */); // overloaded assignment operator


	/**
	* Overloaded comparison operator
	* returns true or false depending on whether the matrices are the same or not
	* @see operator=(const Matrix& m)
	* @return bool. true or false
	*/
	bool operator==(const Matrix& m  /**< Matrix&. Matrix to compare to */
		) const; // overloaded comparison operator

	/**
	* Overloaded *operator that returns a Matrix.
	* It Performs matrix by matrix multiplication.
	* @see operator*(const Matrix & a) const
	* @exception out_of_range ("Matrix access error")
	* One or more of the matrix have a zero size
	* @exception std::out_of_range ("uncompatible matrix sizes")
	* Number of columns in first matrix do not match number of columns in second matrix
	* @return Matrix. matrix-matrix product
	*/
	//
	Matrix operator*(const Matrix & a /**< Matrix. matrix to multiply by */) const;

	/**
	* Overloaded *operator that returns a Vector.
	* It Performs matrix by vector multiplication.
	* @see operator*(const Matrix & a)const
	* @exception std::out_of_range ("Matrix access error")
	* matrix has a zero size
	* @exception std::out_of_range ("Vector access error")
	* vector has a zero size
	* @exception std::out_of_range ("uncompatible matrix-vector sizes")
	* Number of columns in matrix do not match the vector size
	* @return Vector. matrix-vector product
	*/
	//
	std::vector<double> operator*(const std::vector<double> & v /**< Vector. Vector to multiply by */) const;


	/**
	* public method that returns the transpose of the matrix.
	* It returns the transpose of matrix
	* @return Matrix.  matrix transpose
	*/
	Matrix transpose() const;
};