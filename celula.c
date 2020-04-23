#include "celula.h"
#include <stdlib.h>

Celula *criaCelula(){
	Celula *celula = (Celula*) malloc (sizeof(Celula));
	celula->visivel = 0;
	celula->valor = '*';
	celula->id_barco = -1;
	return celula;
}

void destroiCelula(Celula *celula){
	free(celula);
	celula = NULL;
}
