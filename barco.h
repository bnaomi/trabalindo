#ifndef BARCO_H_INCLUDED
#define BARCO_H_INCLUDED
#include <stdio.h>

typedef struct barco{
  int id;
  int tipo;
  int orientacao;
  int linha;
  int coluna;
  int partes_restantes;
} Barco;

Barco *criaBarco(int id, int tipo, int orientacao, int linha, int coluna, int partes_restantes);
void destroiBarco(Barco *barco);
Barco ***criaMatrizBarcos(FILE *arquivo);
void destroiMatrizBarcos(Barco ***barcos);

#endif //BARCO_H_INCLUDED
