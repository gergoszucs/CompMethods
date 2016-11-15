#include "UninitializedFunctionException.h"

UninitializedFunctionException::UninitializedFunctionException() 
	: std::runtime_error("Uninitialized function! setFunction must be called before evaluating a scheme.")
{

}