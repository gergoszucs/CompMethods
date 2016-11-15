#include "LUFactorisation.h"

void LUFactorisation::luFact(const Matrix& a, Matrix& l, Matrix& u, int n) {
	Matrix temp = a;
	double mult;

	// LU (Doolittle's) decomposition without pivoting
	for (int k = 0; k < n - 1; k++) {
		for (int i = k + 1; i < n; i++) {
			if (fabs(temp[k][k]) < 1.e-07)
			{
				printf("pivot is zero\n");
				exit(1);
			}
			mult = temp[i][k] / temp[k][k];
			temp[i][k] = mult;                      // entries of L are saved in temp
			for (int j = k + 1; j < n; j++) {
				temp[i][j] -= mult*temp[k][j];      // entries of U are saved in temp
				if (fabs(temp[i][i]) < 1.e-07)
				{
					printf("pivot is zero\n");
					exit(1);
				}
			}
		}
	}

	// create l and u from temp
	for (int i = 0; i<n; i++) l[i][i] = 1.0;
	for (int i = 1; i<n; i++)
		for (int j = 0; j<i; j++) l[i][j] = temp[i][j];

	for (int i = 0; i<n; i++)
		for (int j = i; j<n; j++) u[i][j] = temp[i][j];
}

void LUFactorisation::luSolve(const Matrix& l, const Matrix& u, const std::vector<double>& b, int n, std::vector<double>& x) {	std::vector<double> temp(b);
	int i, j;

	// forward substitution for L y = b.
	for (i = 1; i < n; i++)
		for (j = 0; j < i; j++)
			temp[i] -= l[i][j] * temp[j];


	// back substitution for U x = y.  
	for (i = n - 1; i >= 0; i--) {
		for (j = i + 1; j < n; j++) temp[i] -= u[i][j] * temp[j];
		temp[i] /= u[i][i];
	}

	// copy solution into x
	for (i = 0; i<n; i++) x[i] = temp[i];}