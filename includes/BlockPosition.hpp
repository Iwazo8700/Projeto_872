#pragma once

#include <vector>
#include <memory>
#include "Image.hpp"
#include "Bloco.hpp"
#include "Map.hpp"
#include "SDL_Model.hpp"

/*! \brief Classe BlockPosition
*
* Classe responsável por converter a matriz representando o Bloco e o Map para
* vectors de Images contendo cada bloco individual que os compõe, de modo que eles 
* possam ser renderizados
*
* */
class BlockPosition{
	private:
		int x_begin; /*!< Número do pixel x a partir do qual a renderização será realizada*/
		int y_begin; /*!< Número do pixel y a partir do qual a renderização será realizada*/
		std::vector<std::shared_ptr<Sprite>> numbers; /*!< Lista com Sprites para os números de 1 à 10*/
	public:
		/*! \brief Construtor do BlockPosition
		*
		* Deve receber dois ints representando os pixels inicias da porção da tela considerada
		* e inicializa as variáveis internas da classe
		*
		* \param int x, y Coordenadas dos pixels iniciais
		* \param std::shared_ptr<SDL_Model> sdl Dados do sdl
		* \return Nada (este é um construtor!)
		* */
                BlockPosition(int x, int y, std::shared_ptr<SDL_Model> sdl);

		/*! \brief Conversor do Bloco para cada bloco constituinte
		*
		* Converte o formato da peça do Bloco para um vetor de Images correspondendo a cada bloco individual
		*
		* \param std::shared_ptr<Bloco> block Bloco a partir do qual será gerado o vetor
		* \return std::vector<std::shared_ptr<Image>> Vetor de Images correspondendo a cada bloco do Bloco
		* */
		std::vector<std::shared_ptr<Image>> create_image_vector(std::shared_ptr<Bloco> block);
		/*! \brief Conversor do Map para cada bloco constituinte
		*
		* Converte o formato do Map para um vetor de Images correspondendo a cada bloco individual
		*
		* \param std::shared_ptr<Map> map Map a partir do qual será gerado o vetor
		* \return std::vector<std::shared_ptr<Image>> Vetor de Images correspondendo a cada bloco do Map
		* */
		std::vector<std::shared_ptr<Image>> create_image_vector(std::shared_ptr<Map> map);
		
		/*! \brief Retorna um vetor de images que ao ser renderizado imprime o valor num
		* \param int num Valor a ser convertido para imagens
		* \param int x_0, y_0 Posições x e y a partir das quais as Images dos números ficarão
		* \param int size Tamanho de cada número
		* \return std::vector<std::shared_ptr<Image>> Retorna um vetor de Images com os números
		*/
		std::vector<std::shared_ptr<Image>> create_score_image(int num, int x_0, int y_0, int size);
}; 
