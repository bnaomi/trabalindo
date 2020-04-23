#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED
#include <stdio.h>
#include "barco.h"

FILE *openFile(char *nomearquivo, char *modo);
int rand_sentido();
int rand_xy();
void geraArquivo(char *nomearquivo);
void leArquivo(FILE *arquivo, Barco ***barcos);
#endif //ARQUIVO_H_INCLUDED