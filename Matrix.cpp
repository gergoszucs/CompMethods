#include "Matrix.h"

/*
*Default constructor (empty matrix)
*/
Matrix::Matrix() : std::vector<std::vector<double> >() {}

/*
* Alternate constructor - creates a matrix with the given values
*/
Matrix::Matrix(int Nrows, int Ncols) : std::vector<std::vector<double> >()
{
	//check input
	if (Nrows < 0 || Ncols < 0) throw std::invalid_argument("matrix size negative");

	// set the size for the rows
	(*this).resize(Nrows);
	// set the size for the columns
	for (int i = 0; i < Nrows; i++) (*this)[i].resize(Ncols);

	// initialise the matrix to contain zero
	for (int i = 0; i < Nrows; i++)
		for (int j = 0; j < Ncols; j++) (*this)[i][j] = 0.0;
}

/*
* Copy constructor
*/
Matrix::Matrix(const Matrix& m) : std::vector<std::vector<double> >()
{
	// set the size of the rows
	(*this).resize(m.size());
	// set the size of the columns
	std::size_t i;
	for (i = 0; i < m.size(); i++) (*this)[i].resize(m[0].size());

	// copy the elements
	for (int i = 0; i < m.getNrows(); i++)
		for (int j = 0; j < m.getNcols(); j++)
			(*this)[i][j] = m[i][j];
}

/*
* accessor method - get the number of rows
*/
int Matrix::getNrows() const
{
	return size();
}

/*
* accessor method - get the number of columns
*/
int Matrix::getNcols() const
{
	return (*this)[0].size();
}

/*
* Operator= - assignment
*/
Matrix& Matrix::operator=(const Matrix& m)
{
	(*this).resize(m.size());
	std::size_t i;
	std::size_t j;
	for (i = 0; i < m.size(); i++) (*this)[i].resize(m[0].size());

	for (i = 0; i<m.size(); i++)
		for (j = 0; j<m[0].size(); j++)
			(*this)[i][j] = m[i][j];
	return *this;
}

/*
* Operator* multiplication of a matrix by a matrix
*/
Matrix Matrix::operator*(const Matrix& a) const {

	int nrows = getNrows();
	int ncols = getNcols();

	// catch invalid matrices
	if (nrows <= 0 || ncols <= 0) { throw std::out_of_range("Matrix access error"); }
	if (a.getNrows() <= 0 || a.getNcols() <= 0) { throw std::out_of_range("Matrix access error"); }

	//if the matrix sizes do not match
	if (ncols != a.getNrows()) throw std::out_of_range("matrix sizes do not match");

	//  matrix to store the result
	Matrix mmult = Matrix(getNrows(), a.getNcols());

	//matrix multiplication
	for (int i = 0; i<getNrows(); i++) {
		for (int j = 0; j<a.getNcols(); j++) {
			for (int k = 0; k<getNcols(); k++) {
				mmult[i][j] += ((*this)[i][k] * a[k][j]);
			}
		}
	}
	return mmult;
}


/*
* Operator* multiplication of a matrix by a vector
*/
std::vector<double> Matrix::operator*(const std::vector<double>& v) const {
	int nrows = getNrows();
	int ncols = getNcols();

	// catch invalid matrix, vector
	if (nrows <= 0 || ncols <= 0) { throw std::out_of_range("Matrix access error"); }
	if (v.size() <= 0) { throw std::out_of_range("Vector access error"); }

	//if the matrix sizes do not match
	if (ncols != v.size()) throw std::out_of_range("matrix sizes do not match");

	// matrix to store the multiplication
	std::vector<double> res(nrows);

	// perform the multiplication
	for (int i = 0; i<nrows; i++)
		for (int j = 0; j<ncols; j++) res[i] += ((*this)[i][j] * v[j]);

	// return the result
	return res;
}


/*
* Operator== comparison function, returns true if the given matrices are the same
*/
bool Matrix::operator==(const Matrix& a) const {
	int nrows = getNrows();
	int ncols = getNcols();

	//if the sizes do not match return false*
	if ((nrows != a.getNrows()) || (ncols != a.getNcols())) return false;

	//compare all of the elements
	for (int i = 0; i<nrows; i++) {
		for (int j = 0; j<ncols; j++) {
			if (fabs((*this)[i][j] - a[i][j]) > 1.e-07) { return false; }
		}
	}

	return true;
}

/*
* Transpose of the matrix
*/
Matrix Matrix::transpose() const
{
	int nrows = getNrows();
	int ncols = getNcols();

	// matrix to stoore the transpose
	Matrix temp(ncols, nrows);

	for (int i = 0; i < ncols; i++)
		for (int j = 0; j < nrows; j++)
			temp[i][j] = (*this)[j][i];

	return temp;
}