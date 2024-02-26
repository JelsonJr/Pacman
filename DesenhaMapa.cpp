#include "DesenhaMapa.hpp"

void desenha_mapa(const std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_map, sf::RenderWindow& i_window)
{
	sf::Sprite sprite;
	sf::Texture texture;

	texture.loadFromFile("Map" + std::to_string(TAMANHO_DA_CELULA) + ".png");
	sprite.setTexture(texture);

	for (unsigned char a = 0; a < LARGURA_DO_MAPA; a++)
	{
		for (unsigned char b = 0; b < ALTURA_DO_MAPA; b++)
		{
			sprite.setPosition(static_cast<float>(TAMANHO_DA_CELULA * a), static_cast<float>(TAMANHO_DA_CELULA * b));

			switch (i_map[a][b])
			{
				case Celula::porta:
					sprite.setTextureRect(sf::IntRect(2 * TAMANHO_DA_CELULA, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));
					i_window.draw(sprite);
					break;

				case Celula::energizador:
					sprite.setTextureRect(sf::IntRect(TAMANHO_DA_CELULA, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));
					i_window.draw(sprite);
					break;

				case Celula::comida:
					sprite.setTextureRect(sf::IntRect(0, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));
					i_window.draw(sprite);
					break;

				case Celula::parede:
					bool down = false;
					bool left = false;
					bool right = false;
					bool up = false;

					if (b < ALTURA_DO_MAPA - 1)
					{
						if (Celula::parede == i_map[a][1 + b])
						{
							down = true;
						}
					}

					if (0 < a)
					{
						if (Celula::parede == i_map[a - 1][b])
						{
							left = true;
						}
					}
					else
					{
						left = true;
					}

					if (a < LARGURA_DO_MAPA - 1)
					{
						if (Celula::parede == i_map[1 + a][b])
						{
							right = true;
						}
					}
					else
					{
						right = true;
					}

					if (0 < b)
					{
						if (Celula::parede == i_map[a][b - 1])
						{
							up = true;
						}
					}

					sprite.setTextureRect(sf::IntRect(TAMANHO_DA_CELULA * (down + 2 * (left + 2 * (right + 2 * up))), 0, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));
					i_window.draw(sprite);
					break;
			}
		}
	}
}