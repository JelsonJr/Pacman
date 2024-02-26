#pragma once
#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "ColisaoMapa.hpp"

class Pacman
{
	bool animation_over;
	bool morto;
	unsigned char direcao;
	unsigned short animation_timer;
	unsigned short energizer_timer;
	Posicao posicao;

public:
	Pacman();

	bool get_animation_over() const;
	bool get_dead() const;
	unsigned char get_direction() const;
	unsigned short get_energizer_timer() const;
	Posicao get_posicao() const;

	void draw(bool i_victory, sf::RenderWindow& i_window);
	void reset();
	void set_animation_timer(unsigned short i_animation_timer);
	void set_dead(bool i_dead);
	void set_posicao(short i_x, short i_y);
	void update(unsigned char i_level, std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_map);
};