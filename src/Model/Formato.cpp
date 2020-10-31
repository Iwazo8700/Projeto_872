#include "Formato.hpp"


Formato::Formato(char const *dir){
	std::ifstream MyReadFile(dir);
	std::string line;
	std::vector<std::vector<bool>> format;
	std::vector<bool> format_line;
	while (getline(MyReadFile, line)) {
 	 // Output the text from the file
	 	 std::cout << line << std::endl;
 		 if(line == "\n"){
		 	this->formatos.push_back(format);
			format.clear();
		 }
		 else{
		 	for(int i=0; i<line.length(); i++){
				format_line.push_back(line[i]=='1');
			}
			format.push_back(format_line);
		 	format_line.clear();
		 }

	}
	for(int i=0; i<formatos.size(); i++){
		for (int j=0; j<formatos[i].size(); j++){
			for(int k=0; k<formatos[i][j].size(); k++){
				std::cout << this->formatos[i][j][k] << ' ';
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}
}


std::vector<std::vector<bool>> Formato::get_I(){
	return this->formatos[0];
}

std::vector<std::vector<bool>> Formato::get_J(){
	return this->formatos[1];
}

std::vector<std::vector<bool>> Formato::get_L(){
	return this->formatos[2];
}

std::vector<std::vector<bool>> Formato::get_O(){
	return this->formatos[3];
}

std::vector<std::vector<bool>> Formato::get_S(){
	return this->formatos[4];
}

std::vector<std::vector<bool>> Formato::get_T(){
	return this->formatos[5];
}

std::vector<std::vector<bool>> Formato::get_Z(){
	return this->formatos[6];
}



