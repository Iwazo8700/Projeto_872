#pragma once

#include "json.hpp"
#include <vector>
#include <memory>
#include "Bloco.hpp"
#include "Sprite.hpp"

using nlohmann::json;

/*! \brief Classe Map
*
* Classe responsável por armazenar o mapa do jogo e suas informações
*
*/

class Map{
	private:
		std::vector<std::vector<int>> map; /*<! Matriz representado o mapa*/
		int block_width; /*<! Largura de cada bloco do mapa (em px)*/
		int block_height; /*<! Altura de cada bloco do mapa (em px)*/
		int height; /*<! Número de linhas no mapa*/
		int width; /*<! Número de colunas no mapa*/
		std::vector<std::shared_ptr<Sprite>> sprites; /*<! Sprite contendo a textura de cada bloco do mapa*/
	public:
		/*! \brief Construtor da classe Map
		*
		* Inicializa as variáveis internas da classe
		* 
		* \param int height,width Número de linhas e colunas do mapa
		* \param int block_height, block_width Altura e largura em px de cada bloco do mapa
		* \return Nada (é um construtor)
		*/
		Map(int height, int width, int block_height, int block_width);
		Map(int height, int width);
		Map(){};
		void set_map(std::vector<std::vector<int>> map);
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Map, map);
		int get_block_width();
		int get_block_height();
		std::vector<std::vector<int>> get_map();

		/*! Adiciona um bloco ao mapa.
		*
		* Coloca na matriz representando o mapa nas posições do Bloco o valor value
		*
		* \param std::shared_ptr<Bloco> block Bloco que será adicionado
		* \param int value Número que será colocado no mapa nas posições ocupadas pelo Bloco
		* \return Nada
		*/
		void add_to_map(std::shared_ptr<Bloco> block, int value);
		std::shared_ptr<Sprite> get_texture(int i, int j);
		std::shared_ptr<Sprite> get_texture(int pos);
		void set_sprites(std::vector<std::shared_ptr<Sprite>> sprites);
		/*!
		* Remove as n últimas linhas da matriz e insere n novas linhas de zeros no seu início
		*
		* \param int n Número de linhas que serão removidas e adicionadas
		* \return Nada
		*/
		void completed_lines(int n);
		/*!
		* Para cada valor no vetor lines, remove a linha correspondente ao valor e adiciona uma linha de zeros no início da matriz
		*
		* \param std::vector<int> line Vetor contendo a posição de cada linha que deve ser excluída
		* \return Nada
		*/
		void completed_lines(std::vector<int> lines);
};
