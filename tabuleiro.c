#include "arquivo.h"
#include "celula.h"
#include "barco.h"
#include "tabuleiro.h"
#include <stdlib.h>
#include <stdio.h>

Tabuleiro *criaTabuleiro(int linhas, int colunas, char *entrada){
  FILE *arquivo = openFile(entrada, "r");
  Tabuleiro *tabuleiro = (Tabuleiro*) malloc (sizeof(Tabuleiro));
  tabuleiro->linhas = linhas;
  tabuleiro->colunas = colunas;

  //aloca matriz_campo
  int i, j;
  tabuleiro->matriz_campo = (Celula***) malloc (sizeof(Celula**) * tabuleiro->linhas);//aloca um vetor de tamanho[linhas]

  //para cada posição do vetor alocado na linha de cima aloca um vetor de tamanho[colunas]
  for(i=0; i < tabuleiro->linhas; i++){
    tabuleiro->matriz_campo[i] = (Celula**) malloc (sizeof(Celula*) * tabuleiro->colunas);
  }

  //preenche a matriz_campo
  for(i=0; i < tabuleiro->linhas; i++){
    for(j=0; j < tabuleiro->colunas; j++){
      tabuleiro->matriz_campo[i][j] = criaCelula();
    }
  }

  Barco ***barcos = criaMatrizBarcos(arquivo);
  posiciona(tabuleiro, barcos);
  fclose(arquivo);

  return tabuleiro;
}

void destroiTabuleiro(Tabuleiro *tabuleiro){
  int i, j;
  for(i=0; i < tabuleiro->linhas; i++){
    for(j=0; j < tabuleiro->colunas; j++){
      destroiCelula(tabuleiro->matriz_campo[i][j]);
    }
    free(tabuleiro->matriz_campo[i]);
    tabuleiro->matriz_campo[i] = NULL;
  }
  free(tabuleiro->matriz_campo);
  tabuleiro->matriz_campo = NULL;
  free(tabuleiro);
  tabuleiro = NULL;
}

void setVisivel(Tabuleiro *tabuleiro, int linha, int coluna){
  tabuleiro->matriz_campo[linha][coluna]->visivel = 1;
}

void setValorID(Tabuleiro *tabuleiro, int linha, int coluna, char valor, int id){
	tabuleiro->matriz_campo[linha][coluna]->valor = valor;
  tabuleiro->matriz_campo[linha][coluna]->id_barco = id;
}

void posicionaBoia(Tabuleiro *tabuleiro, Barco ***barcos){ //barcos[0]
  int i;
  for(i=0; i < 10; i++){
    setValorID(tabuleiro, barcos[0][i]->linha, barcos[0][i]->coluna, '0', i);
  }
}

void posicionaAviao(Tabuleiro *tabuleiro, Barco ***barcos){ //barcos[1]
  int i;
  for(i=0; i < 5; i++){ //posiciona 5 aviões
    if(barcos[1][i]->orientacao == 0){ //se for norte
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna - 1, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna + 1, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha + 1, barcos[1][i]->coluna, '1', i);
    }
    if(barcos[1][i]->orientacao == 1){ //se for sul
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna - 1, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna + 1, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha - 1, barcos[1][i]->coluna, '1', i);
    }
    if(barcos[1][i]->orientacao == 2){ //se for oeste
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha - 1, barcos[1][i]->coluna, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha + 1, barcos[1][i]->coluna, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna + 1, '1', i);
    }
    if(barcos[1][i]->orientacao == 3){ //se for leste
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha - 1, barcos[1][i]->coluna, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha + 1, barcos[1][i]->coluna, '1', i);
        setValorID(tabuleiro, barcos[1][i]->linha, barcos[1][i]->coluna - 1, '1', i);
    }
  }
}

void posicionaSubmarino(Tabuleiro *tabuleiro, Barco ***barcos){ //barcos[2]
  int i, j;
  for(i=0; i < 5; i++){ //posiciona 5 submarinos
    if(barcos[2][i]->orientacao == 0){ //se for norte
      for(j=0; j < 4; j++){
        setValorID(tabuleiro, barcos[2][i]->linha + j, barcos[2][i]->coluna, '2', i);
      }
    }
    if(barcos[2][i]->orientacao == 1){ //se for sul
      for(j=0; j < 4; j++){
        setValorID(tabuleiro, barcos[2][i]->linha - j, barcos[2][i]->coluna, '2', i);
      }
    }
    if(barcos[2][i]->orientacao == 2){ //se for oeste
      for(j=0; j < 4; j++){
        setValorID(tabuleiro, barcos[2][i]->linha, barcos[2][i]->coluna + j, '2', i);
      }
    }
    if(barcos[2][i]->orientacao == 3){ //se for leste
      for(j=0; j < 4; j++){
        setValorID(tabuleiro, barcos[2][i]->linha, barcos[2][i]->coluna - j, '2', i);
      }
    }
  }
}

