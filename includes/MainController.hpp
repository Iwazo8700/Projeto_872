#pragma once

#include "Formato.hpp"
#include "Bloco.hpp"
#include "Map.hpp"
#include "Image.hpp"
#include "BlockPosition.hpp"
#include "Collision.hpp"
#include "Keyboard.hpp"
#include "Player.hpp"
#include "IAFunctions.hpp"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

/*! \brief Classe MainController
*
* Classe responsável pelo controle geral do jogo, controlando cada passo.
*
*/

class MainController{
	private:
		std::shared_ptr<Formato> formats; /*<! Formats contendo todos os formatos possíveis para as peças*/
		std::shared_ptr<Map> map; /*<! Ponteiro para o Map que será usado*/
		std::shared_ptr<Collision> collision; /*<! Collision que verificará colisões*/
		std::vector<std::shared_ptr<Player>> players; /*<! Lista com todos os Players presentes*/
		std::vector<std::shared_ptr<IAFunctions>> iafunc_vec;
	public:
		/*! \brief Construtor da MainController
		*
		* Inicializa todas as variáveis internas da classe
		*
		* \param std::shared_ptr<Map> map Mapa do jogo já alocado
		* \param std::vector<std::shared_ptr<Player>> players Lista com todos os players do jogo já alocado
		* \param std::shared_ptr<Formato> formato Instância já alocada do objeto contendo todas as formas possíveis para uma peça
		*/
		MainController(std::shared_ptr<Map> map, std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Formato> formato);
		/*! \brief Construtor da MainController para IA
		*
		* Inicializa todas as variáveis internas da classe
		*
		* \param std::shared_ptr<Map> map Mapa do jogo já alocado
		* \param std::vector<std::shared_ptr<Player>> players Lista com todos os players do jogo já alocado
		* \param std::shared_ptr<Formato> formato Instância já alocada do objeto contendo todas as formas possíveis para uma peça
		* \param std::vector<std::shared_ptr<IAFuntions>> iafunc_vec Vetor com os objetos controlados pela IA
		*/
		MainController(std::shared_ptr<Map> map, std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Formato> formato, std::vector<std::shared_ptr<IAFunctions>> iafunc_vec);
		/*! \brief Verifica se a peça do Player deve cair um bloco automaticamente.
		* Verifica usando os atributos speed e time do Player além do tempo atual para verificar se o tempo entre os movimentos já passou, de modo
		* que a peça deveria cair mais um bloco.
		*
		* \param std::shared_ptr<Player> player Jogador para o qual será verificado
		* \return bool true se a peça deveria cair um bloco e false caso contrário
		*/
		bool should_move(std::shared_ptr<Player> player);
		/* \brief Executa um passo do programa
		*
		* Atualiza as posições dos Jogadores com base no tempo decorrido e nas teclas apertadas. 
		* Atualiza o mapa, excluindo as linhas completas e adicionando novas vazias.
		* Fixa o bloco do Player quando necessário e cria um novo aleatório para ele.
		* Verifica os Players que perderam
		*
		* \return Nada
		*/
		void step();
		/*! \brief Cria um Bloco com um formato aleatório entre os fornecidos pelo format
		*
		* \param int x, y Posições x,y correspondentes à linha e à coluna do Bloco sendo gerado
		* \param int height,width Altura e largura em px do bloco sendo gerado
		* \param std::shared_ptr<Sprite> sprite Sprite contendo a textura desejada para o Bloco 
		* \return std::shared_ptr<Bloco> ponteiro para o Bloco aleatório gerado
		*/
		std::shared_ptr<Bloco> create_random_block(int x, int y, int height, int width, std::shared_ptr<Sprite> sprite);
		void set_players(std::vector<std::shared_ptr<Player>> player);
		/*! \brief Exclui as linhas completas (todos valores dela diferentes de 0) do mapa e insere novas linhas vazias
		*
		* \return int Número de linhas completas que foram excluídas
		*
		*/
		int update_board();
		/*! \brief Verifica se um Player perdeu
		*
		* Verifica se a peça do Player se fixou em uma posição que faça com que ela passe do limite superior do mapa,
		* implicando que o Player perdeu
		*
		* \param std::shared_ptr<Player> player Jogador para o qual se verificará se perdeu
		* \return bool Retorna true se o Player deveria perder e false caso contrário
		*/	
		bool is_dead(std::shared_ptr<Player> player);

		void IAstep();
};
