#include "sim.h"

float epsilon = 0.01;

float norm_i(std::pair<float**, int> mtrx){
	std::vector<float> mas;
	for (int i = 0; i < mtrx.second; i++){
		mas.push_back(0);
		for (int j = 0; j < mtrx.second; j++){
			mas[i] += mtrx.first[i][j];
		}
	}
	return *std::max_element(mas.begin(), mas.end());
}

float vec_i(std::pair<float**, int> mtrx){ //����� ������� ������������� � ������ �� �������
	std::vector<float> mas;
	for (int i = 0; i < mtrx.second; i++){
		mas.push_back(abs(mtrx.first[i][mtrx.second]));
	}
	return *std::max_element(mas.begin(), mas.end());
}

float norm_j(std::pair<float**, int> mtrx){
	std::vector<float> mas;
	for (int i = 0; i < mtrx.second; i++){
		mas.push_back(0);
		for (int j = 1; j < mtrx.second; j++){
			mas[i] += mtrx.first[j][i];
		}
	}
	return *std::max_element(mas.begin(), mas.end());
}

float vec_j(std::pair<float**, int> mtrx){ //����� ������� ������������� � ������ �� ��������
	float norm = 0;
	for (int i = 0; i < mtrx.second; i++){
		for (int j = 1; j < mtrx.second; j++){
			norm += abs(mtrx.first[i][mtrx.second]);
		}
	}
	return norm;
}

float norm(float* vec1, float* vec2, int n){
	float sum = 0;
	for (int i = 0; i < n; i++){
		sum += fabs(vec1[i] - vec2[i]);
	}
	return sum;
}

std::pair<float**, int> new_mtrx(std::pair<float**, int> m, float* x){
	float** massiv = new float* [m.second];
	for (int i = 0; i < m.second; i++){
		massiv[i] = new float [m.second + 1];
	}

	float divisor = 0;
	for (int i = 0; i < m.second; i++){ 		//��������� ������ ������ �������� ������� ���������
		divisor = m.first[i][i]; 				//�� ������� ����� ���������� ����-��
		for (int j = 0; j < m.second + 1; j++){ //��������� (� �� � 0 ��� ��-��� ������� ���������) ��������� ����� (������ ����)
			massiv[i][j] = (i == j) ? 0 :			//����� ��������� ������� ��������� ������ (��������� ����)
							((j == m.second) ?
							m.first[i][j] / divisor : //��� ����� �� ������������ ������ ��-�,
						  - m.first[i][j] / divisor); //����� ������ �������� �������
		}
		x[i] = massiv[i][m.second];
	}
	return std::make_pair(massiv, m.second);
}

float* iter_proc (std::pair<float**, int> m, float* x) {
	float* X = static_cast<float*>(calloc(m.second, sizeof(float)));
	for(int i = 0; i < m.second; i++){
		for(int j = 0; j < m.second + 1; j++){
			X[i] += (j != m.second) ? m.first[i][j] * x[j] : m.first[i][j];
		}
//		std::cout << std::fixed << std::setprecision(4) << X[i] << std::endl;
	}

//	std::pair<float**, int> M = std::make_pair(m, m.second);

//	float i_m_norm = norm_i(M);//����� � ������ � ��������� �����������,
//	float j_m_norm = norm_j(M);//�� ������, ����� ��� ������ 87-93 � ��������������� �������
//
//	float m_norm = std::min(i_m_norm, j_m_norm);
//	float v_norm = (m_norm == i_m_norm) ? vec_i(M) : vec_j(M);

//	float estimation = m_norm * v_norm / ( 1 - m_norm );//� ��������� ���������, � � �� ���

	if(norm(X, x, m.second) > epsilon){
		return iter_proc(m, X);
	}
	return X;
}

float* sim(const Matrix& matrix){
	int n = matrix.GetA().second;

	float* x = new float [n];
	return iter_proc(new_mtrx(matrix.GetA(), x), x);
}
