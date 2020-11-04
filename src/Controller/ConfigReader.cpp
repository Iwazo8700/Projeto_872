#include "ConfigReader.hpp"

ConfigReader::ConfigReader(const char* config_file){
	std::string text;
	
	std::fstream file(config_file, std::fstream::in);

	this->shift_x = -1;
	this->shift_y = -1;
	this->block_size_x = -1;	
	this->block_size_y = -1;

	this->screen_width=440; 
	this->screen_height=440;
	this->lines=20; 
	this->columns=10; 
	this->speed=500; 
	this->delay=20; 
	this->decrease=50;
	this->decrease_n=10;
	this->keyboard_time=50;

	while(getline(file, text)){
		if(text.size() == 0 || text.at(0) == '#')
			continue;
		else if(text.find("screen_width") != std::string::npos)
			this->screen_width = this->get_value(text);
		else if(text.find("screen_height") != std::string::npos)
			this->screen_height = this->get_value(text);
		else if(text.find("lines") != std::string::npos)
			this->lines = this->get_value(text);
		else if(text.find("columns") != std::string::npos)
			this->columns = this->get_value(text);
		else if(text.find("speed") != std::string::npos)
			this->speed = this->get_value(text);
		else if(text.find("shift_x") != std::string::npos)
			this->shift_x = this->get_value(text);
		else if(text.find("shift_y") != std::string::npos)
			this->shift_y = this->get_value(text);
		else if(text.find("delay") != std::string::npos)
			this->delay = this->get_value(text);
		else if(text.find("keyboard_time") != std::string::npos)
			this->keyboard_time = this->get_value(text);
		else if(text.find("decrease") != std::string::npos)
			this->decrease = this->get_value(text);
		else if(text.find("number_dec") != std::string::npos)
			this->decrease_n = this->get_value(text);
		else if(text.find("block_size_x") != std::string::npos)
			this->block_size_x = this->get_value(text);
		else if(text.find("block_size_y") != std::string::npos)
			this->block_size_y = this->get_value(text);
	}
	if(this->block_size_x == -1)
		this->block_size_x = this->screen_width/(2*this->columns+2);
	if(this->block_size_y == -1)
		this->block_size_y = this->screen_height/(this->lines+2);
	if(this->shift_x == -1)
		this->shift_x = this->block_size_x;
	if(this->shift_y == -1)
		this->shift_y = this->block_size_y;
}

int ConfigReader::get_keyboard_time(){
	return this->keyboard_time;
}

int ConfigReader::get_decrease(){
	return this->decrease;
}

int ConfigReader::get_decrease_n(){
	return this->decrease_n;
}

int ConfigReader::get_value(std::string text){
	std::size_t first_num = text.find_first_of("0123456789"); 
	std::size_t last_num = text.find_last_of("0123456789"); 
	return std::stoi(text.substr(first_num, last_num-first_num+1));
}

int ConfigReader::get_screen_width(){
	return this->screen_width;
}

int ConfigReader::get_screen_height(){
	return this->screen_height;
}
	
int ConfigReader::get_lines(){
	return this->lines;
}

int ConfigReader::get_block_size_x(){
	return this->block_size_x;
}

int ConfigReader::get_block_size_y(){
	return this->block_size_y;
}

int ConfigReader::get_columns(){
	return this->columns;
}
	
int ConfigReader::get_speed(){
	return this->speed;
}

int ConfigReader::get_shift_x(){
	return this->shift_x;
}

int ConfigReader::get_shift_y(){
	return this->shift_y;
}	

int ConfigReader::get_delay(){
	return this->delay;
}
