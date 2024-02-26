#include <array>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Pacman.hpp"
#include "Fantasma.hpp"
#include "GerenciadorDeFantasmas.hpp"
#include "ConverteEsboco.hpp"
#include "DesenhaMapa.hpp"
#include "EscreveTexto.hpp"

int main()
{
	bool venceu = false;
	unsigned lag = 0;
	unsigned char level = 0;
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	std::array<std::string, ALTURA_DO_MAPA> esboco_do_mapa = {
		" ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};
	std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA> mapa{};
	std::array<Posicao, 4> posicao_dos_fantasmas;

	sf::Event ev;
	sf::RenderWindow janela(sf::VideoMode(TAMANHO_DA_CELULA * LARGURA_DO_MAPA * SCREEN_RESIZE, (TAMANHO_DA_FONTE + TAMANHO_DA_CELULA * ALTURA_DO_MAPA) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close);
	janela.setView(sf::View(sf::FloatRect(0, 0, TAMANHO_DA_CELULA * LARGURA_DO_MAPA, TAMANHO_DA_FONTE + TAMANHO_DA_CELULA * ALTURA_DO_MAPA)));

	GerenciadorDeFantasmas gerenciador_dos_fantasmas;
	Pacman pacman;

	srand(static_cast<unsigned>(time(0)));

	mapa = converte_esboco(esboco_do_mapa, posicao_dos_fantasmas, pacman);
	gerenciador_dos_fantasmas.reset(level, posicao_dos_fantasmas);
	previous_time = std::chrono::steady_clock::now();

	while (janela.isOpen())
	{
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();
		lag += delta_time;
		previous_time += std::chrono::microseconds(delta_time);

		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			while (janela.pollEvent(ev))
			{
				switch (ev.type)
				{
					case sf::Event::Closed:
						janela.close();
				}
			}

			if (!venceu && !pacman.get_dead())
			{
				venceu = true;
				pacman.update(level, mapa);
				gerenciador_dos_fantasmas.update(level, mapa, pacman);

				for (const std::array<Celula, ALTURA_DO_MAPA>& column : mapa)
				{
					for (const Celula& celula : column)
					{
						if (Celula::comida == celula)
						{
							venceu = false;
							break;
						}
					}

					if (!venceu) break;
				}

				if (venceu)
				{
					pacman.set_animation_timer(0);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
			{
				venceu = false;

				if (pacman.get_dead())
				{
					level = 0;
				}
				else
				{
					level++;
				}

				mapa = converte_esboco(esboco_do_mapa, posicao_dos_fantasmas, pacman);
				gerenciador_dos_fantasmas.reset(level, posicao_dos_fantasmas);
				pacman.reset();
			}
			if (FRAME_DURATION > lag)
			{
				janela.clear();

				if (!venceu && !pacman.get_dead())
				{
					desenha_mapa(mapa, janela);

					gerenciador_dos_fantasmas.draw(GHOST_FLASH_START >= pacman.get_energizer_timer(), janela);

					escreve_texto(0, 0, TAMANHO_DA_CELULA * ALTURA_DO_MAPA, "Level: " + std::to_string(1 + level), janela);
				}

				pacman.draw(venceu, janela);

				if (pacman.get_animation_over())
				{
					if (venceu)
					{
						escreve_texto(1, 0, 0, "Next level!", janela);
					}
					else
					{
						escreve_texto(1, 0, 0, "Game over", janela);
					}
				}

				janela.display();
			}
		}
	}
}