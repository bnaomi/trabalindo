#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

typedef struct ia{
  int pos_base[2];
  int orientacao;
} Ia;

Ia *criaIA();
void destroiIA(Ia *ia);
int busca(int linha, int coluna, Ia *ia, int *prox_pos, Tabuleiro *tabuleiro);
int *proxTiroIA(int* prox_pos, Tabuleiro *tabuleiro_adv, Ia *ia);

#endif //IA_H_INCLUDED