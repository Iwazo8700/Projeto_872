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

using boost::asio::ip::udp;

int main(){

	//Configura definicoes com base no arquivo de configuracao
	std::shared_ptr<ConfigReader> config (new ConfigReader("../assets/config"));
	std::string IP = config->get_ip();

	int speed = config->get_speed();
	int delay = config->get_delay();
	int keyboard_time = config->get_keyboard_time();
	int decrease = config->get_decrease();
	int decrease_n = config->get_decrease_n();
	int SCREEN_W = config->get_screen_width();
	int SCREEN_H = config->get_screen_height();
	int BLOCK_SIZE_X = config->get_block_size_x();
	int BLOCK_SIZE_Y = config->get_block_size_y();
	int LINES = config->get_lines();
	int num_lines = config->get_num_lines();
	int COLUMNS = config->get_columns();
	int SHIFT_X = config->get_shift_x();
	int SHIFT_Y = config->get_shift_y();
	int thickness = config->get_thickness();
	int r = config->get_r();
	int g = config->get_g();
	int b = config->get_b();
	int block_r = config->get_block_r();
	int block_g = config->get_block_g();
	int block_b = config->get_block_b();
	bool normal = config->get_normal();

	// Inicializa variaveis necessarias para o programa
	std::shared_ptr<Formato> format (new Formato("../assets/Formatos.dat"));
	std::shared_ptr<SDL_Model> sdl (new SDL_Model(SCREEN_W,SCREEN_H));
	std::shared_ptr<View> view (new View(sdl));
	std::shared_ptr<Sprite> sprite (new Sprite(sdl,""));
	std::shared_ptr<Sprite> sprite2 (new Sprite(sdl,""));
	std::shared_ptr<Sprite> sprite7 (new Sprite(sdl,""));
	std::shared_ptr<Sprite> sprite4 (new Sprite(sdl,""));
	std::shared_ptr<Sprite> sprite5 (new Sprite(sdl,""));
	std::shared_ptr<Sprite> sprite6 (new Sprite(sdl,""));
	std::shared_ptr<Sprite> sprite8 (new Sprite(sdl,""));
	sprite2->set_texture(sdl->create_map_texture(LINES,COLUMNS,BLOCK_SIZE_X,BLOCK_SIZE_Y,thickness,r,g,b));
	sprite7->set_texture(sdl->create_block_texture(BLOCK_SIZE_X,BLOCK_SIZE_Y,block_r,block_g,block_b));
	sprite4->set_texture(sdl->create_block_texture(BLOCK_SIZE_X,BLOCK_SIZE_Y,(block_r+100)%256,block_g,block_b));
	sprite5->set_texture(sdl->create_block_texture(BLOCK_SIZE_X,BLOCK_SIZE_Y,block_r,(block_g+100)%256,block_b));
	sprite6->set_texture(sdl->create_block_texture(BLOCK_SIZE_X,BLOCK_SIZE_Y,block_r,block_g,(block_b+100)%256));
	sprite->set_texture(sdl->create_block_texture(BLOCK_SIZE_X,BLOCK_SIZE_Y,(block_r+100)%256,block_g,(block_b+100)%256));
	sprite8->set_texture(sdl->create_block_texture(BLOCK_SIZE_X,BLOCK_SIZE_Y,block_r,(block_g+100)%256,(block_b+100)%256));
	std::shared_ptr<Sprite> sprite3 (new Sprite(sdl, "../assets/score.png"));
	std::shared_ptr<Map> map (new Map(COLUMNS,LINES,BLOCK_SIZE_X,BLOCK_SIZE_Y));
	std::shared_ptr<Image> img (new Image(SHIFT_X, SHIFT_Y,BLOCK_SIZE_X*COLUMNS,BLOCK_SIZE_Y*LINES,sprite2));
	std::shared_ptr<Image> end_screen (new Image(SCREEN_W/2-2*BLOCK_SIZE_X,SCREEN_H/2-2*BLOCK_SIZE_Y,4*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,sprite3));
	std::shared_ptr<Bloco> block (new Bloco(COLUMNS/2,-5,format->get_random(),sprite,BLOCK_SIZE_Y,BLOCK_SIZE_X));
	std::shared_ptr<Collision> collision (new Collision(map,true));
	std::vector<std::shared_ptr<Sprite>> vecin;
	vecin.push_back(sprite);
	vecin.push_back(sprite7);
	vecin.push_back(sprite4);
	vecin.push_back(sprite5);
	vecin.push_back(sprite6);
	vecin.push_back(sprite8);
	map->set_sprites(vecin);
	std::shared_ptr<BlockPosition> blk_pos(new BlockPosition(SHIFT_X, SHIFT_Y, sdl));
	std::shared_ptr<Keyboard> key (new Keyboard(block, keyboard_time, num_lines));
	std::shared_ptr<Image> score (new Image(SCREEN_W*3/4-2*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,4*BLOCK_SIZE_X,2*BLOCK_SIZE_Y,sprite3));
	
	json j;

	int player_num = 0;
	int plyr_x, plyr_y,plyr_points;
	char recv[2000];
	std::vector<std::vector<bool>> plyr_format;
	std::vector<std::shared_ptr<Image>> prints;
	std::vector<std::shared_ptr<Image>> tmp_prints;
	int letter;

	// Configura udp e conecta com servidor
	boost::asio::io_service io_service;
	udp::endpoint local_endpoint(udp::v4(), 0);
	udp::socket meu_socket(io_service, local_endpoint);
	boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string(IP);
	udp::endpoint remote_endpoint(ip_remoto, 9001);
	std::string v("Conectando\n");
	meu_socket.send_to(boost::asio::buffer(v), remote_endpoint);

	// Espera mensagem do servidor confirmando conexao
	meu_socket.receive_from(boost::asio::buffer(recv, 2000), remote_endpoint);

	while(1){

		// Caso o jogador feche a tela, sai do jogo e envia uma mensagem de desconexao para o servidor
		if(key->Quit()){
			j["Quit"] = true;
			meu_socket.send_to(boost::asio::buffer(j.dump()), remote_endpoint);
			break;
		}

		// Limpa vetor que recebera a mensagem para nao haver lixo nele
		memset(recv, '\0', 2000);
		
		// Recebe mensagem do servidor
		meu_socket.receive_from(boost::asio::buffer(recv, 2000), remote_endpoint);	
		
		j = json::parse(recv);
		
		// Verifica se o jogo terminou ou ainda nao, se tiver sai do jogo
		if(j["Over"] == true) break;

		// Le o mapa da mensagem recebida e cria sua imagem	
		map->set_map(j["Map"]["map"]);
		prints = blk_pos->create_image_vector(map);

		// Cria as imagens com as pontuacoes dos jogadores
		player_num = j["Players"].size();
		for(int plyr = 0; plyr < player_num; plyr++){
			plyr_points = j["Players"][plyr]["player"]["points"];
			
			tmp_prints = blk_pos->create_block_image(SCREEN_W*3/4-3*BLOCK_SIZE_X, (5+2*plyr)*BLOCK_SIZE_X, BLOCK_SIZE_X,vecin[plyr%vecin.size()]);
			prints.insert(prints.end(), tmp_prints.begin(),tmp_prints.end());		
			
			tmp_prints = blk_pos->create_score_image(plyr_points, SCREEN_W*3/4-2*BLOCK_SIZE_X, (5+2*plyr)*BLOCK_SIZE_X, BLOCK_SIZE_X);
			prints.insert(prints.end(), tmp_prints.begin(),tmp_prints.end());		
		}
		
		prints.insert(prints.end(), score);		
		prints.insert(prints.begin(),img);

		// Renderiza imagens
		view->render(prints);
	
		// Verifica se o jogador clicou em alguma tecla
		key->update_pressed_key();


		// Envia para o servidor um json contendo a tecla clicada pelo jogador
		j = *key;
		j["Quit"] = false;

		meu_socket.send_to(boost::asio::buffer(j.dump()), remote_endpoint);
	}

	// Caso o jogo tenha terminado, renderiza na tela apenas as pontuacoes dos jogadores
	if(j["Over"] == true){
		std::shared_ptr<Image> score (new Image(SCREEN_W/2-6*BLOCK_SIZE_X,1*BLOCK_SIZE_Y,12*BLOCK_SIZE_X,4*BLOCK_SIZE_Y,sprite3));
		std::vector<std::shared_ptr<Image>> end_prints;

		player_num = j["Players"].size();
		for(int plyr = 0; plyr < player_num; plyr++){
			plyr_points = j["Players"][plyr]["player"]["points"];
		
			tmp_prints = blk_pos->create_block_image(SCREEN_W/2-8*BLOCK_SIZE_X, (6+4*plyr)*BLOCK_SIZE_X, BLOCK_SIZE_X*2,vecin[plyr%vecin.size()]);
			end_prints.insert(end_prints.end(), tmp_prints.begin(),tmp_prints.end());		
		
			tmp_prints = blk_pos->create_score_image(plyr_points, SCREEN_W/2-6*BLOCK_SIZE_X, (6+4*plyr)*BLOCK_SIZE_X, BLOCK_SIZE_X*2);
			end_prints.insert(end_prints.end(), tmp_prints.begin(),tmp_prints.end());		
		}
	
		end_prints.insert(end_prints.end(), score);		

		std::string end_message("Finalizado\n");
		meu_socket.send_to(boost::asio::buffer(end_message), remote_endpoint);
		while(1){
			if(key->Quit())
				break;
			
			view->render(end_prints);
		}
	}
	
	std::cout << "Jogo Finalizado" << std::endl;	

	return 0;
}
