#include "Keyboard.hpp"



Keyboard::Keyboard(std::shared_ptr<Bloco> bloco){
	this->state = SDL_GetKeyboardState(nullptr); // estado do teclado
	this->bloco = bloco;
}

void Keyboard::set_bloco(std::shared_ptr<Bloco> bloco){
	this->bloco = bloco;
}

std::vector<std::vector<bool>> Keyboard::Rotation(){
	if(Rot_atraso){
		Rot_atraso = false;
		return bloco->get_formato();
		
	}
	Rot_atraso = true;
	SDL_PumpEvents();
	if (state[SDL_SCANCODE_UP]) return RotAnti();
	if (state[SDL_SCANCODE_DOWN]) return RotHoraria();
	return bloco->get_formato();


}


int Keyboard::Desloc(){
	if(Desloc_atraso){
		Desloc_atraso = false;
		return bloco->get_x();
		
	}
	Desloc_atraso = true;
	SDL_PumpEvents(); // atualiza estado do teclado
	if (state[SDL_SCANCODE_LEFT]) return bloco->get_x()-1;
	if (state[SDL_SCANCODE_RIGHT]) return bloco->get_x()+1;
	return bloco->get_x();
}


int Keyboard::Space(std::shared_ptr<Collision> collision){
	if(Space_atraso){
		Space_atraso = false;
		return bloco->get_y();
		
	}
	Space_atraso = true;
	SDL_PumpEvents();
	if(state[SDL_SCANCODE_SPACE]) return Down(collision);
	return bloco->get_y();
	
}

bool Keyboard::Quit(){
	while (SDL_PollEvent(&evento)){ 
    		if (evento.type == SDL_QUIT) return true;
		//if(evento.type == SDL_KEYUP) RotHoraria(bloco); 
      		//if(evento.type == SDL_KEYDOWN) RotAnti(bloco);
		// Exemplos de outros eventos.
      		// Que outros eventos poderiamos ter e que sao uteis?
      		//if (evento.type == SDL_KEYDOWN) {
      		//}
      		//if (evento.type == SDL_MOUSEBUTTONDOWN) {
      		//}
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
		bloco->set_y(bloco->get_y() + 1);
	//std::cout << bloco->get_y() <<std::endl;
	return bloco->get_y() - 1;

}


