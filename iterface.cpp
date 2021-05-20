#include "interface.h"

int interface() {
	std::cout << "Hello!" << std::endl
			  << "This program can calculate a system of linear algebraic equations," << std::endl
			  << "using the simple iteration method." << std::endl
			  << "You should be careful, because only if the determinant of the system matrix is not zero," << std::endl
			  << "the system will have a single solution." << std::endl
			  << "This program will check it itself." << std::endl
			  << "What do you want to do? (click the appropriate button)" << std::endl
			  << "1 - see an example (6 rgr option)" << std::endl
			  << "2 - enter the system matrix from the keyboard" << std::endl
			  << "3 - read the system matrix from the file" << std::endl;
	int cnt;
	std::cin >> cnt;

	Matrix matrix_;

	if (cnt == 2 || cnt == 3){
		std::cout << "Please, enter the number of variables:" << std::endl;

		int n;
		std::cin >> n;

		switch(cnt) {
		case 2:
			std::cout << "Please enter the " << n * (n + 1) << " elements in rows, separated by spaces/enterers:" << std::endl;
			matrix_ = Matrix(std::cin, n);
			break;
		case 3:
			std::cout << "Please, enter the file name with the extension (the file must be located in the project folder):" << std::endl;
			std::string filename;   //если вводить просто имя.расширение - док должен лежать в файле проекта/экзешника
			fflush(stdin);			//если вводить путь файла целиком, нужно разделять путь двойными слэшами, зато лежать может где-угодно
			std::getline(std::cin, filename);//считывание имени файла с пробелами
			std::ifstream matrix_file(filename);
			if (!matrix_file.is_open()){
				throw std::runtime_error("file is not open");
			}
			matrix_ = Matrix(matrix_file, n);
			matrix_file.close();
			break;
		}
	} else if (cnt != 1) {
		std::cout << "You have entered incorrect num" << std::endl;
	}

	std::cout << "Your matrix:" << std::endl << matrix_ << std::endl;
	try {
		float* answer = new float [matrix_.GetA().second];
		answer = sim(matrix_);
		std::cout << "Answer:" << std::endl;
		for (int i = 0; i < matrix_.GetA().second; i++){
			std::cout << std::setw(4) << "x[" << i << "] = " << std::setw(10)
					<< std::fixed << std::setprecision(7) << answer[i] << std::endl;
		}
	} catch (std::logic_error& le) {
		std::cerr << le.what() << std::endl;
	}

	return 0;
}
