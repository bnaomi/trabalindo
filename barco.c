#include "barco.h"
#include "arquivo.h"
#include <stdlib.h>
#include <stdio.h>
Barco *criaBarco(int id, int tipo, int orientacao, int linha, int coluna, int partes_restantes){
  Barco *barco = (Barco*) malloc (sizeof(Barco));
  barco->id = id;
  barco->tipo = tipo;
  barco->orientacao = orientacao;
  barco->linha = linha;
  barco->coluna = coluna;
  barco->partes_restantes = partes_restantes;
  return barco;
}

/*
**   As linhas da matriz "barcos" representam os tipos das embarcações
**   As colunas representam IDs das embarcações daquele tipo
**   Ex: barcos[0][5] aponta para uma boia de ID 5
**       barcos[4][2] aponta para um espião de ID 2
*/

void destroiBarco(Barco *barco){
  free(barco);
  barco = NULL;
}

Barco ***criaMatrizBarcos(FILE *arquivo){

  Barco ***barcos = (Barco***) malloc (sizeof(Barco**) * 6); //aloca espaço para 6 tipos de embarcações
  barcos[0] = (Barco**) malloc (sizeof(Barco*)*10); //aloca 10 posições (boias)
  barcos[1] = (Barco**) malloc (sizeof(Barco*)*5); //aloca 5 posições (aviões)
  barcos[2] = (Barco**) malloc (sizeof(Barco*)*5); //aloca 5 posições (submarinos)
  barcos[3] = (Barco**) malloc (sizeof(Barco*)*4); //aloca 4 posições (espiões tipo 1)
  barcos[4] = (Barco**) malloc (sizeof(Barco*)*4); //aloca 4 posições (espiões tipo 2)
  barcos[5] = (Barco**) malloc (sizeof(Barco*)*2); //aloca 2 posições (porta-aviões)
  leArquivo(arquivo, barcos);
  return barcos;
}

void destroiMatrizBarcos(Barco ***barcos){
  int i, j, qtde_pos[6] = {10, 5, 5, 4, 4, 2};
  for(i=0; i < 6; i++){
    for(j=0; j < qtde_pos[i]; j++){
      destroiBarco(barcos[i][j]);
      barcos[i][j] = NULL;
    }
    free(barcos[i]);
    barcos[i] = NULL;
  }
  free(barcos);
  barcos = NULL;
}
