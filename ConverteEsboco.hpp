#pragma once

#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Pacman.hpp"

std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA> converte_esboco(
	const std::array<std::string,
	ALTURA_DO_MAPA>& i_map_sketch,
	std::array<Posicao, 4>& i_ghost_positions,
	Pacman& i_pacman
);