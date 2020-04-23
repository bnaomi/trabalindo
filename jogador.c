#include "tabuleiro.h"
#include "jogador.h"
#include <stdlib.h>

Jogador *criaJogador(int id, char* entrada){
  Jogador *jogador = (Jogador*) malloc (sizeof(Jogador));
  jogador->tabuleiro = criaTabuleiro(20, 20, entrada);
  jogador->id = id;
  jogador->vencedor = 0;
  jogador->frota_total = 118;
  return jogador;
}

void destroiJogador(Jogador *jogador){
  destroiTabuleiro(jogador->tabuleiro);
  free(jogador);
  jogador = NULL;
}