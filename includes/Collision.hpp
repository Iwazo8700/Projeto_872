#pragma once

#include "Map.hpp"
#include "Bloco.hpp"
#include <vector>
#include <memory>

class Collision{
	private:
		std::shared_ptr<Map> map;
	public:
		Collision(std::shared_ptr<Map> map);
		void set_map(std::shared_ptr<Map> map);
		bool is_colliding(std::shared_ptr<Bloco> block);
		bool is_colliding(std::shared_ptr<Bloco> block, std::vector<std::shared_ptr<Bloco>> others);
};
