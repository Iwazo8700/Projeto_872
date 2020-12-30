#include "Keyboard.hpp"

Keyboard::Keyboard(std::shared_ptr<Bloco> bloco, int delay = 40, int num_lines=1){
	this->state = SDL_GetKeyboardState(nullptr); // estado do teclado
	this->bloco = bloco;
	this->time_des = 0;
	this->time_rot = 0;
	this->time_ver = 0;
	this->time_space = 0;
	this->delay = delay;
	this->num_lines = num_lines;
	this->pressed_key = NONE;
}

Keyboard::Keyboard(int delay = 40, int num_lines=1){
	this->state = SDL_GetKeyboardState(nullptr); // estado do teclado
	this->time_des = 0;
	this->time_rot = 0;
	this->time_ver = 0;
	this->time_space = 0;
	this->delay = delay;
	this->num_lines = num_lines;
	this->pressed_key = '0';
}

void Keyboard::set_bloco(std::shared_ptr<Bloco> bloco){
	this->bloco = bloco;
}

void Keyboard::update_pressed_key(){
	SDL_PumpEvents();
	if(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
		this->pressed_key = UP;
	else if(state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
		this->pressed_key = DOWN;
	else if(state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A])
		this->pressed_key = LEFT;
	else if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])
		this->pressed_key = RIGHT;
	else if(state[SDL_SCANCODE_SPACE])
		this->pressed_key = SPACE;
	else if(state[SDL_SCANCODE_Q])
		this->pressed_key = ROT_LEFT;
	else if(state[SDL_SCANCODE_E])
		this->pressed_key = ROT_RIGHT;
	else if(state[SDL_SCANCODE_K])
		this->pressed_key = SAVE;
	else if(state[SDL_SCANCODE_L])
		this->pressed_key = LOAD;
	else
		this->pressed_key = NONE;
	
}

char Keyboard::get_pressed_key(){
	return this->pressed_key;
}

void Keyboard::set_pressed_key(char key){
	this->pressed_key = key;
}

std::vector<std::vector<bool>> Keyboard::Rotation(){
	if(this->time_rot+this->delay<=SDL_GetTicks()){
		this->time_rot = SDL_GetTicks();
		if (this->pressed_key == ROT_LEFT) return RotAnti();
		if (this->pressed_key == ROT_RIGHT) return RotHoraria();
	}
	return bloco->get_formato();
}


int Keyboard::Desloc(){
	if(this->time_des+this->delay<=SDL_GetTicks()){
		this->time_des = SDL_GetTicks();
		if (this->pressed_key == LEFT) return bloco->get_x()-1;
		if (this->pressed_key == RIGHT) return bloco->get_x()+1;
	}
	return bloco->get_x();
}

int Keyboard::Desloc_Vert(){
	if(this->time_ver+this->delay<=SDL_GetTicks()){
		this->time_ver = SDL_GetTicks();
		if (this->pressed_key == DOWN) return bloco->get_y()+this->num_lines;
	}
	return bloco->get_y();
}

int Keyboard::Space(std::shared_ptr<Collision> collision, std::vector<std::shared_ptr<Bloco>> others){
	if(this->time_space+this->delay <= SDL_GetTicks()){
		this->time_space = SDL_GetTicks();
		if(this->pressed_key == SPACE) {
			Down(collision, others);
			return 1;
		}
	}
	return 0;
	
}

int Keyboard::Space(std::shared_ptr<Collision> collision){
	if(this->time_space+this->delay <= SDL_GetTicks()){
		this->time_space = SDL_GetTicks();
		if(this->pressed_key == SPACE) {
			Down(collision);
			return 1;
		}
	}
	return 0;
	
}

bool Keyboard::Quit(){
	while (SDL_PollEvent(&evento)){ 
    		if (evento.type == SDL_QUIT) return true;
    	}
	return false;
}

bool Keyboard::Save(){
	if (this->pressed_key == SAVE) return true;

	return false;
}


bool Keyboard::Load(){
	if (this->pressed_key == LOAD) return true;

	return false;
}

std::vector<std::vector<bool>> Keyboard::RotHoraria(){
	std::vector<std::vector<bool>> peca = bloco->get_formato();
	std::vector<std::vector<bool>> retorno(peca[0].size(), std::vector<bool> (peca.size()));
	for(int i=0; i<peca.size(); i++){
		for(int j=0; j<peca[i].size(); j++){
			retorno[j][retorno[j].size()-1-i] = peca[i][j];
		}
	}
	return retorno;

}

std::vector<std::vector<bool>> Keyboard::RotAnti(){
	std::vector<std::vector<bool>> peca = bloco->get_formato();
	std::vector<std::vector<bool>> retorno(peca[0].size(), std::vector<bool> (peca.size()));
	for(int i=0; i<peca.size(); i++){
		for(int j=0; j<peca[i].size(); j++){
			retorno[retorno.size()-1-j][i] = peca[i][j];
		}
	}

	return retorno;
}


int Keyboard::Down(std::shared_ptr<Collision> collision){
	while(!collision->is_colliding(bloco))
		this->bloco->set_y(this->bloco->get_y() + 1);
	this->bloco->set_y(this->bloco->get_y() - 1);
	return this->bloco->get_y();
}

int Keyboard::Down(std::shared_ptr<Collision> collision, std::vector<std::shared_ptr<Bloco>> others){
	while(!collision->is_colliding(bloco) && !collision->is_colliding(bloco,others))
		this->bloco->set_y(this->bloco->get_y() + 1);
	this->bloco->set_y(this->bloco->get_y() - 1);
	return this->bloco->get_y();
}


