#pragma once

#include <vector>
#include <memory>
#include "Bloco.hpp"
#include "Keyboard.hpp"

/*! \brief Classe Player
*
* Classe responsável por armazenar as informações relacionadas a cada jogador.
*
*/

class Player{
	private:
		std::shared_ptr<Bloco> piece; /*<! Bloco que o Player está controlando*/
		std::shared_ptr<Keyboard> keyboard; /*<! Keyboard com o controle do Player*/
		int points; /*<! Pontuação do Player*/
		int speed; /*<! Tempo em ms para a peça cair automáticamente uma posição*/
		unsigned int time; /*<! Guarda o tempo última vez que a peça caiu uma posição automaticamente*/
		bool alive; /*<! Variável que indica se o Player perdeu o jogo ou não*/
	public:
		/*! \brief Construtor da classe Player
		*
		* Inicializa as variáveis internas do Player
		*
		* \param std::shared_ptr<Bloco> piece Peça que o Player controla
		* \param std::shared_ptr<Keyboard> keyboard Keyboard contendo a entrada do teclado do Player
		* \param int speed Tempo para a peça cair um bloco automaticamente
		* \return Nada (é um Construtor)
		*/
		Player(std::shared_ptr<Bloco> piece, std::shared_ptr<Keyboard> keyboard, int speed);
		void set_piece(std::shared_ptr<Bloco> piece);
		void set_keyboard(std::shared_ptr<Keyboard> keyboard);
		/*!
		* Adiciona um valor à velocidade do Player
		* \int speed Valor que será adicionado à velocidade
		* \return Nada
		*/
		void increase_speed(int speed);
		/*!
		* Adiciona um valor à pontuação do Player
		* \int points Valor que será adicionado à pontuação
		* \return Nada
		*/
		void add_points(int points);
		void set_time(unsigned int time);	

		std::shared_ptr<Bloco> get_piece();
		std::shared_ptr<Keyboard> get_keyboard();
		int get_points();
		int get_speed();
		unsigned int get_time();
		/*! Retorna se o Player está vivo ainda ou não
		*
		* \return bool true se o Player está vivo e false caso contrário
		*/
		bool is_alive();
		/*! Mata o Player (define alive = false)
		* \return Nada
		*/
		void kill();
};
