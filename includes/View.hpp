#pragma once
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL_image.h>
#include "SDL_Model.hpp"
#include "Image.hpp"
#include <vector>

/*! \brief
*
* Classe View
* View responsável por renderizar as imagens na tela
* */

class View {
	private:
		std::shared_ptr<SDL_Model> sdl; /*!< SDL_Model com as informações do renderer e window*/
	public:
		/*! \brief Construtor do View
		*
		* Inicializa o atributo da classe View
		* através do parâmetro recebido
		*
		* \param std::shared_ptr<SDL_Model> sdl 
		* \return Nada (este é um construtor!)
		* */
		View(std::shared_ptr<SDL_Model> sdl);
		/*! \brief Função de render
		*
		* Renderiza na tela as imagens recebidas como parâmetro
		* na ordem em que aparecem no vetor recebido
		*
		* \param std::vector<Images> object
		* \return Nada
		* */
		void render(std::vector<Image> objects);
};

