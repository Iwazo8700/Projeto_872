#pragma once          

#include <vector>                                                      
#include <memory>           
#include "Player.hpp"          
                         
class IA{          
        private:           
                std::shared_ptr<Player> player;
        	float a,b,c,d;
	public:
		IA(std::shared_ptr<Player> player, float a, float b, float c, float d);
		void set_player(std::shared_ptr<Player> player);
		std::shared_ptr<Player> get_player();
		float get_a();
		float get_b();
		float get_c();
		float get_d();
		void set_a(float a);
		void set_b(float b);
		void set_c(float c);
		void set_d(float d);
}; 

