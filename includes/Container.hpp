#pragma once

#include "Map.hpp"
#include "Player.hpp"
#include "Bloco.hpp"
#include "json.hpp"

using nlohmann::json;

class Container{
	private:
		Player player;
		bool alive;
	public:
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Container, player,alive);
		void set_data(Player player, bool alive);
};
