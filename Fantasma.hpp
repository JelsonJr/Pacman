#pragma once
#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Pacman.hpp"
#include "Fantasma.hpp"
#include "ColisaoMapa.hpp"

class Fantasma
{
	bool movement_mode;
	bool use_door;
	unsigned char direction;
	unsigned char frightened_mode;
	unsigned char frightened_speed_timer;
	unsigned char id;
	unsigned short animation_timer;

	Posicao home;
	Posicao home_exit;
	Posicao position;
	Posicao target;
public:
	Fantasma(unsigned char i_id);

	Posicao get_position() const;
	float get_target_distance(unsigned char i_direction) const;
	bool pacman_collision(const Posicao& i_pacman_position) const;
	void draw(bool i_flash, sf::RenderWindow& i_window);
	void reset(const Posicao& i_home, const Posicao& i_home_exit);
	void set_position(short i_x, short i_y);
	void switch_mode();
	void update(unsigned char i_level, std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_map, Fantasma& i_ghost_0, Pacman& i_pacman);
	void update_target(unsigned char i_pacman_direction, const Posicao& i_ghost_0_position, const Posicao& i_pacman_position);
};