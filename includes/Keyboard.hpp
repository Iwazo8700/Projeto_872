#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <vector>
#include <iostream>
#include "Bloco.hpp"

/*! \brief
 *
 * Classe Keyboard
 * Controller responsável por ler as infromações do teclado
 * e atualizar a peça
 *
 *
 * */

class Keyboard{
	private:
		SDL_Event evento; // eventos discretos
 		const Uint8* state; // estado do teclado

	public:
		Keyboard();
		bool Read(std::shared_ptr<Bloco> bloco);
		void RotHoraria(std::shared_ptr<Bloco> bloco);
		void RotAnti(std::shared_ptr<Bloco> bloco);

};
