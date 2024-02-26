#include "ConverteEsboco.hpp"

std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA> converte_esboco(
	const std::array<std::string, 
	ALTURA_DO_MAPA>& i_map_sketch, 
	std::array<Posicao, 4>& i_ghost_positions, 
	Pacman& i_pacman) {

	std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA> output_map{};

	for (unsigned char a = 0; a < ALTURA_DO_MAPA; a++)
	{
		for (unsigned char b = 0; b < LARGURA_DO_MAPA; b++)
		{
			output_map[b][a] = Celula::vazio;

			switch (i_map_sketch[a][b])
			{
				case '#':
					output_map[b][a] = Celula::parede;
					break;

				case '=':
					output_map[b][a] = Celula::porta;
					break;

				case '.':
					output_map[b][a] = Celula::comida;
					break;

				case '0':
					i_ghost_positions[0].x = TAMANHO_DA_CELULA * b;
					i_ghost_positions[0].y = TAMANHO_DA_CELULA * a;
					break;

				case '1':
					i_ghost_positions[1].x = TAMANHO_DA_CELULA * b;
					i_ghost_positions[1].y = TAMANHO_DA_CELULA * a;
					break;

				case '2':
					i_ghost_positions[2].x = TAMANHO_DA_CELULA * b;
					i_ghost_positions[2].y = TAMANHO_DA_CELULA * a;
					break;

				case '3':
					i_ghost_positions[3].x = TAMANHO_DA_CELULA * b;
					i_ghost_positions[3].y = TAMANHO_DA_CELULA * a;
					break;
				
				case 'P':
					i_pacman.set_posicao(TAMANHO_DA_CELULA * b, TAMANHO_DA_CELULA * a);
					break;

				case 'o':
					output_map[b][a] = Celula::energizador;
					break;
			}
		}
	}

	return output_map;
}