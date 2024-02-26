#include "GerenciadorDeFantasmas.hpp"

GerenciadorDeFantasmas::GerenciadorDeFantasmas() :
	current_wave(0),
	wave_timer(LONG_SCATTER_DURATION),
	ghosts({ Fantasma(0), Fantasma(1), Fantasma(2), Fantasma(3) })
{}

void GerenciadorDeFantasmas::draw(bool i_flash, sf::RenderWindow& i_window)
{
	for (Fantasma& ghost : ghosts)
	{
		ghost.draw(i_flash, i_window);
	}
}

void GerenciadorDeFantasmas::reset(unsigned char i_level, const std::array<Posicao, 4>& i_ghost_positions)
{
	current_wave = 0;
	wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));

	for (unsigned char a = 0; a < 4; a++)
	{
		ghosts[a].set_position(i_ghost_positions[a].x, i_ghost_positions[a].y);
	}
	
	for (Fantasma& ghost : ghosts)
	{
		ghost.reset(ghosts[2].get_position(), ghosts[0].get_position());
	}
}

void GerenciadorDeFantasmas::update(unsigned char i_level, std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_map, Pacman& i_pacman)
{
	if (!i_pacman.get_energizer_timer())
	{
		if (!wave_timer)
		{
			if (7 > current_wave)
			{
				current_wave++;

				for (Fantasma& ghost : ghosts)
				{
					ghost.switch_mode();
				}
			}

			if (current_wave % 2 == 1)
			{
				wave_timer = CHASE_DURATION;
			}
			else if (2 == current_wave)
			{
				wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));
			}
			else
			{
				wave_timer = static_cast<unsigned short>(SHORT_SCATTER_DURATION / pow(2, i_level));
			}

			return;
		}

		wave_timer--;
	}

	for (Fantasma& ghost : ghosts)
	{
		ghost.update(i_level, i_map, ghosts[0], i_pacman);
	}
}