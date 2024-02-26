#include "Fantasma.hpp"

Fantasma::Fantasma(unsigned char i_id) :
	id(i_id)
{}

Posicao Fantasma::get_position() const
{
	return position;
}

bool Fantasma::pacman_collision(const Posicao& i_pacman_position) const
{
	bool x_collision = (position.x >= i_pacman_position.x - TAMANHO_DA_CELULA) && (position.x < i_pacman_position.x + TAMANHO_DA_CELULA);
	bool y_collision = (position.y >= i_pacman_position.y - TAMANHO_DA_CELULA) && (position.y < i_pacman_position.y + TAMANHO_DA_CELULA);

	return x_collision && y_collision;
}

float Fantasma::get_target_distance(unsigned char i_direction) const
{
	short x = position.x;
	short y = position.y;

	switch (i_direction)
	{
		case 0:
			x += VELOCIDADE_DO_FANTASMA;
			break;
		
		case 1:
			y -= VELOCIDADE_DO_FANTASMA;
			break;
		
		case 2:
			x -= VELOCIDADE_DO_FANTASMA;
			break;
		
		case 3:
			y += VELOCIDADE_DO_FANTASMA;
			break;
	}

	return static_cast<float>(sqrt(pow(x - target.x, 2) + pow(y - target.y, 2)));
}

void Fantasma::draw(bool i_flash, sf::RenderWindow& i_window)
{
	unsigned char body_frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(FANTASMA_VELOCIDADE_DA_ANIMACAO)));

	sf::Sprite body;
	sf::Sprite face;
	sf::Texture texture;
	
	texture.loadFromFile("Ghost" + std::to_string(TAMANHO_DA_CELULA) + ".png");
	
	body.setTexture(texture);
	body.setPosition(position.x, position.y);
	body.setTextureRect(sf::IntRect(TAMANHO_DA_CELULA * body_frame, 0, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));

	face.setTexture(texture);
	face.setPosition(position.x, position.y);

	if (!frightened_mode)
	{
		switch (id)
		{
			case 0:
				body.setColor(sf::Color(255, 0, 0));
				break;

			case 1:
				body.setColor(sf::Color(255, 182, 255));
				break;

			case 2:
				body.setColor(sf::Color(0, 255, 255));
				break;

			case 3:
				body.setColor(sf::Color(255, 182, 85));
				break;
		}	

		face.setTextureRect(sf::IntRect(TAMANHO_DA_CELULA * direction, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));
		i_window.draw(body);
	}
	else if (1 == frightened_mode)
	{
		body.setColor(sf::Color(36, 36, 255));
		face.setTextureRect(sf::IntRect(4 * TAMANHO_DA_CELULA, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));

		if (1 == i_flash && 0 == body_frame % 2)
		{
			body.setColor(sf::Color(255, 255, 255));
			face.setColor(sf::Color(255, 0, 0));
		}
		else
		{
			body.setColor(sf::Color(36, 36, 255));
			face.setColor(sf::Color(255, 255, 255));
		}

		i_window.draw(body);
	}
	else
	{
		face.setTextureRect(sf::IntRect(TAMANHO_DA_CELULA * direction, 2 * TAMANHO_DA_CELULA, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));
	}

	i_window.draw(face);
	animation_timer = (1 + animation_timer) % (FRAMES_DA_ANIMACAO_DO_FANTASMA * FANTASMA_VELOCIDADE_DA_ANIMACAO);
}

void Fantasma::reset(const Posicao& i_home, const Posicao& i_home_exit)
{
	movement_mode = 0;
	use_door = 0 < id;
	direction = 0;
	frightened_mode = 0;
	frightened_speed_timer = 0;
	animation_timer = 0;
	home = i_home;
	home_exit = i_home_exit;
	target = i_home_exit;
}

void Fantasma::set_position(short i_x, short i_y)
{
	position = { i_x, i_y };
}

void Fantasma::switch_mode()
{
	movement_mode = 1 - movement_mode;
}

