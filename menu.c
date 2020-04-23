#include <stdio.h>
#include "menu.h"
#include "arquivo.h"
#include "game.h"

void print_menu(){
  int opcao;
  do {
    printf("\n    BATALHA NAVAL\n");
    printf("  1 - Gerar novos tabuleiros.\n");
    printf("  2 - Iniciar jogo.\n");
    printf("  3 - Instruções.\n");
    printf("  4 - Créditos.\n");
    printf("  0 - Sair.\n");
    printf("_:");
    scanf("%d", &opcao);

    switch (opcao){
      case 1:
        geraArquivo("tabuleiro1.txt");
        geraArquivo("tabuleiro2.txt");
        printf("  Tabuleiros prontos!\n");
        printf("\n");
        break;
      case 2:
        jogo();
        printf("\n");
        break;
      case 3:
        printf("\n    Bem-vindo\n");
        printf("  Para jogar, basta escrever o número da linha que deseja acertar e aperte ENTER,\n");
        printf("  e após isso a respectiva letra maiúscula da coluna e aperte ENTER.\n\n");
        printf("    --Legendas--\n");
        printf("  *: Posição não descoberta.\n");
        printf("  #: Tiro na água.\n");
        printf("  0: Boia atingida.\n");
        printf("  1: Avião atingido.\n");
        printf("  2: Submarino atingido.\n");
        printf("  3: Espião1 atingido.\n");
        printf("  4: Espião2 atingido.\n");
        printf("  5: Porta-aviões atingido.\n\n");
        break;
      case 4:
        printf("\n  Créditos da Batalha Naval :) \n");
        printf("  Jogo feito para a matéria de Fundamentos de programação 1.\n");
        printf("    Professor: Jeferson José Baqueta\n\n");
        printf("  Alunos:\n");
        printf("    Bruna Naomi Yamanaka Silva \n");
        printf("    Lucas Lourenção Targa\n\n");
        printf("  Curitiba, 03 de dezembro de 2018\n\n");
        break;
      case 0:
        break;
      default:
        printf("Opção inválida. :(\n");
    }
  } while(opcao != 0);
}
