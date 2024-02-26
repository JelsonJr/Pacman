#pragma once
#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Pacman.hpp"
#include "Fantasma.hpp"

class GerenciadorDeFantasmas
{
	unsigned char current_wave;
	unsigned short wave_timer;

	std::array<Fantasma, 4> ghosts;
public:
	GerenciadorDeFantasmas();

	void draw(bool i_flash, sf::RenderWindow& i_window);
	void reset(unsigned char i_level, const std::array<Posicao, 4>& i_ghost_positions);
	void update(unsigned char i_level, std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_map, Pacman& i_pacman);
};