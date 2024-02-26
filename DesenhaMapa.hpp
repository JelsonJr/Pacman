#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include "Global.hpp"

void desenha_mapa(const std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_map, sf::RenderWindow& i_window);