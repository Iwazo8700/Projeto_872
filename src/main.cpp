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
#include <atomic>
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

// Variaveis necessarias tanto dentro da Thread quanto fora
int speed;
int delay;
int keyboard_time;
int decrease;
int decrease_n;
int LINES;
int num_lines;
int COLUMNS;
std::mutex mtx;

// Variavel compartilhada que serve de flag para avisar para a thread que o programa acabou
std::atomic<bool> end_program(false);


/*
	Funcao que sera executada em uma thread separada do programa principal.
	Fica em loop recebendo mensagens que podem ser:
		- Novo Player   --> Adiciona Player no jogo
		- Comando       --> Atualiza Teclado do Player para que o comando recebido seja executado a seguir
		- Player Saindo --> Retira o Player do jogo
*/

void udp_connection(std::shared_ptr<std::vector<std::shared_ptr<Player>>> player_vec,std::shared_ptr<std::vector<udp::endpoint>> remote_endpoint,udp::socket& my_socket){
	// Inicializa variaveis necessarias para a criacao dos players
	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	
	char v[100]; // Vetor que recebera a mensagem
	json j;	     // Objeto Json para receber as informacoes

	udp::endpoint tmp_remote_endpoint; // Guaradara o IP da mensagem recebida
	std::map<udp::endpoint,	std::shared_ptr<Player>> player_map; // Map entre os players e seus correspondentes IPs
	int counter = 0;  // Posicao inicial do bloco do novo player
	char character;
	std::string confirmation_message("Pedido para entrar recebido");
	
	std::cout << "Servidor Inicializado." << std::endl;	

	while(1){
		if(end_program)
			break;

		// Zera o vetor que recebe a mensagem para nao haver lixo nele
		memset(v,'\0',100);
	
		// Recebe mensagem
		my_socket.receive_from(boost::asio::buffer(v,120),tmp_remote_endpoint);		

		if(end_program)
			break;

		// Se o IP do qual a mensagem foi recebida for novo, adiciona um novo Player ao jogo
		if(player_map.count(tmp_remote_endpoint) == 0){
			// Cria novo Player, com seu bloco e teclado
			std::shared_ptr<Bloco> block (new Bloco(counter%(COLUMNS-4),-5,format->get_random()));
			std::shared_ptr<Keyboard> key (new Keyboard(block, keyboard_time, num_lines));
			std::shared_ptr<Player> player (new Player(block, key, speed));

			// Atualiza vetor com os IPs que estao jogando
			mtx.lock();
			remote_endpoint->push_back(tmp_remote_endpoint);	
			player_vec->push_back(player);
			mtx.unlock();
			player_map.insert(std::pair<udp::endpoint,std::shared_ptr<Player>>(tmp_remote_endpoint,player));

			my_socket.send_to(boost::asio::buffer(confirmation_message), tmp_remote_endpoint);
			counter += 4; // Atualiza a posicao para os blocos dos player nao surgirem no mesmo local
			std::cout << "Novo Player Conectado" << std::endl;
		}else{
			// Caso o IP da mensagem ja esteja no jogo

			// Pega as informacoes do json recebido	
			j = json::parse(v);

			if(j["Quit"] == true){
				// Caso seja uma mensagem de sair do jogo

				// Exlui player dos vetores e maps que o guardavam, tirando-o do jogo
				mtx.lock();
	
				player_vec->resize(std::remove(player_vec->begin(),player_vec->end(),player_map.at(tmp_remote_endpoint))-player_vec->begin());
				player_map.erase(tmp_remote_endpoint);
				remote_endpoint->resize(std::remove(remote_endpoint->begin(),remote_endpoint->end(),tmp_remote_endpoint)-remote_endpoint->begin());
	
				mtx.unlock();

				std::cout << "Player Saiu" << std::endl;
			}else{
				// Caso seja um comando
		
				character = j["pressed_key"].get<char>();

				// Atualizado o teclado do Player correspondente, de modo que o comando sera executado na iteracao seguinte do step() na main
				mtx.lock();
				player_map.at(tmp_remote_endpoint)->get_keyboard()->set_pressed_key(character);
				mtx.unlock();
			}
		}
	}
}

