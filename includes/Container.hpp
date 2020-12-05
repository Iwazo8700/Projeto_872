#pragma once

#include "Map.hpp"
#include "Player.hpp"
#include "Bloco.hpp"
#include "json.hpp"

using nlohmann::json;

class Container{
	private:
		Bloco block;
		Player player;
	public:
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Container, block, player);
		void set_data(Player player, Bloco block);
};
