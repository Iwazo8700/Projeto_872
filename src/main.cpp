#include "SDL_Model.hpp"
#include <string> 
#include "Sprite.hpp"
#include "Bloco.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "View.hpp"
#include "Image.hpp"
#include "Formato.hpp"
#include "MainController.hpp"
#include "Collision.hpp"
#include "BlockPosition.hpp"
#include "Keyboard.hpp"
#include "ConfigReader.hpp"
#include "IA.hpp"
#include "Container.hpp"
#include "IAFunctions.hpp"
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <chrono>
#include "json.hpp"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include <pthread.h>
#include <mutex>

using boost::asio::ip::udp;

int speed;
int delay;
int keyboard_time;
int decrease;
int decrease_n;
int LINES;
int num_lines;
int COLUMNS;
std::mutex mtx;


void udp_connection(std::vector<std::shared_ptr<Player>>& player_vec,std::vector<udp::endpoint>& remote_endpoint,udp::socket& my_socket){
	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	char v[100];
	json j;	

	udp::endpoint tmp_remote_endpoint;
	std::map<udp::endpoint,	std::shared_ptr<Player>> player_map;
	int counter = 0;
	char character;

	while(1){
		memset(v,0,100);
		my_socket.receive_from(boost::asio::buffer(v,120),tmp_remote_endpoint);

		if(player_map.count(tmp_remote_endpoint) == 0){
			std::shared_ptr<Bloco> block (new Bloco(counter%(COLUMNS-4),-5,format->get_random()));
			std::shared_ptr<Keyboard> key (new Keyboard(block, keyboard_time, num_lines));
			std::shared_ptr<Player> player (new Player(block, key, speed));
			std::vector<std::shared_ptr<Player>> tmp_vec;
			std::vector<udp::endpoint> tmp_vec2;
			mtx.lock();
			remote_endpoint.push_back(tmp_remote_endpoint);	
			player_vec.push_back(player);
			mtx.unlock();
			player_map.insert(std::pair<udp::endpoint,std::shared_ptr<Player>>(tmp_remote_endpoint,player));
			counter += 4;
		}else{
			int letter = 0;
			for(letter = 99; v[letter] != '}'; letter--);
			v[letter+1] = '\0';		
			j = json::parse(v);
			if(j["Quit"] == true){
				std::vector<std::shared_ptr<Player>> tmp_vec;
				std::vector<udp::endpoint> tmp_vec2;
				mtx.lock();
				remove_copy(player_vec.begin(),player_vec.end(),tmp_vec.begin(),player_map.at(tmp_remote_endpoint));
				player_map.erase(tmp_remote_endpoint);
				remove_copy(remote_endpoint.begin(),remote_endpoint.end(),tmp_vec2.begin(),tmp_remote_endpoint);
				player_vec.assign(tmp_vec.begin(),tmp_vec.end());
				remote_endpoint.assign(tmp_vec2.begin(),tmp_vec2.end());
				std::cout << "Excluido" << std::endl;
				mtx.unlock();
			}else{
				character = j["pressed_key"].get<char>();
				mtx.lock();
				player_map.at(tmp_remote_endpoint)->get_keyboard()->set_pressed_key(character);
				mtx.unlock();
			}
		}
	}
}

int main(){
	std::shared_ptr<ConfigReader> config (new ConfigReader("../assets/config"));

	speed = config->get_speed();
	delay = config->get_delay();
	keyboard_time = config->get_keyboard_time();
	decrease = config->get_decrease();
	decrease_n = config->get_decrease_n();
	LINES = config->get_lines();
	num_lines = config->get_num_lines();
	COLUMNS = config->get_columns();

	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::shared_ptr<Map> map (new Map(COLUMNS,LINES));
	std::shared_ptr<Map> tmp_map (new Map(COLUMNS,LINES));
	std::shared_ptr<Collision> collision (new Collision(map));
	
	std::vector<std::shared_ptr<Player>> player_vec;
	std::shared_ptr<MainController> ctrl;
	
	ctrl = std::shared_ptr<MainController>(new MainController(map, player_vec, format));

	json j;

	std::shared_ptr<Keyboard> key (new Keyboard(keyboard_time, num_lines));

	boost::asio::io_service my_io_service;
	udp::endpoint local_endpoint(udp::v4(), 9001);
	udp::socket my_socket(my_io_service,local_endpoint);
	std::vector<udp::endpoint> remote_endpoint;

	std::thread communication(udp_connection, std::ref(player_vec), std::ref(remote_endpoint), std::ref(my_socket));

	while(1){
		auto start = std::chrono::steady_clock::now();
		if(key->Quit()) break;
		
		ctrl->set_players(player_vec);	
	
		mtx.lock();
		ctrl->step();
		mtx.unlock();

		for(auto plyr : player_vec)
			if(plyr->is_alive())
				break;
		for(auto plyr : player_vec)
			plyr->set_speed(speed - ((plyr->get_lines_completed()/decrease_n)*decrease));

		int tmp_count = 0;
		tmp_map->set_map(map->get_map());
		std::vector<Container> containers(player_vec.size());
		for(auto plyr : player_vec){
			containers[tmp_count++].set_data(*plyr,plyr->is_alive());
			tmp_map->add_to_map(plyr->get_piece(),tmp_count);
		}

		j["Players"] = containers;
		j["Map"] = *tmp_map;
		j["Over"] = false;
		
		for(auto endpoint : remote_endpoint)
			my_socket.send_to(boost::asio::buffer(j.dump()), endpoint);

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = end-start;
		if(diff.count()/1000 < delay)
			SDL_Delay(delay-diff.count()/1000);


		/*

		if(key->Save()){
			int tmp_count = 0;
			std::vector<Container> containers(player_vec.size());
			for(auto plyr : player_vec){
				containers[tmp_count++].set_data(*plyr,*(plyr->get_piece()));
			}

			j["Players"] = containers;
			j["Map"] = *map;
			std::ofstream o("../assets/savefile.json");
			o << j << std::endl;
		}
		if(key->Load()){
			std::ifstream i("../assets/savefile.json");
			if (i.is_open() ) {
				i >> j;
				i.close();
				std::vector<Container> containers;
				int player_num = 0;
				for(auto plyr : player_vec){
					plyr->set_points(j["Players"][player_num]["player"]["points"]);
					plyr->set_speed(j["Players"][player_num]["player"]["speed"]);
					plyr->set_lines_completed(j["Players"][player_num]["player"]["lines_completed"]);
					map->set_map(j["Players"][player_num]["map"]["map"]);
					plyr->get_piece()->set_formato(j["Players"][player_num]["block"]["formato"]);
					plyr->get_piece()->set_x(j["Players"][player_num]["block"]["x"]);
					plyr->get_piece()->set_y(j["Players"][player_num]["block"]["y"]);
					player_num++;
				}
			} else {
				std::cout << "Erro ao tentar ler arquivo de saves!" << std::endl;
			}
		}

		*/
	}
	
	j["Over"] = true;
	for(auto endpoint : remote_endpoint)
		my_socket.send_to(boost::asio::buffer(j.dump()), endpoint);
		
	return 0;
}
