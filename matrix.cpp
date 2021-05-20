#include "matrix.h"

///////////////////////////////  О п р е д е л и т е л ь  //////////////////////////////

float det_(float **T, int N) {
	switch (N){
	case 1:
		return T[0][0];
	case 2:
		return T[0][0] * T[1][1] - T[0][1] * T[1][0];
	default:
		if (N < 1) {
			throw std::invalid_argument("There is no elements in this matrix.");
		}
		float **minor = new float*[N-1];		//массив указателей на столбцы исходной матрицы
		float det = 0;							//исключая заданные стр. и стл. (минор)
		int sign = 1;							//знак минора
		for (int i = 0; i < N; i++) {			//разложение по первому столбцу
			int sub_j = 0;
			for (int j = 0; j < N; j++) {		//заполнение "минорной" матрицы ссылками на исходные столбцы
				if (i != j)						//исключить i строку
					minor[sub_j++] = T[j] + 1;	//исключить 1й(0й) столбец
			}
			det += sign * T[i][0] * det_(minor, N-1);
			sign = -sign;
		}
		delete[] minor;
		return det;
	}
}

///////////////////////////////  К л а с с  м а т р и ц  ///////////////////////////////

	Matrix::Matrix() : n(3) {
		A = new float* [n];
		for (int i = 0; i < n; i++) {
			A[i] = new float [n + 1];
		}

		A[0][0] = 1.61;
		A[0][1] = 0.71;
		A[0][2] = -0.05;
		A[0][3] = 0.44;

		A[1][0] = -1.03;
		A[1][1] = -2.05;
		A[1][2] = 0.87;
		A[1][3] = -1.16;

		A[2][0] = 2.50;
		A[2][1] = -3.12;
		A[2][2] = -6.03;
		A[2][3] = -7.50;

		det = det_(A, n);
	}

	Matrix::Matrix (std::istream& input, int n_) : n(n_) {
		A = new float* [n];
		for (int i = 0; i < n; i++) {
			A[i] = new float [n + 1];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n + 1; j++) {
				input >> A[i][j];
			}
		}

		det = det_(A, n);
	}

	Matrix& Matrix::operator= (Matrix&& m) {
		if (&m == this) {
			return *this;
		}

		for(int i = 0; i < n; i++){
			delete[] A[i];
		}

		n = m.n;
		det = m.det;

		for (int i = 0; i < n; i++) {
			A[i] = m.A[i];
		}

		for(int i = 0; i < n; i++){
			m.A[i] = nullptr;
		}

		return *this;
	}

	bool Matrix::main_diagonal() const { //проверка на то, являются ли элементы главной диагонали нулевыми (можно ли на них делить)
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n + 1; j++){
				if (i == j){
					if (A[i][j] == 0)
						return false;
				}
			}
		}
		return true;
	}

	std::pair<float**, int> Matrix::GetA() const {
		float **A_copy = new float* [n];

		for (int i = 0; i < n; i++) {
			A_copy[i] = new float [n + 1];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n + 1; j++) {
				A_copy[i][j] = A[i][j];
			}
		}

		return std::make_pair(A_copy, n);
	}

	float Matrix::GetD() const { return det; }

	bool Matrix::joint() const { return (det != 0); }

	Matrix::~Matrix(){
		for (int i = 0; i < n; i++) {
			delete [] A[i];
		}
	}

std::ostream& operator<< (std::ostream &out, const Matrix& matrix){
	bool first = true;
	for (int i = 0; i < matrix.n; i++){
		if (!first)
			out << std::endl;

		for (int j = 0; j < matrix.n + 1; j++){
			std::cout << std::setw(6);
			std::cout << std::fixed << std::setprecision(2);
			out << matrix.A[i][j] << " ";
		}

		first = false;
	}
	return out;
}
