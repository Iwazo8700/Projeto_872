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
}

void Keyboard::set_bloco(std::shared_ptr<Bloco> bloco){
	this->bloco = bloco;
}

std::vector<std::vector<bool>> Keyboard::Rotation(){
	if(this->time_rot+this->delay<=SDL_GetTicks()){
		this->time_rot = SDL_GetTicks();
		SDL_PumpEvents();
		if (state[SDL_SCANCODE_UP]) return RotAnti();
		if (state[SDL_SCANCODE_DOWN]) return RotHoraria();
	}
	return bloco->get_formato();


}


int Keyboard::Desloc(){
	if(this->time_des+this->delay<=SDL_GetTicks()){
		this->time_des = SDL_GetTicks();
		SDL_PumpEvents(); // atualiza estado do teclado
		if (state[SDL_SCANCODE_LEFT]) return bloco->get_x()-1;
		if (state[SDL_SCANCODE_RIGHT]) return bloco->get_x()+1;
	}
	return bloco->get_x();
}

int Keyboard::Desloc_Vert(){
	if(this->time_ver+this->delay<=SDL_GetTicks()){
		this->time_ver = SDL_GetTicks();
		SDL_PumpEvents(); // atualiza estado do teclado
		if (state[SDL_SCANCODE_S]) return bloco->get_y()+this->num_lines;
	}
	return bloco->get_y();
}

int Keyboard::Space(std::shared_ptr<Collision> collision){
	if(this->time_space+this->delay <= SDL_GetTicks()){
		this->time_space = SDL_GetTicks();
		SDL_PumpEvents();
		if(state[SDL_SCANCODE_SPACE]) {
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
	return this->bloco->get_y() - 1;

}


