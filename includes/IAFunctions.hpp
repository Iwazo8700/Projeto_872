#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <memory>
#include "Keyboard.hpp"
#include "IA.hpp"
#include "Map.hpp"
#include "Bloco.hpp"
#include "Player.hpp"
#include "Collision.hpp"

class IAFunctions{
	private:
		std::shared_ptr<IA> ia;
		std::shared_ptr<Map> map, tmp_map;
		std::shared_ptr<Collision> collision;
	public:
		IAFunctions(std::shared_ptr<IA> ia, std::shared_ptr<Map> map, std::shared_ptr<Collision> collision);
		void set_Map(std::shared_ptr<Map> map);
		std::shared_ptr<Map> get_Map();
		std::shared_ptr<IA> get_IA();
		void set_IA(std::shared_ptr<IA> ia);
		int AggregateHeights();
		int CompleteLines();
		int Holes();
		int Bumpiness();
		float Score();
		std::shared_ptr<Bloco> TestAll();

};
