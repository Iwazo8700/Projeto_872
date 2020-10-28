#pragma once

#include <memory>

/*! \brief
*
* Classe Bloco
* Model responsável por armazenar os dados de um bloco, 
* guardando seu sprite, sua forma e sua posição
* */

class Bloco {
	private:
		int x,y; /*!< Posição do bloco relativo ao mapa*/
		char formato; /*!< Char representando a forma do bloco*/
		std::shared_ptr<Sprite> sprite; /*!< Shared Pointer para Sprite (previamente alocado) que será usada para renderizar o bloco*/

	public:
		/*! \brief Construtor do Bloco
		*
		* Deve receber um char representando o formato do Bloco, 
		* dois ints representando sua posição relativa no mapa e
		* um shared_ptr para um Sprite que será usado para renderiza-lo
		*
		* \param char Um formato
		* \return Nada (este é um construtor!)
		* */
		Bloco(int x, int y, char formato, std::shared_ptr<Sprite> sprite);

		int get_x();
		int get_y();
		char get_formato();
		std::shared_ptr<Sprite> get_sprite();

		void set_x(int x);
		void set_y(int y);
		void set_formato(char formato);
		void set_sprite(std::shared_ptr<Sprite> sprite); 
}
