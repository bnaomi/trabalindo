#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
#include "tabuleiro.h"

typedef struct jogador{
	int id;
	int vencedor;
	int frota_total;
	Tabuleiro *tabuleiro;
} Jogador;

Jogador *criaJogador(int id, char *entrada);
void destroiJogador(Jogador *jogador);

#endif //JOGADOR_H_INCLUDED
