#include <iostream>
#include<bits/stdc++.h>
#include <cstdlib>
using namespace std;


namespace Matrix{

	vector<vector<double>> RandomInit(int linha, int coluna){
		random_device rd;
		mt19937 gen(rd());

		uniform_real_distribution<> dis(0, 1);
		vector<vector<double>> matrix(linha, vector<double> (coluna));
		for(int i=0; i<linha; i++){
			for(int j=0; j<coluna; j++)
				matrix[i][j] = dis(gen);
		}
		return matrix;
	}

	vector<vector<double>> MatSoma(vector<vector<double>> matrix1, vector<vector<double>> matrix2){
		
		vector<vector<double>> resultado(matrix1.size(), vector<double> (matrix1[0].size()));
		if(matrix1.size() == matrix2.size() && matrix1[0].size() == matrix2[0].size()){
			for(int i=0; i<matrix1.size(); i++)
				for(int j=0; j<matrix1[0].size(); j++)
					resultado[i][j] = matrix1[i][j] + matrix2[i][j];
		}
		return resultado;
	}

	vector<vector<double>> MatSub(vector<vector<double>> matrix1, vector<vector<double>> matrix2){
		
		vector<vector<double>> resultado(matrix1.size(), vector<double> (matrix1[0].size()));
		if(matrix1.size() == matrix2.size() && matrix1[0].size() == matrix2[0].size()){
			for(int i=0; i<matrix1.size(); i++)
				for(int j=0; j<matrix1[0].size(); j++)
					resultado[i][j] = matrix1[i][j] - matrix2[i][j];
		}
		return resultado;
	}

	vector<vector<double>> SomaEsc(vector<vector<double>> matrix1, double n){

		vector<vector<double>> resultado(matrix1.size(), vector<double> (matrix1[0].size()));
		for(int i=0; i<matrix1.size(); i++)
			for(int j=0; j<matrix1[0].size(); j++)
				resultado[i][j] = matrix1[i][j] + n;	
		return resultado;
	}

	vector<vector<double>> SubEsc(vector<vector<double>> matrix1, double n){

		vector<vector<double>> resultado(matrix1.size(), vector<double> (matrix1[0].size()));
		for(int i=0; i<matrix1.size(); i++)
			for(int j=0; j<matrix1[0].size(); j++)
				resultado[i][j] = matrix1[i][j] - n;	
		return resultado;
	}

	vector<vector<double>> MultEsc(vector<vector<double>> matrix1, double n){

		vector<vector<double>> resultado(matrix1.size(), vector<double> (matrix1[0].size()));
		for(int i=0; i<matrix1.size(); i++)
			for(int j=0; j<matrix1[0].size(); j++)
				resultado[i][j] = matrix1[i][j] * n;
		return resultado;
	}

	vector<vector<double>> DivEsc(vector<vector<double>> matrix1, double n){

		vector<vector<double>> resultado(matrix1.size(), vector<double> (matrix1[0].size()));
		for(int i=0; i<matrix1.size(); i++)
			for(int j=0; j<matrix1[0].size(); j++)
				resultado[i][j] = matrix1[i][j] / n;
		return resultado;
	}

	vector<vector<double>> MulMat(vector<vector<double>> matrix1, vector<vector<double>> matrix2){
		double acu = 0;
		vector<vector<double>> resultado(matrix1.size(), vector<double> (matrix2[0].size()));
		if(matrix1[0].size() == matrix2.size()){
			for(int i=0; i < matrix1.size(); i++){
				for(int j=0; j < matrix2[0].size(); j++){
					acu = 0;
					for (int n=0; n < matrix1[0].size(); n++){
						acu += matrix1[i][n] * matrix2[n][j];
					}
					resultado[i][j] = acu;
				}
			}
		
		}
		return resultado;
	}

	vector<vector<double>> MatExp(vector<vector<double>> matrix){
		vector<vector<double>> retorno(matrix.size(), vector<double> (matrix[0].size()));
		for (int i=0; i < matrix.size(); i++){
			for(int j=0; j < matrix[0].size(); j++){
				retorno[i][j] = exp(matrix[i][j]);
			}	
		}
		return retorno;
	}

	vector<vector<double>> MatLog(vector<vector<double>> matrix){
		vector<vector<double>> retorno(matrix.size(), vector<double> (matrix[0].size()));
		for (int i=0; i < matrix.size(); i++){
			for(int j=0; j < matrix[0].size(); j++){
				retorno[i][j] = log(matrix[i][j]);
			}	
		}
		return retorno;
	}

	vector<vector<double>> SumLine(vector<vector<double>> matrix){
		vector<vector<double>> retorno(matrix.size(), vector<double> (1));
		double acu = 0;
		for(int i=0; i < matrix.size(); i++){
			acu = 0;
			for(int j=0; j<matrix[0].size(); j++){
				acu += matrix[i][j];
			}
			retorno[i][0] = acu;
		}
		
		return retorno;
	}
	vector<vector<double>> SumCol(vector<vector<double>> matrix){
		vector<vector<double>> retorno(1, vector<double> (matrix[0].size()));
		double acu = 0;
		for(int i=0; i < matrix[0].size(); i++){
			acu = 0;
			for(int j=0; j<matrix.size(); j++){
				acu += matrix[j][i];
			}
			retorno[0][i] = acu;
		}

		return retorno;
	}

	double Sum(vector<vector<double>> matrix){
		double retorno = 0;

		for(int i=0; i<matrix.size(); i++){
			for(int j=0; j<matrix[0].size(); j++){
				retorno += matrix[i][j];
			}
		}
		return retorno;
	}

}


namespace Activation{
	vector<vector<double>> Softmax(vector<vector<double>> matrix){
		vector<vector<double>> retorno(matrix.size(), vector<double> matrix[0].size()), exp=Mastrix.MatExp(matrix);
		for(int i=0; i<matrix.size(); i++){
			for(int j=0; j<matrix[0].size(); j++){
				retorno[i][j] = exp[i][j]/Matrix.SumLine(exp)[i][0];
			}
		}
	}
	return retorno;

}


int main(){
	vector<vector<double>> matrix, ;
	int linha, coluna;
	cin >> linha >> coluna;
	matrix = Matrix::RandomInit(matrix);
	cout.precision(5);
	for (int i = 0; i < matrix.size(); i++) { 
        for (int j = 0; j < matrix[0].size(); j++){ 
            cout << fixed << matrix[i][j]<< " "; 
        } 
        cout<< "\n"; 
    }
	matrix = Activation::Softmax(matrix)

	

	//matrix2 = Matrix::MatLog(matrix2);
	for (int i = 0; i < matrix2.size(); i++) { 
        for (int j = 0; j < matrix2[0].size(); j++){ 
            cout << fixed << matrix2[i][j]<< " "; 
        } 
        cout<< "\n"; 
    }

}
