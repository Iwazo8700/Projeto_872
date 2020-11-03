#pragma once

#include <vector>
#include <memory>
#include "Image.hpp"
#include "Bloco.hpp"
#include "Map.hpp"

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
	public:
		/*! \brief Construtor do BlockPosition
		*
		* Deve receber dois ints representando os pixels inicias da porção da tela considerada
		* e inicializa as variáveis internas da classe
		*
		* \param int x, y Coordenadas dos pixels iniciais
		* \return Nada (este é um construtor!)
		* */
                BlockPosition(int x, int y);

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
}; 
