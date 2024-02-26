#pragma once
#include <array>
#include <cmath>
#include "Global.hpp"

bool colisao_mapa(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_map);