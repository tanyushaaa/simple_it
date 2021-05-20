#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <utility>
///////////////////////////////  О п р е д е л и т е л ь  //////////////////////////////

float det_(float **T, int N);
///////////////////////////////  К л а с с  м а т р и ц  ///////////////////////////////

class Matrix {
public:
	Matrix();
	Matrix (std::istream& input, int n_);
	Matrix& operator= (Matrix&& m);
	bool main_diagonal() const;
	std::pair<float**, int> GetA() const;
	float GetD() const;
	bool joint() const;
	~Matrix();
	friend std::ostream& operator<< (std::ostream &out, const Matrix& matrix);
private:
	int n; //кол-во неизвестных
	float** A = nullptr;
	float det;
};

