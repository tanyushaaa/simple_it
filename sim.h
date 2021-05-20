#pragma once
#include "matrix.h"
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

float norm_i(std::pair<float**, int> mtrx);
float norm_j(std::pair<float**, int> mtrx);
std::pair<float**, int> new_mtrx(std::pair<float**, int> m, float** x);
float* iter_proc (std::pair<float**, int> m, float* x);
float* sim(const Matrix& matrix);
