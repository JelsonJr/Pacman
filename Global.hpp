#pragma once

constexpr unsigned char TAMANHO_DA_CELULA = 16;
constexpr unsigned char TAMANHO_DA_FONTE = 16;
constexpr unsigned char SCREEN_RESIZE = 2;
constexpr unsigned char GHOST_1_CHASE = 2;
constexpr unsigned char GHOST_2_CHASE = 1;
constexpr unsigned char GHOST_3_CHASE = 4;
constexpr unsigned char FRAMES_DA_ANIMACAO_DO_FANTASMA = 6;
constexpr unsigned char FANTASMA_VELOCIDADE_DA_ANIMACAO = 4;
constexpr unsigned char VELOCIDADE_DO_FANTASMA_FUGINDO = 4;
constexpr unsigned char VELOCIDADE_DO_FANTASMA_ASSUSTADO = 3;
constexpr unsigned char VELOCIDADE_DO_FANTASMA = 1;
constexpr unsigned char ALTURA_DO_MAPA = 21;
constexpr unsigned char LARGURA_DO_MAPA = 21;
constexpr unsigned char PACMAN_ANIMATION_FRAMES = 6;
constexpr unsigned char PACMAN_ANIMATION_SPEED = 4;
constexpr unsigned char PACMAN_DEATH_FRAMES = 12;
constexpr unsigned char PACMAN_SPEED = 2;

constexpr unsigned short CHASE_DURATION = 1024;
constexpr unsigned short ENERGIZER_DURATION = 512;
constexpr unsigned short FRAME_DURATION = 16667;
constexpr unsigned short GHOST_FLASH_START = 64;
constexpr unsigned short LONG_SCATTER_DURATION = 512;
constexpr unsigned short SHORT_SCATTER_DURATION = 256;

enum Celula
{
	porta,
	vazio,
	energizador,
	comida,
	parede
};

struct Posicao
{
	short x;
	short y;

	bool operator == (const Posicao& i_position)
	{
		return this->x == i_position.x && this->y == i_position.y;
	}
};