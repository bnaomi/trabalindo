#include "tabuleiro.h"
#include "jogador.h"
#include "ia.h"
#include "game.h"
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#define TABULEIRO_1 "tabuleiro1.txt"
#define TABULEIRO_2 "tabuleiro2.txt"
#define ID_JOGADOR_1 1
#define ID_JOGADOR_2 2

Game *criaGame(char *tabuleiro1, char *tabuleiro2){
  Game *game = (Game*) malloc (sizeof(Game));
  game->jogador_1 = criaJogador(1, tabuleiro1);
  game->jogador_2 = criaJogador(2, tabuleiro2);
  game->ia = criaIA();
  game->fim_jogo = 0;

  printarTabuleiro(game->jogador_1->tabuleiro);
  printf("\n");
  printarTabuleiro(game->jogador_2->tabuleiro);

  return game;
}

void destroiGame(Game *game){
  destroiJogador(game->jogador_1);
  destroiJogador(game->jogador_2);
  free(game);
  game = NULL;
}

void atirarPlayer(Game *game, int jogador_id){
  int linha, coluna, prox_pos[2];
  Jogador *adv;
  char c;
  Ia *ia;

    if(jogador_id == 1)
    {
        adv = game->jogador_2;
        do
        {
            printf("LINHA do proximo tiro: ");
            scanf("%d", &linha);
            setbuf(stdin,NULL);
            printf("COLUNA do proximo tiro: ");
            scanf("%c", &c);
            setbuf(stdin,NULL);
            coluna = (c-65);

            if((linha<0)||(linha>19)||(coluna<0)||(coluna>19))
            {
                do{
                  printf("Coordenada invalida. Tente linhas entre 0 e 19, e colunas entre A e T.\n");
                  printf("LINHA do proximo tiro: ");
                  scanf("%d", &linha);
                  setbuf(stdin,NULL);
                  printf("COLUNA do proximo tiro: ");
                  scanf("%c", &c);
                  setbuf(stdin,NULL);
                  coluna = (c-65);
                }while((linha<0)||(linha>19)||(coluna<0)||(coluna>19));
                continue;
            }
            if(adv->tabuleiro->matriz_campo[linha][coluna]->visivel)
            {
                printf("Essa coordenada ja foi atingida.\n\n");
            }
        }
        while(adv->tabuleiro->matriz_campo[linha][coluna]->visivel);

        printf("Sua jogada -> x: %d, y: %d\n\n", linha, coluna);
        setVisivel(adv->tabuleiro, linha, coluna);
        if(adv->tabuleiro->matriz_campo[linha][coluna]->valor != '*')
        {
            printf("Voce acertou uma embarcacao inimiga!\n\n");
            adv->frota_total--;
        }
        else
        {
            printf("Tiro na agua!\n\n");
        }
        printf("Tabuleiro do adversario:\n\n");
        printarTabuleiro(adv->tabuleiro);
        printf("\n\n");
        if(adv->frota_total == 0){
          game->jogador_1->vencedor = 1;
          game->fim_jogo = 1;
        }
    }
    if(jogador_id == 2) //se for IA
    {
        adv = game->jogador_1;
        ia = game->ia;
        /* tiro aleatório
        do
        {
            linha = rand()%20;
            coluna = rand()%20;
        }
        while (adv->tabuleiro->matriz_campo[linha][coluna]->visivel);
        */
        proxTiroIA(prox_pos, adv->tabuleiro, ia);
        linha = prox_pos[0];
        coluna = prox_pos[1];
        printf("Jogada do adversario -> x: %d, y: %d\n", linha, coluna);
        setVisivel(adv->tabuleiro, linha, coluna);
        if(adv->tabuleiro->matriz_campo[linha][coluna]->valor != '*')
        {
            printf("Adversario acertou sua embarcacao!\n\n");
            adv->frota_total--;
        }
        else
        {
            printf("Adversario acertou na agua!\n\n");
        }
        printf("Tabuleiro do player:\n\n");
        printarTabuleiro(adv->tabuleiro);
        printf("\n\n");
        if(adv->frota_total == 0){
          game->jogador_2->vencedor = 1;
          game->fim_jogo = 1;
        }
  }
}

void jogo(){
  Game *game = criaGame(TABULEIRO_1, TABULEIRO_2);
  int rodadas =1;
  srand(time(NULL));
  do{
		atirarPlayer(game, ID_JOGADOR_1);
		atirarPlayer(game, ID_JOGADOR_2);
		rodadas++;
        printf("------- RODADA %d ---------\n", rodadas);
	}while(!game->fim_jogo);
  printf("FIM DE JOGO!\n");
  printf("Vencedor: ");
  game->jogador_1->vencedor ? printf("Você venceu! :D\n") : printf("Você perdeu. :(\n");
  destroiGame(game);
}