void posicionaEspiao(Tabuleiro *tabuleiro, Barco ***barcos){ //barcos[3] e barcos[4]
  int i, j;
  void posic(Tabuleiro *tabuleiro, Barco ***barcos, int tipo){
    for (i = 0; i < 4; i++) { //posiciona 4 espiões
      if(barcos[tipo][i]->orientacao == 0){ //se for norte
        for(j=0; j < 4; j++){
          setValorID(tabuleiro, barcos[tipo][i]->linha - j, barcos[tipo][i]->coluna, '0'+tipo, i);
        }
        setValorID(tabuleiro, barcos[tipo][i]->linha, barcos[tipo][i]->coluna - 1, '0'+tipo, i);
        setValorID(tabuleiro, barcos[tipo][i]->linha, barcos[tipo][i]->coluna + 1, '0'+tipo, i);
      }
      if(barcos[tipo][i]->orientacao == 1){ //se for sul
        for(j=0; j < 4; j++){
          setValorID(tabuleiro, barcos[tipo][i]->linha + j, barcos[tipo][i]->coluna, '0'+tipo, i);
        }
        setValorID(tabuleiro, barcos[tipo][i]->linha, barcos[tipo][i]->coluna - 1, '0'+tipo, i);
        setValorID(tabuleiro, barcos[tipo][i]->linha, barcos[tipo][i]->coluna + 1, '0'+tipo, i);
      }
      if(barcos[tipo][i]->orientacao == 2){ //se for oeste
        for(j=0; j < 4; j++){
          setValorID(tabuleiro, barcos[tipo][i]->linha, barcos[tipo][i]->coluna - j, '0'+tipo, i);
        }
        setValorID(tabuleiro, barcos[tipo][i]->linha - 1, barcos[tipo][i]->coluna, '0'+tipo, i);
        setValorID(tabuleiro, barcos[tipo][i]->linha + 1, barcos[tipo][i]->coluna, '0'+tipo, i);
      }
      if(barcos[tipo][i]->orientacao == 3){ //se for leste
        for(j=0; j < 4; j++){
          setValorID(tabuleiro, barcos[tipo][i]->linha, barcos[tipo][i]->coluna + j, '0'+tipo, i);
        }
        setValorID(tabuleiro, barcos[tipo][i]->linha - 1, barcos[tipo][i]->coluna, '0'+tipo, i);
        setValorID(tabuleiro, barcos[tipo][i]->linha + 1, barcos[tipo][i]->coluna, '0'+tipo, i);
      }
    }
  }
  posic(tabuleiro, barcos, 3); //posiciona espião tipo 1
  posic(tabuleiro, barcos, 4); //posiciona espião tipo 2
}

void posicionaPortaAviao(Tabuleiro *tabuleiro, Barco ***barcos){ //barcos[5]
  int i, j;

  //Posição de origem escolhida: xxxx@
  //                             xxxxx

  for(i=0; i < 2; i++){ //posiciona 2 porta-aviões
    if(barcos[5][i]->orientacao == 0){ //se for norte
      for(j=0; j < 5; j++){
        setValorID(tabuleiro, barcos[5][i]->linha + j, barcos[5][i]->coluna, '5', i);
        setValorID(tabuleiro, barcos[5][i]->linha + j , barcos[5][i]->coluna + 1, '5', i);
      }
    }
    if(barcos[5][i]->orientacao == 1){ //se for sul
      for(j=0; j < 5; j++){
        setValorID(tabuleiro, barcos[5][i]->linha - j, barcos[5][i]->coluna, '5', i);
        setValorID(tabuleiro, barcos[5][i]->linha - j, barcos[5][i]->coluna - 1, '5', i);
      }
    }
    if(barcos[5][i]->orientacao == 2){ //se for oeste
      for(j=0; j < 5; j++){
        setValorID(tabuleiro, barcos[5][i]->linha, barcos[5][i]->coluna + j, '5', i);
        setValorID(tabuleiro, barcos[5][i]->linha - 1, barcos[5][i]->coluna + j, '5', i);
      }
    }
    if(barcos[5][i]->orientacao == 3){ //se for leste
      for(j=0; j < 5; j++){
        setValorID(tabuleiro, barcos[5][i]->linha, barcos[5][i]->coluna - j, '5', i);
        setValorID(tabuleiro, barcos[5][i]->linha + 1, barcos[5][i]->coluna - j, '5', i);
      }
    }
  }
}

void posiciona(Tabuleiro *tabuleiro, Barco ***barcos){
  posicionaPortaAviao(tabuleiro, barcos);
  posicionaEspiao(tabuleiro, barcos);
  posicionaAviao(tabuleiro, barcos);
  posicionaSubmarino(tabuleiro, barcos);
  posicionaBoia(tabuleiro, barcos);
}

void printarTabuleiro(Tabuleiro *tabuleiro){
  int i, j;
  printf("   ");
  for(i=0; i < tabuleiro->colunas; i++){
    printf("%c ", i+65); //printa letras
  }
  printf("\n");
  for(i=0; i < tabuleiro->linhas; i++){
    if(i < 10)
      printf(" ");
    printf("%d ", i); //printa números
    for(j=0; j < tabuleiro->colunas; j++){
      if(tabuleiro->matriz_campo[i][j]->visivel)
        printf("%c ", tabuleiro->matriz_campo[i][j]->valor);
      else{
        printf("# ");
      }
    }
    printf("\n");
  }
  printf("\n");
}