int main(){

	// Inicializa configuracoes do jogo a partir do arquivo de configuracao
	std::shared_ptr<ConfigReader> config (new ConfigReader("../assets/config"));


	speed = config->get_speed();
	delay = config->get_delay();
	keyboard_time = config->get_keyboard_time();
	decrease = config->get_decrease();
	decrease_n = config->get_decrease_n();
	LINES = config->get_lines();
	num_lines = config->get_num_lines();
	COLUMNS = config->get_columns();
	bool normal = config->get_normal();

	bool end_game = false; // Variavel que controla quando o jogo deve acabar

	// Cria Mapa e variaveis necessarias para o jogo e controle dos jogadores
	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::shared_ptr<Map> map (new Map(COLUMNS,LINES));
	std::shared_ptr<Map> tmp_map (new Map(COLUMNS,LINES));
	std::shared_ptr<Collision> collision (new Collision(map, normal));
	
	std::shared_ptr<std::vector<std::shared_ptr<Player>>> player_vec(new std::vector<std::shared_ptr<Player>>(0));
	std::shared_ptr<MainController> ctrl;
	
	ctrl = std::shared_ptr<MainController>(new MainController(map, player_vec, format,normal));

	json j;

	std::shared_ptr<Keyboard> key (new Keyboard(keyboard_time, num_lines));

	// Configura udp
	boost::asio::io_service my_io_service;
	udp::endpoint local_endpoint(udp::v4(), 9001);
	udp::socket my_socket(my_io_service,local_endpoint);
	std::shared_ptr<std::vector<udp::endpoint>> remote_endpoint(new std::vector<udp::endpoint>(0));

	// Cria Thread que ficara executando communication para receber as informacoes pelo udp
	std::thread communication(udp_connection, player_vec, remote_endpoint, std::ref(my_socket));

	while(1){

		auto start = std::chrono::steady_clock::now(); // Contador para regular FPS
		
		// Executa um passo do programa
		mtx.lock();
		ctrl->step();
		mtx.unlock();

		// Se todos o player morreram, acaba o jogo
		end_game = true;		
		for(auto plyr : *player_vec)
			if(plyr->is_alive())
				end_game = false;

		if(end_game && player_vec->size())
			break;		

		// Atualiza informacoes de cada player
		for(auto plyr : *player_vec)
			plyr->set_speed(speed - ((plyr->get_lines_completed()/decrease_n)*decrease));

		// Cria json que contera as informacoes que devem ser colocadas na tela para cada player
		int tmp_count = 0;
		tmp_map->set_map(map->get_map());
		std::vector<Container> containers(player_vec->size());

		// Cria um mapa onde 0 corresponde a nenhuma peca e qualquer outro numero corresponde a uma cor
		for(auto plyr : *player_vec){
			containers[tmp_count++].set_data(*plyr,plyr->is_alive());
			tmp_map->add_to_map(plyr->get_piece(),tmp_count);
		}

		j["Players"] = containers;
		j["Map"] = *tmp_map;
		j["Over"] = false;
		
		// Envia o json para cada jogador conectado
		for(auto endpoint : *remote_endpoint)
			my_socket.send_to(boost::asio::buffer(j.dump()), endpoint);


		// COntrole do FPS
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
	

	// Caso o jogo tenha acabado, envia uma mensagem avisando que o jogo acabou para cada player
	int tmp_count = 0;
	std::vector<Container> containers(player_vec->size());

	// Cria um mapa onde 0 corresponde a nenhuma peca e qualquer outro numero corresponde a uma cor
	for(auto plyr : *player_vec){
		containers[tmp_count++].set_data(*plyr,plyr->is_alive());
	}

	j["Players"] = containers;
	j["Over"] = true;
	for(auto endpoint : *remote_endpoint)
		my_socket.send_to(boost::asio::buffer(j.dump()), endpoint);

	// Define a flag de termino de programa como true e espera a thread acabar
	end_program = true;
	communication.join();	

	return 0;
}
