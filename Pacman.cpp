#include "Pacman.hpp"

Pacman::Pacman() :
	animation_over(0),
	morto(0),
	direcao(0),
	energizer_timer(0),
	posicao({ 0, 0 })
{}

Posicao Pacman::get_posicao() const
{
	return posicao;
}

bool Pacman::get_animation_over() const
{
	return animation_over;
}

bool Pacman::get_dead() const
{
	return morto;
}

unsigned char Pacman::get_direction() const
{
	return direcao;
}

unsigned short Pacman::get_energizer_timer() const
{
	return energizer_timer;
}

void Pacman::draw(bool i_victory, sf::RenderWindow& i_window)
{
	unsigned char frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(PACMAN_ANIMATION_SPEED)));
	sf::Sprite sprite;
	sf::Texture texture;

	sprite.setPosition(posicao.x, posicao.y);

	if (morto || i_victory)
	{
		if (animation_timer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED)
		{
			animation_timer++;
			texture.loadFromFile("PacmanDeath" + std::to_string(TAMANHO_DA_CELULA) + ".png");

			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(TAMANHO_DA_CELULA * frame, 0, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));
			i_window.draw(sprite);
			
			return;
		}
		
		animation_over = 1;
		return;
	}
	
	texture.loadFromFile("Pacman" + std::to_string(TAMANHO_DA_CELULA) + ".png");

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(TAMANHO_DA_CELULA * frame, TAMANHO_DA_CELULA * direcao, TAMANHO_DA_CELULA, TAMANHO_DA_CELULA));
	i_window.draw(sprite);

	animation_timer = (1 + animation_timer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED);
}

void Pacman::reset()
{
	animation_over = 0;
	morto = 0;
	direcao = 0;
	animation_timer = 0;
	energizer_timer = 0;
}

void Pacman::set_animation_timer(unsigned short i_animation_timer)
{
	animation_timer = i_animation_timer;
}

void Pacman::set_dead(bool i_dead)
{
	morto = i_dead;

	if (morto)
	{
		animation_timer = 0;
	}
}

void Pacman::set_posicao(short i_x, short i_y)
{
	posicao = { i_x, i_y };
}

void Pacman::update(unsigned char i_level, std::array<std::array<Celula, ALTURA_DO_MAPA>, LARGURA_DO_MAPA>& i_mapa)
{
	std::array<bool, 4> paredes{};
	paredes[0] = colisao_mapa(0, 0, PACMAN_SPEED + posicao.x, posicao.y, i_mapa);
	paredes[1] = colisao_mapa(0, 0, posicao.x, posicao.y - PACMAN_SPEED, i_mapa);
	paredes[2] = colisao_mapa(0, 0, posicao.x - PACMAN_SPEED, posicao.y, i_mapa);
	paredes[3] = colisao_mapa(0, 0, posicao.x, PACMAN_SPEED + posicao.y, i_mapa);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !paredes[0])
	{
		direcao = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !paredes[1])
	{
		direcao = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !paredes[2])
	{
		direcao = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !paredes[3])
	{
		direcao = 3;
	}

	if (!paredes[direcao]) 
	{
		switch (direcao) {
			case 0: posicao.x += PACMAN_SPEED; break;
			case 1: posicao.y -= PACMAN_SPEED; break;
			case 2: posicao.x -= PACMAN_SPEED; break;
			case 3: posicao.y += PACMAN_SPEED; break;
		}
	}

	if (-TAMANHO_DA_CELULA >= posicao.x)
	{
		posicao.x = TAMANHO_DA_CELULA * LARGURA_DO_MAPA - PACMAN_SPEED;
	}
	else if (TAMANHO_DA_CELULA * LARGURA_DO_MAPA <= posicao.x)
	{
		posicao.x = PACMAN_SPEED - TAMANHO_DA_CELULA;
	}

	if (colisao_mapa(1, 0, posicao.x, posicao.y, i_mapa))
	{
		energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION / pow(2, i_level));
		return;
	}
	
	energizer_timer = std::max(0, energizer_timer - 1);
}