void Fantasma::update(unsigned char i_level, std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_map, Fantasma& i_ghost_0, Pacman& i_pacman)
{
	bool move = 0;
	unsigned char available_ways = 0;
	unsigned char speed = VELOCIDADE_DO_FANTASMA;

	std::array<bool, 4> walls{};

	if (0 == frightened_mode && i_pacman.get_energizer_timer() == ENERGIZER_DURATION / pow(2, i_level))
	{
		frightened_speed_timer = VELOCIDADE_DO_FANTASMA_ASSUSTADO;

		frightened_mode = 1;
	}
	else if (0 == i_pacman.get_energizer_timer() && 1 == frightened_mode)
	{
		frightened_mode = 0;
	}

	if (2 == frightened_mode && 0 == position.x % VELOCIDADE_DO_FANTASMA_FUGINDO && 0 == position.y % VELOCIDADE_DO_FANTASMA_FUGINDO)
	{
		speed = VELOCIDADE_DO_FANTASMA_FUGINDO;
	}

	update_target(i_pacman.get_direction(), i_ghost_0.get_position(), i_pacman.get_posicao());

	walls[0] = colisao_mapa(0, use_door, speed + position.x, position.y, i_map);
	walls[1] = colisao_mapa(0, use_door, position.x, position.y - speed, i_map);
	walls[2] = colisao_mapa(0, use_door, position.x - speed, position.y, i_map);
	walls[3] = colisao_mapa(0, use_door, position.x, speed + position.y, i_map);

	if (1 != frightened_mode)
	{
		unsigned char optimal_direction = 4;
		move = 1;

		for (unsigned char a = 0; a < 4; a++)
		{
			if (a == (2 + direction) % 4)
			{
				continue;
			}
			else if (0 == walls[a])
			{
				if (4 == optimal_direction)
				{
					optimal_direction = a;
				}

				available_ways++;

				if (get_target_distance(a) < get_target_distance(optimal_direction))
				{
					optimal_direction = a;
				}
			}
		}

		if (1 < available_ways)
		{
			direction = optimal_direction;
		}
		else
		{
			if (4 == optimal_direction)
			{
				direction = (2 + direction) % 4;
			}
			else
			{
				direction = optimal_direction;
			}
		}
	}
	else
	{
		unsigned char random_direction = rand() % 4;

		if (0 == frightened_speed_timer)
		{
			move = 1;

			frightened_speed_timer = VELOCIDADE_DO_FANTASMA_ASSUSTADO;

			for (unsigned char a = 0; a < 4; a++)
			{
				if (a == (2 + direction) % 4)
				{
					continue;
				}
				else if (0 == walls[a])
				{
					available_ways++;
				}
			}

			if (0 < available_ways)
			{
				while (1 == walls[random_direction] || random_direction == (2 + direction) % 4)
				{
					random_direction = rand() % 4;
				}

				direction = random_direction;
			}
			else
			{
				direction = (2 + direction) % 4;
			}
		}
		else
		{
			frightened_speed_timer--;
		}
	}

	if (1 == move)
	{
		switch (direction)
		{
		case 0:
		{
			position.x += speed;

			break;
		}
		case 1:
		{
			position.y -= speed;

			break;
		}
		case 2:
		{
			position.x -= speed;

			break;
		}
		case 3:
		{
			position.y += speed;
		}
		}

		if (-TAMANHO_DA_CELULA >= position.x)
		{
			position.x = TAMANHO_DA_CELULA * LARGURA_DO_MAPA - speed;
		}
		else if (position.x >= TAMANHO_DA_CELULA * LARGURA_DO_MAPA)
		{
			position.x = speed - TAMANHO_DA_CELULA;
		}
	}

	if (1 == pacman_collision(i_pacman.get_posicao()))
	{
		if (0 == frightened_mode)
		{
			i_pacman.set_dead(1);
		}
		else 
		{
			use_door = 1;

			frightened_mode = 2;

			target = home;
		}
	}
}

void Fantasma::update_target(unsigned char i_pacman_direction, const Posicao& i_ghost_0_position, const Posicao& i_pacman_position)
{
	if (use_door && position == target) {
		if (home_exit == target) 
		{
			use_door = false;
		}

		if (home == target)
		{
			frightened_mode = false;
			target = home_exit; 
		}

		return;
	}
}
