#pragma once

#include "Map.hpp"
#include "Bloco.hpp"
#include <vector>
#include <memory>

/*! \brief Classe Collision
*
* Classe responsável por verificar colisões entre Blocos e o Mapa ou entre os próprios Blocos
* 
* */

class Collision{
	private:
		std::shared_ptr<Map> map; /*<! std::shared_ptr<Map> para o Map com o qual a colisão deve ser verificada*/
	public:
		/*! \brief Construtor da Collision
		*
		* Deve receber um std::shared_ptr<Map> para o Map com o qual será verificada as colisões.
		* Inicializa as variáveis internas da classe/
		*
		* \param std::shared_ptr<Map> map Map com o qual será verificada a colisão
		* \return Nada (este é um construtor!)
		* */
		Collision(std::shared_ptr<Map> map);
		void set_map(std::shared_ptr<Map> map);

		/*!
		*
		* \brief Verifica se um Bloco está colidindo com o Mapa
		*
		* \param std::shared_ptr<Bloco> block Bloco com o qual será verificada a colisão
		* \return bool Retorna true se o bloco está colidindo e false caso contrário
		*/
		bool is_colliding(std::shared_ptr<Bloco> block);
		/*!
		*
		* \brief Verifica se um Bloco está colidindo com outros Blocos
		*
		* Verifica apenas a colisão entre o Bloco e os Blocos do vetor de Blocos.
		* Não verifica colisão entre os Blocos do próprio vetor.
		*
		* \param std::shared_ptr<Bloco> block Bloco com o qual será verificada a colisão
		* \param std::vector<std::shared_ptr<Bloco>> others Outros Blocos com os quais será verificada a colisão
		* \return bool Retorna true se o bloco está colidindo e false caso contrário
		*/
		bool is_colliding(std::shared_ptr<Bloco> block, std::vector<std::shared_ptr<Bloco>> others);
};
