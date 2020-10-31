#include "Formato.hpp"

Formato::Formato(){}


vector<vector<int>> get_Formato_I(){
	vector<vector<int>> I(4, 4);
	I = 	[[0,0,0,0,
		  1,1,1,1,
		  0,0,0,0,
		  0,0,0,0],

		 [0,0,1,0,
		  0,0,1,0,
		  0,0,1,0,
		  0,0,1,0],

		 [0,0,0,0,
		  0,0,0,0,
		  1,1,1,1,
		  0,0,0,0],

		 [0,1,0,0,
		  0,1,0,0,
		  0,1,0,0
		  0,1,0,0]]

	return I;
}
vector<vector<int>> get_Formato_O(){
	vector<vector<int>> O(4,4);
	O = 	[[0,1,1,0,
		  0,1,1,0,
		  0,0,0,0,
		  0,0,0,0],

		 [0,1,1,0,
		  0,1,1,0,
		  0,0,0,0,
		  0,0,0,0],

		 [0,1,1,0,
		  0,1,1,0,
		  0,0,0,0,
		  0,0,0,0],

		 [0,1,1,0,
		  0,1,1,0,
		  0,0,0,0,
		  0,0,0,0]]
	return O;
}
vector<vector<int>> get_Formato_J(){
	vector<vector<int>> J(3,3);
	J = 	[[1,0,0,
		  1,1,1,
		  0,0,0,],
		
		 [0,1,1,
		  0,1,0,
		  0,1,0,],

		 [0,0,0,
		  1,1,1,
		  0,0,1,],

		 [0,1,0,
		  0,1,0,
		  1,1,0,]]
	return J;
}

vector<vector<int>> get_Formato_L(){
	vector<vector<int>> L(3,3);
	L = 	[[0,0,1,
		  1,1,1,
		  0,0,0,],
		
		 [0,1,0,
		  0,1,0,
		  0,1,1,],

		 [0,0,0,
		  1,1,1,
		  1,0,0,],

		 [1,1,0,
		  0,1,0,
		  0,1,0,]]
	return L;
}

vector<vector<int>> get_Formato_S(){
	vector<vector<int>> S(3,3);
	S = 	[[0,1,1,
		  1,1,0,
		  0,0,0,],
		
		 [0,1,0,
		  0,1,1,
		  0,0,1,],

		 [0,0,0,
		  0,1,1,
		  1,1,0,],

		 [1,0,0,
		  1,1,0,
		  0,1,0,]]
	return S;
}

vector<vector<int>> get_Formato_Z(){
	vector<vector<int>> Z(3,3);
	Z = 	[[1,1,0,
		  0,1,1,
		  0,0,0,],
		
		 [0,0,1,
		  0,1,1,
		  0,1,0,],

		 [0,0,0,
		  1,1,0,
		  0,1,1,],

		 [0,1,0,
		  1,1,0,
		  1,0,0,]]
	return Z;
}

vector<vector<int>> get_Formato_T(){
	vector<vector<int>> T(3,3);
	T = 	[[0,1,0,
		  1,1,1,
		  0,0,0,],
		
		 [0,1,0,
		  0,1,1,
		  0,1,0,],

		 [0,0,0,
		  1,1,1,
		  0,1,0,],

		 [0,1,0,
		  1,1,0,
		  0,1,0,]]
	return T;
}


