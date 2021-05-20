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

float vec_i(std::pair<float**, int> mtrx){ //норма вектора согласованная с нормой по строкам
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

float vec_j(std::pair<float**, int> mtrx){ //норма вектора согласованная с нормой по столбцам
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
	for (int i = 0; i < m.second; i++){ 		//оставляем справа только элементы главной диагонали
		divisor = m.first[i][i]; 				//на которые делим оставшиеся коэф-ты
		for (int j = 0; j < m.second + 1; j++){ //остальное (в тч и 0 при эл-тах главной диагонали) переносим влево (меняем знак)
			massiv[i][j] = (i == j) ? 0 :			//слева оставляем столбец свободных членов (оставляем знак)
							((j == m.second) ?
							m.first[i][j] / divisor : //все делим на единственный правый эл-т,
						  - m.first[i][j] / divisor); //чтобы справа осталась единица
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

//	float i_m_norm = norm_i(M);//глядя в лекцию и Черкасова параллельно,
//	float j_m_norm = norm_j(M);//не поняла, зачем мне строки 87-93 и соответствующие функции
//
//	float m_norm = std::min(i_m_norm, j_m_norm);
//	float v_norm = (m_norm == i_m_norm) ? vec_i(M) : vec_j(M);

//	float estimation = m_norm * v_norm / ( 1 - m_norm );//в Черкасове считается, а в лк нет

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
