#include "ColisaoMapa.hpp"

bool colisao_mapa(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_map)
{
	bool output = 0;

	float cell_x = i_x / static_cast<float>(TAMANHO_DA_CELULA);
	float cell_y = i_y / static_cast<float>(TAMANHO_DA_CELULA);

	for (unsigned char a = 0; a < 4; a++)
	{
		short x = 0;
		short y = 0;

		switch (a)
		{
		case 0: 
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(floor(cell_y));

			break;
		}
		case 1: 
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(floor(cell_y));

			break;
		}
		case 2: 
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(ceil(cell_y));

			break;
		}
		case 3:
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(ceil(cell_y));
		}
		}

		if (0 <= x && 0 <= y && ALTURA_DO_MAPA > y && LARGURA_DO_MAPA > x)
		{
			if (0 == i_collect_pellets) 
			{
				if (Celula::parede == i_map[x][y])
				{
					output = 1;
				}
				else if (0 == i_use_door && Celula::porta == i_map[x][y])
				{
					output = 1;
				}
			}
			else 
			{
				if (Celula::energizador == i_map[x][y])
				{
					output = 1;

					i_map[x][y] = Celula::vazio;
				}
				else if (Celula::comida == i_map[x][y])
				{
					i_map[x][y] = Celula::vazio;
				}
			}
		}
	}

	return output;
}