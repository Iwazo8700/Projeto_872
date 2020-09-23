#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/MatrixFunctions>
#include <cmath>

using namespace Eigen;

double Exp(double x){
	return std::exp(x);
}

double Log(double x){
	return std::log(x);
}

MatrixXd LogSoftmax(MatrixXd x){
	MatrixXd retorno;
	return (x/(x.unaryExpr(&Exp).rowwise().sum()));
}

int main(){
	
	Matrix2d m;
	MatrixXd n;
	m << 1, 2,
		 3, 4;
	std::cout << m << std::endl;
	n = LogSoftmax(m);
	std::cout << n << std::endl;	

	return 0;
}




