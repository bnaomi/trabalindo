#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED
#include "celula.h"
#include "barco.h"

typedef struct tabuleiro{
	int linhas;
	int colunas;
	Celula ***matriz_campo;
} Tabuleiro;

Tabuleiro *criaTabuleiro(int linhas, int colunas, char *entrada);
void destroiTabuleiro(Tabuleiro *tabuleiro);
void setVisivel(Tabuleiro *tabuleiro, int linha, int coluna);
void setValorID(Tabuleiro *tabuleiro, int linha, int coluna, char valor, int id);
void posicionaBoia(Tabuleiro *tabuleiro, Barco ***barcos);
void posicionaAviao(Tabuleiro *tabuleiro, Barco ***barcos);
void posicionaSubmarino(Tabuleiro *tabuleiro, Barco ***barcos);
void posicionaEspiao(Tabuleiro *tabuleiro, Barco ***barcos);
void posicionaPortaAviao(Tabuleiro *tabuleiro, Barco ***barcos);
void posiciona(Tabuleiro *tabuleiro, Barco ***barcos);
void printarTabuleiro(Tabuleiro *tabuleiro);

#endif //TABULEIRO_H_INCLUDED
