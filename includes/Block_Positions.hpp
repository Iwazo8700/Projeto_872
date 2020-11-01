#pragma once

#include <vector>
#include <memory>
#include "Image.hpp"
#include "Bloco.hpp"
#include "Map.hpp"

class BlockPosition{
	private:
		int x_begin, y_begin; /*!< Número dos pixels iniciais da porção da tela sendo considerada*/
	public:
		BlockPosition(int x, int y, int height, int width);
		std::vector<std::shared_ptr<Image>> create_image_vector(std::shared_ptr<Bloco> block);
		std::vector<std::shared_ptr<Image>> create_image_vector(std::shared_ptr<Map> map);
}; 
