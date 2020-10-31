#pragma once

#include "Image.hpp"
#include "Bloco.hpp"
#include <vector>
#include <memory>

class Block_Position{
	private:
		int height, width;  /*!< Largura e altura da parte da tela considerada*/
		int x_begin, y_begin; /*!< Valor do pixel inicial da altura e da largura da parte da tela considerada*/
	public:
		Block_Position(int x, int y, int height, int width);
		std::vector<Image> create_image_vector(std::vector<std::vector<int>> blocks);
}
