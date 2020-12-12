#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <vector>
#include <iostream>
#include "Bloco.hpp"
#include "Collision.hpp"

#define UP 'a'
#define DOWN 'b'
#define LEFT 'c'
#define RIGHT 'd'
#define SPACE 'e'
#define ROT_RIGHT 'f'
#define ROT_LEFT 'g'
#define SAVE 'h'
#define LOAD 'i'
#define NONE 'j'

/*! \brief
 *
 * Classe Keyboard
 * Controller responsável por ler as infromações do teclado
 * e atualizar a peça
 *
 *
 * */

class Keyboard{
	private:
		SDL_Event evento; // eventos discretos
 		const Uint8* state; // estado do teclado
		std::shared_ptr<Bloco> bloco;
		bool Rot_atraso = false;
		bool Desloc_atraso = false;
		bool Space_atraso = false;
		char pressed_key;
		int time_des,time_ver,time_rot,time_space,delay,num_lines;
	public:
		Keyboard(std::shared_ptr<Bloco> bloco, int delay, int num_lines);
		Keyboard(int delay, int num_lines);
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Keyboard, pressed_key);
		void set_bloco(std::shared_ptr<Bloco> bloco);
		void update_pressed_key();
		std::vector<std::vector<bool>> Rotation();
		bool Quit();
		bool Load();
		bool Save();
		int Desloc();
		char get_pressed_key();
		std::vector<std::vector<bool>> RotHoraria();
		std::vector<std::vector<bool>> RotAnti();
		int Space(std::shared_ptr<Collision> collision);
		int Desloc_Vert();
		int Down(std::shared_ptr<Collision> collision);
		void set_pressed_key(char key);

};
