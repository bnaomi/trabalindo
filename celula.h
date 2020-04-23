#ifndef CELULA_H_INCLUDED
#define CELULA_H_INCLUDED

typedef struct celula{
	int visivel;
	char valor;
	int id_barco;
} Celula;

Celula *criaCelula();
void destroiCelula(Celula *celula);

#endif //CELULA_H_INCLUDED
