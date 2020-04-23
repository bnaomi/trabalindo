#include "arquivo.h"
#include "barco.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *openFile(char *nomearquivo, char *modo){
    FILE *arquivo = fopen(nomearquivo, modo);
    if (arquivo!=NULL){
        return (arquivo);
    }
    else{
        printf("Erro ao abrir o arquivo de entrada. :(\n");
        return (NULL);
    }
}

int rand_sentido(){
    return rand()%4;
}

int rand_xy(){
    return rand()%20;
}

void geraArquivo(char *nomearquivo){
  int linha, i, j, coluna, sentido,sobrepoe;
  int aux=0;
  char id='4';
  sobrepoe=0;
  FILE *arquivo = openFile(nomearquivo, "w");
  //cria matriz
  char matriz[20][20];
  for(linha=0; linha<20; linha++){
    for (coluna=0; coluna<20; coluna++){
      matriz[linha][coluna]='*';
    }
  }
  //Posição origem escolhida: xxxx@
  //                          xxxxx
//porta aviao
    i=0;
      while(i < 2)
      {
          do
          {
              sentido = rand_sentido();
              linha = rand_xy();
              coluna = rand_xy();
          }
          while(matriz[linha][coluna]!='*');
      if(sentido == 0)  //NORTE
      {
        for(j=0; j<5; j++){
            if((matriz[linha+j][coluna]!='*')||(matriz[linha+j][coluna+1]!='*')||(linha>15)||(coluna>18)){
                sobrepoe = 1;
                break;
            }
        }
        if(!sobrepoe){
            for(j=0; j < 5; j++){
                matriz[linha+j][coluna] = '5';
                matriz[linha+j][coluna+1] = '5';
            }
            fprintf(arquivo, "%d %c %d %d %d\n", i, '5', sentido, linha, coluna);
            i++;
        }
        sobrepoe = 0;
    }
      if(sentido == 1)  //SUL
      {
          for(j=0; j < 5; j++){
              if((matriz[linha-j][coluna]!='*')||(matriz[linha-j][coluna-1]!='*')||(coluna<1)||(linha<4)){
                  sobrepoe = 1;
                  break;
              }
          }
          if(!sobrepoe){
              for(j=0; j < 5; j++){
                  matriz[linha-j][coluna] = '5';
                  matriz[linha-j][coluna-1] = '5';
              }
              fprintf(arquivo, "%d %c %d %d %d\n", i, '5', sentido, linha, coluna);
              i++;
          }
          sobrepoe = 0;
      }
      if(sentido == 2)  //OESTE
      {
          for(j=0; j < 5; j++){
              if((matriz[linha-1][coluna+j]!='*')||(matriz[linha][coluna+j]!='*')||(linha<1)||(coluna>15)){
                  sobrepoe = 1;
                  break;
              }
          }
          if(!sobrepoe){
              for(j=0; j < 5; j++){
                  matriz[linha][coluna+j] = '5';
                  matriz[linha-1][coluna+j] = '5';
              }
              fprintf(arquivo, "%d %c %d %d %d\n", i, '5', sentido, linha, coluna);
              i++;
          }
          sobrepoe = 0;
      }
      if(sentido == 3)  //LESTE
      {
      for(j=0; j < 5; j++){
              if((matriz[linha+1][coluna-j]!='*')||(matriz[linha][coluna-j]!='*')||(linha>18)||(coluna<4)){
                  sobrepoe = 1;
                  break;
              }
          }
          if(!sobrepoe){
              for(j=0; j < 5; j++){
                  matriz[linha][coluna-j] = '5';
                  matriz[linha+1][coluna-j] = '5';
              }
              fprintf(arquivo, "%d %c %d %d %d\n", i, '5', sentido, linha, coluna);
              i++;
          }
          sobrepoe = 0;
      }
    }

    i=0;
    //espiao1 e 2
        while(i<8){
            if(i>3)
            {
                id='3';
                aux=(i-4);
            }
            do
            {
                linha = rand_xy();
                coluna = rand_xy();
                sentido= rand_sentido();
            }
            while( matriz[linha][coluna] != '*' );
            if(sentido == 0)  //NORTE
            {
                for(j=0; j < 4; j++)
                {
                    if(matriz[linha-j][coluna] != '*'||(linha<3)||(coluna==19)||(coluna==0))
                    {
                        sobrepoe = 1;
                        break;
                    }
                }
                if((matriz[linha][coluna-1] != '*')||(matriz[linha][coluna+1]!='*'))
                {
                    sobrepoe = 1;
                }

                if(!sobrepoe)  //se nÃ£o sobrepÃµe, posiciona espiÃ£o
                {
                    for(j=0; j < 4; j++){
                    matriz[linha-j][coluna] = id;
                    }
                    matriz[linha][coluna] = id;
                    matriz[linha][coluna-1] = id;
                    matriz[linha][coluna+1] = id;
                    fprintf(arquivo, "%d %c %d %d %d\n", aux, id, sentido, linha, coluna);
                    i++;
                    aux++;
                }
                sobrepoe = 0;
            }
            if(sentido == 1)  //SUL
            {
                for(j=0; j < 4; j++)
                {
                    if((matriz[linha+j][coluna]!='*')||(linha>16)||(coluna==19)||(coluna==0))
                    {
                        sobrepoe = 1;
                        break;
                    }
                }
                if((matriz[linha][coluna-1]!='*')||(matriz[linha][coluna+1]!='*'))
                {
                    sobrepoe = 1;
                }

                if(!sobrepoe)  //se nÃ£o sobrepÃµe, posiciona espiÃ£o
                {
                    for(j=0; j < 4; j++){
                    matriz[linha+j][coluna] = id;
                    }
                    matriz[linha][coluna] = id;
                    matriz[linha][coluna-1] = id;
                    matriz[linha][coluna+1] = id;
                    fprintf(arquivo, "%d %c %d %d %d\n", aux, id, sentido, linha, coluna);
                    i++;
                    aux++;
                }
                sobrepoe = 0;
            }
            if(sentido == 2)  //OESTE
            {
                for(j=0; j < 4; j++)
                {
                    if((matriz[linha][coluna-j]!='*')||(linha==0)||(linha==19)||(coluna<3))
                    {
                        sobrepoe = 1;
                        break;
                    }
                }
                if( (matriz[linha-1][coluna] != '*') || (matriz[linha+1][coluna] != '*') )
                {
                    sobrepoe = 1;
                }

                if(!sobrepoe)  //se nÃ£o sobrepÃµe, posiciona espiÃ£o
                {
                    for(j=0; j < 4; j++){
                    matriz[linha][coluna-j] = id;
                    }
                    matriz[linha][coluna] = id;
                    matriz[linha-1][coluna] = id;
                    matriz[linha+1][coluna] = id;
                    fprintf(arquivo, "%d %c %d %d %d\n", aux, id, sentido, linha, coluna);
                    i++;
                    aux++;
                }
                sobrepoe = 0;
            }
            if(sentido == 3)  //LESTE
            {
                for(j=0; j < 4; j++)
                {
                    if((matriz[linha][coluna+j] != '*')||(linha==0)||(linha==19)||(coluna>16))
                    {
                        sobrepoe = 1;
                        break;
                    }
                }
                if((matriz[linha-1][coluna]!='*')||(matriz[linha+1][coluna] != '*') )
                {
                    sobrepoe = 1;
                }

                if(!sobrepoe)  //se nÃ£o sobrepÃµe, posiciona espiÃ£o
                {
                    for(j=0; j < 4; j++){
                    matriz[linha][coluna+j] = id;
                    }
                    matriz[linha][coluna] = id;
                    matriz[linha-1][coluna] = id;
                    matriz[linha+1][coluna] = id;
                    fprintf(arquivo, "%d %c %d %d %d\n", aux, id, sentido, linha, coluna);
                    i++;
                    aux++;
                }
                sobrepoe = 0;
            }
        }



  //submarino
    i=0;
    while(i<5){
      do{
        linha = rand_xy();
        coluna = rand_xy();
        sentido= rand_sentido();
      }while(matriz[linha][coluna]!='*');

    if(sentido == 0){  //NORTE
      //verifica se a posição é INVÁLIDA
      if((matriz[linha+1][coluna]!='*')||(matriz[linha+2][coluna]!='*')||(matriz[linha+3][coluna]!='*')||(linha>16)){
        continue;
      }
      else{ //posiciona submarino
        matriz[linha][coluna] = '2';
        matriz[linha+1][coluna] = '2';
        matriz[linha+2][coluna] = '2';
        matriz[linha+3][coluna] = '2';
        fprintf(arquivo, "%d %c %d %d %d\n", i, '2', sentido, linha, coluna);
        i++;
      }
    }
    if(sentido == 1){ //SUL
      //verifica se a posição é INVÁLIDA
      if((matriz[linha-1][coluna]!='*')||(matriz[linha-2][coluna]!='*')||(matriz[linha-3][coluna]!='*')||(linha<3)){
        continue;
      }
      else{ //posiciona submarino
        matriz[linha][coluna] = '2';
        matriz[linha-1][coluna] = '2';
        matriz[linha-2][coluna] = '2';
        matriz[linha-3][coluna] = '2';
        fprintf(arquivo, "%d %c %d %d %d\n", i, '2', sentido, linha, coluna);
        i++;
      }
    }
    if(sentido == 2){ //OESTE
      //verifica se a posição é INVÁLIDA
      if((matriz[linha][coluna+1]!='*')||(matriz[linha][coluna+2]!='*')||(matriz[linha][coluna+3]!='*')||(coluna>16)){
        continue;
      }
      else{ //posiciona submarino
        matriz[linha][coluna] = '2';
        matriz[linha][coluna+1] = '2';
        matriz[linha][coluna+2] = '2';
        matriz[linha][coluna+3] = '2';
        fprintf(arquivo, "%d %c %d %d %d\n", i, '2', sentido, linha, coluna);
        i++;
      }
    }
    if(sentido == 3){ //LESTE
      //verifica se a posição é INVÁLIDA
      if((matriz[linha][coluna-1]!='*')||(matriz[linha][coluna-2]!='*')||(matriz[linha][coluna-3]!='*')||(coluna<3)){
        continue;
      }
      else{ //posiciona submarino
        matriz[linha][coluna] = '2';
        matriz[linha][coluna-1] = '2';
        matriz[linha][coluna-2] = '2';
        matriz[linha][coluna-3] = '2';
        fprintf(arquivo, "%d %c %d %d %d\n", i, '2', sentido, linha, coluna);
        i++;
      }
    }
  }

  //aviao
  i=0;
  while(i < 5){
    do{
      sentido = rand_sentido();
      linha = rand_xy();
      coluna = rand_xy();
    }while(matriz[linha][coluna]!='*');

    if(sentido == 0){  //NORTE
      //verifica se a posição é INVÁLIDA
      if((matriz[linha][coluna-1]!='*')||(matriz[linha][coluna+1]!='*')||(matriz[linha+1][coluna]!='*')||(coluna==19)||(linha==19)||(coluna==0)){
            continue;
      }
      else{  //posiciona avião
        fprintf(arquivo, "%d %c %d %d %d\n", i, '1', sentido, linha, coluna);
        matriz[linha][coluna] = '1';
        matriz[linha+1][coluna] = '1';
        matriz[linha][coluna-1] = '1';
        matriz[linha][coluna+1] = '1';
        i++;
      }
    }
    if(sentido == 1){  //SUL
      //verifica se a posição é INVÁLIDA
      if((matriz[linha][coluna-1]!='*')||(matriz[linha][coluna+1]!='*')||(matriz[linha-1][coluna]!= '*')||(coluna==19)||(linha==0)||(coluna==0)){
            continue;
      }
      else{  //posiciona avião
        fprintf(arquivo, "%d %c %d %d %d\n", i, '1', sentido, linha, coluna);
        matriz[linha][coluna] = '1';
        matriz[linha-1][coluna] = '1';
        matriz[linha][coluna-1] = '1';
        matriz[linha][coluna+1] = '1';
        i++;
      }
    }
    if(sentido == 2){ //OESTE
      //verifica se a posição é INVÁLIDA
      if((matriz[linha-1][coluna]!='*')||(matriz[linha+1][coluna]!='*')||(matriz[linha][coluna+1]!='*')||(coluna==19)||(linha==0)||(linha==19)){
            continue;
      }
      else{  //posiciona avião
        fprintf(arquivo, "%d %c %d %d %d\n", i, '1', sentido, linha, coluna);
        matriz[linha][coluna] = '1';
        matriz[linha-1][coluna] = '1';
        matriz[linha+1][coluna] = '1';
        matriz[linha][coluna+1] = '1';
        i++;
      }
    }
    if(sentido == 3){  //LESTE
      //verifica se a posição é INVÁLIDA
      if((matriz[linha][coluna-1]!='*')||(matriz[linha-1][coluna]!='*')||(matriz[linha+1][coluna]!='*')||(coluna==0)||(linha==0)||(linha==19)){
            continue;
      }
      else{  //posiciona avião
        fprintf(arquivo, "%d %c %d %d %d\n", i, '1', sentido, linha, coluna);
        matriz[linha][coluna] = '1';
        matriz[linha-1][coluna] = '1';
        matriz[linha+1][coluna] = '1';
        matriz[linha][coluna-1] = '1';
        i++;
      }
    }
  }

  //boia
  for (i=0; i<10; i++){
    do{
      linha = rand_xy();
      coluna = rand_xy();
    }while( matriz[linha][coluna] != '*' );
    matriz[linha][coluna] = '0';
    fprintf(arquivo, "%d %c %d %d %d\n", i, '0', 4, linha, coluna);
  }
  fclose(arquivo);
}

//usada dentro de barco.c > criaMatrizBarcos();
void leArquivo(FILE *arquivo, Barco ***barcos){
  int id, tipo, orientacao, linha, coluna;

  /*o index é o identificador do barco,
  e o valor partes[identificador] é quantidade de células que o barco ocupa no tabuleiro */
  int partes[6] = {1, 4, 4, 6, 6, 10};

  while(fscanf(arquivo, "%d %d %d %d %d", &id, &tipo, &orientacao, &linha, &coluna) != EOF){
    barcos[tipo][id] = criaBarco(id, tipo, orientacao, linha, coluna, partes[tipo]);
  }

}
