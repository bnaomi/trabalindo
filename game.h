#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "jogador.h"
#include "ia.h"

typedef struct game{
	Jogador *jogador_1;
	Jogador *jogador_2;
	Ia *ia;
	int fim_jogo;
} Game;

Game *criaGame(char *tabuleiro1, char *tabuleiro2);
void destroiGame(Game *game);
void atirarPlayer(Game *game, int jogador_id);
void jogo();

#endif //GAME_H_INCLUDED