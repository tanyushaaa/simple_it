#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <utility>
///////////////////////////////  � � � � � � � � � � � �  //////////////////////////////

float det_(float **T, int N);
///////////////////////////////  � � � � �  � � � � � �  ///////////////////////////////

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
	int n; //���-�� �����������
	float** A = nullptr;
	float det;
};

