#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstddef> 

/*! \brief Classe ConfigReader
*
* Classe responsável por ler arquivo de configurações e retornar seus dados
*
*/

class ConfigReader{
	private:
		int screen_width; /*<! Largura da tela em px*/
		int screen_height; /*<! Altura da tela em px*/
		int block_size_x; /*<! Largura do bloco em px*/
		int block_size_y; /*<! Altura do bloco em px*/
		int lines; /*<! Número de linhas no mapa*/
		int num_lines; /*<! Número de linhas que o bloco desce a cada clique*/
		int columns; /*<! Número de colunas no mapa*/
		int speed; /*<! Velocidade inicial do player*/
		int shift_x; /*<! Distância em px do mapa à borda lateral da tela*/
		int shift_y; /*<! Distância em px do mapa à borda superior da tela*/
		int delay; /*<! Delay entre cada iteração do loop principal*/
		int decrease; /*<! Decremento da velocidade para cada n blocos completo*/
		int decrease_n; /*<! Número de linhas completas para decrementar a velocidade*/
		int keyboard_time; /*<! Tempo mínimo entre 2 cliques do teclado*/
		int get_value(std::string text); /*<! Retorna o int dentro da string text*/
		int r,g,b; /*<! Cores rgb para as linhas do mapa*/
		int block_r,block_g,block_b; /*<! Cores rgb para o bloco*/
		int thickness; /*<! Grossura das linhas do mapa*/
	public:
		/*! Construtor da classe ConfigReader
		*
		* Lê o arquivo fornecido e salva seus dados em suas variáveis
		*
		* \param const char* config_file Nome do arquivo contendo as configurações
		* \return Nada (é um construtor)
		*/	
		ConfigReader(const char* config_file);
		int get_screen_width();	
		int get_screen_height();	
		int get_lines();
		int get_thickness();
		int get_block_r();
		int get_block_g();
		int get_block_b();
		int get_r();
		int get_g();
		int get_b();
		int get_num_lines();	
		int get_keyboard_time();	
		int get_block_size_x();	
		int get_block_size_y();	
		int get_columns();	
		int get_speed();	
		int get_shift_x();	
		int get_shift_y();	
		int get_delay();
		int get_decrease();
		int get_decrease_n();
};
