#include "Keyboard.hpp"



Keyboard::Keyboard(){
	this->state = SDL_GetKeyboardState(nullptr); // estado do teclado
}

bool Keyboard::Read(std::shared_ptr<Bloco> bloco){
	SDL_PumpEvents(); // atualiza estado do teclado
	if (state[SDL_SCANCODE_LEFT]) RotAnti(bloco);
	if (state[SDL_SCANCODE_RIGHT]) RotHoraria(bloco);
	//if (statqe[SDL_SCANCODE_UP]) return;
	//if (state[SDL_SCANCODE_DOWN]) return;
	
	while (SDL_PollEvent(&evento)){ 
    		if (evento.type == SDL_QUIT) return false;
		//if(evento.type == SDL_KEYUP) RotHoraria(bloco); 
      		//if(evento.type == SDL_KEYDOWN) RotAnti(bloco);
		// Exemplos de outros eventos.
      		// Que outros eventos poderiamos ter e que sao uteis?
      		//if (evento.type == SDL_KEYDOWN) {
      		//}
      		//if (evento.type == SDL_MOUSEBUTTONDOWN) {
      		//}
    	}
	return true;

}

void Keyboard::RotHoraria(std::shared_ptr<Bloco> bloco){
	std::vector<std::vector<bool>> peca = bloco->get_formato();
	std::vector<std::vector<bool>> retorno(peca[0].size(), std::vector<bool> (peca.size()));
	for(int i=0; i<peca.size(); i++){
		for(int j=0; j<peca[i].size(); j++){
			retorno[j][retorno[j].size()-1-i] = peca[i][j];
		}
	}
	

	bloco->set_formato(retorno);

}

void Keyboard::RotAnti(std::shared_ptr<Bloco> bloco){
	std::vector<std::vector<bool>> peca = bloco->get_formato();
	std::vector<std::vector<bool>> retorno(peca[0].size(), std::vector<bool> (peca.size()));
	for(int i=0; i<peca.size(); i++){
		for(int j=0; j<peca[i].size(); j++){
			retorno[retorno.size()-1-j][i] = peca[i][j];
		}
	}
	

	bloco->set_formato(retorno);
}





