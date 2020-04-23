#include "arquivo.h"
#include "barco.h"
#include "tabuleiro.h"
#include "ia.h"
#include <stdlib.h>

Ia *criaIA(){
  Ia *ia = (Ia*) malloc (sizeof(Ia));
  ia->pos_base[0] = -1;
  ia->pos_base[1] = -1;
  ia->orientacao = rand_sentido();
  return ia;
}

void destroiIA(Ia *ia){
  free(ia);
  ia = NULL;
}

int busca(int linha, int coluna, Ia *ia, int *prox_pos, Tabuleiro *tabuleiro){
  if( (linha == -1) || (coluna == -1) || (linha == 20) || (coluna == 20) ){
    return 0;
  }
  //se a posição já foi atingida e for água
  if( (tabuleiro->matriz_campo[linha][coluna]->visivel) && (tabuleiro->matriz_campo[linha][coluna]->valor == '*') ){
    return 0;
  }
  //se a posição já foi atingida e for barco
  if( (tabuleiro->matriz_campo[linha][coluna]->visivel) && (tabuleiro->matriz_campo[linha][coluna]->valor != '*')){
    if(ia->orientacao == 0){ //NORTE
      return busca(linha-1, coluna, ia, prox_pos, tabuleiro);
    }
    if(ia->orientacao == 1){ //SUL
      return busca(linha+1, coluna, ia, prox_pos, tabuleiro);
    }
    if(ia->orientacao == 2){ //OESTE
      return busca(linha, coluna-1, ia, prox_pos, tabuleiro);
    }
    if(ia->orientacao == 3){ //LESTE
      return busca(linha, coluna+1, ia, prox_pos, tabuleiro);
    }
  }
  //se a posição ainda não tiver sido atingida
  if((tabuleiro->matriz_campo[linha][coluna]->visivel) == 0){
    prox_pos[0] = linha;
    prox_pos[1] = coluna;
    return 1;
  }
  return 0;
}

int *proxTiroIA(int *prox_pos, Tabuleiro *tabuleiro_adv, Ia *ia){
  /* Se ainda não acertou um barco, retorna uma posição aleatória
     e se a posição retornada tiver um barco, salva a coordenada para próximos tiros */
  if(ia->pos_base[0] == -1){
    prox_pos[0] = rand_xy();
    prox_pos[1] = rand_xy();
    if( (tabuleiro_adv->matriz_campo[prox_pos[0]][prox_pos[1]]->valor != '*') && (tabuleiro_adv->matriz_campo[prox_pos[0]][prox_pos[1]]->valor != '0')){
      ia->pos_base[0] = prox_pos[0];
      ia->pos_base[1] = prox_pos[1];
    }
    return prox_pos;
  }

  int i = 0;
  while( (busca(ia->pos_base[0], ia->pos_base[1], ia, prox_pos, tabuleiro_adv) == 0) && i < 5){
    ia->orientacao = ((ia->orientacao)+1)%4;
    i++;
  }
  if(i==5){
    ia->pos_base[0] = -1;
    ia->pos_base[1] = -1;
    prox_pos[0] = rand_xy();
    prox_pos[1] = rand_xy();
  }

  return prox_pos;
}