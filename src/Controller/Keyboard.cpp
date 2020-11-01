#include "Keyboard.hpp"



Keyboard::Keyboard(std::shared_ptr<Bloco> bloco){
	this->state = SDL_GetKeyboardState(nullptr); // estado do teclado
	this->bloco = bloco;
}

void Keyboard::set_bloco(std::shared_ptr<Bloco> bloco){
	this->bloco = bloco;
}

std::vector<std::vector<bool>> Keyboard::Rotation(){
	if (state[SDL_SCANCODE_UP]) return RotAnti();
	if (state[SDL_SCANCODE_DOWN]) return RotHoraria();
	
	return bloco->get_formato();


}


int Keyboard::Desloc(){
	SDL_PumpEvents(); // atualiza estado do teclado
	if (state[SDL_SCANCODE_LEFT]) return bloco->get_x()-1;
	if (state[SDL_SCANCODE_RIGHT]) return bloco->get_x()+1;
	return bloco->get_x();
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





