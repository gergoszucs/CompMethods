#ifdef VECTORNORMS_H

#include <cmath>
#include <algorithm>

template <class T>
T VectorNorms<T>::infiniteNorm(std::vector<T>* vec){

    return *std::max_element((*vec).begin(), (*vec).end());
}

template <class T>
double VectorNorms<T>::pNorm(std::vector<T>* vec, int p){

	auto sum = 0.0;

	for (auto& elem: (*vec)) {
        sum += pow(elem, p);
	}

    return pow(sum, 1.0/p);
}

#endif