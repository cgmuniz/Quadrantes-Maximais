#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 256 /* tamanho máximo de um nome de arquivo*/

void maximais(int matrizN, int alt[matrizN][matrizN], int **vazioCP, int expo,
              int expoIni, int numMaximais[2][expoIni + 1], int pos1, int pos2,
              int reg) {

  int aux = matrizN / 2;

  int posSupesq1;
  int posSupesq2;
  int posSupdir1;
  int posSupdir2;
  int posInfesq1;
  int posInfesq2;
  int posInfdir1;
  int posInfdir2;

  if (reg == 1) {
    posSupesq1 = pos1 - aux;
    posSupesq2 = pos2 - aux;
    posSupdir1 = pos1 - aux;
    posSupdir2 = pos2 - aux + 1;
    posInfesq1 = pos1 - aux + 1;
    posInfesq2 = pos2 - aux;
    posInfdir1 = pos1 - aux + 1;
    posInfdir2 = pos2 - aux + 1;
  } else if (reg == 2) {
    posSupesq1 = pos1 - aux;
    posSupesq2 = pos2 + aux - 1;
    posSupdir1 = pos1 - aux;
    posSupdir2 = pos2 + aux;
    posInfesq1 = pos1 - aux + 1;
    posInfesq2 = pos2 + aux - 1;
    posInfdir1 = pos1 - aux + 1;
    posInfdir2 = pos2 + aux;
  } else if (reg == 3) {
    posSupesq1 = pos1 + aux - 1;
    posSupesq2 = pos2 - aux;
    posSupdir1 = pos1 + aux - 1;
    posSupdir2 = pos2 - aux + 1;
    posInfesq1 = pos1 + aux;
    posInfesq2 = pos2 - aux;
    posInfdir1 = pos1 + aux;
    posInfdir2 = pos2 - aux + 1;
  } else if (reg == 4) {
    posSupesq1 = pos1 + aux - 1;
    posSupesq2 = pos2 + aux - 1;
    posSupdir1 = pos1 + aux - 1;
    posSupdir2 = pos2 + aux;
    posInfesq1 = pos1 + aux;
    posInfesq2 = pos2 + aux - 1;
    posInfdir1 = pos1 + aux;
    posInfdir2 = pos2 + aux;
  }

  if (matrizN == 1) {
    numMaximais[alt[0][0]][0] += 1;
  }

  if (matrizN > 2) {
    int matriz1[aux][aux];
    int matriz2[aux][aux];
    int matriz3[aux][aux];
    int matriz4[aux][aux];

    for (int i = 0; i < aux; i++) {
      for (int j = 0; j < aux; j++) {
        matriz1[i][j] = alt[i][j];
      }
    }

    for (int i = 0; i < aux; i++) {
      for (int j = 0; j < aux; j++) {
        matriz1[i][j] = alt[i][j];
        matriz2[i][j] = alt[i][j + aux];
        matriz3[i][j] = alt[i + aux][j];
        matriz4[i][j] = alt[i + aux][j + aux];
      }
    }

    maximais(aux, matriz1, vazioCP, expo - 1, expoIni, numMaximais, posSupesq1,
             posSupesq2, 1);
    maximais(aux, matriz2, vazioCP, expo - 1, expoIni, numMaximais, posSupdir1,
             posSupdir2, 2);
    maximais(aux, matriz3, vazioCP, expo - 1, expoIni, numMaximais, posInfesq1,
             posInfesq2, 3);
    maximais(aux, matriz4, vazioCP, expo - 1, expoIni, numMaximais, posInfdir1,
             posInfdir2, 4);
  }

  if (expo == 1) {
    int diff = 0;

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        if (alt[i][j] !=
            alt[0][0]) { // Compara com o valor do canto superior esquerdo
          diff = 1;
          break;
        }
      }
    }

    if (diff == 1) {
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          numMaximais[alt[i][j]][expo - 1] += 1;
        }
      }
      vazioCP[pos1][pos2] = 1;
    } else {
      if (expo == expoIni) {
        numMaximais[alt[0][0]][expo] += 1;
      }
      vazioCP[pos1][pos2] = 0;
    }
  }

  else {
    int supesq = vazioCP[posSupesq1][posSupesq2];
    int supdir = vazioCP[posSupdir1][posSupdir2];
    int infesq = vazioCP[posInfesq1][posInfesq2];
    int infdir = vazioCP[posInfdir1][posInfdir2];

    if (supesq == 0 && supdir == 0 && infesq == 0 && infdir == 0) {
      int diff = 0;

      for (int i = aux - 1; i <= aux; i++) {
        for (int j = aux - 1; j <= aux; j++) {
          if (alt[i][j] != alt[aux - 1][aux - 1]) { // Compara com o valor do
                                                    // canto superior esquerdo
            diff = 1;
            break;
          }
        }
      }

      if (diff == 1) {
        for (int i = aux - 1; i <= aux; i++) {
          for (int j = aux - 1; j <= aux; j++) {
            numMaximais[alt[i][j]][expo - 1] += 1;
          }
        }

        vazioCP[pos1][pos2] = 1;
      } else {
        vazioCP[pos1][pos2] = 0;

        if (expo == expoIni) {
          numMaximais[alt[0][0]][expo] += 1;
        }
      }

    } else {
      vazioCP[pos1][pos2] = 1;

      if (supesq == 0) {
        numMaximais[alt[0][0]][expo - 1] += 1;
      }

      if (supdir == 0) {
        numMaximais[alt[0][0 + aux]][expo - 1] += 1;
      }

      if (infesq == 0) {
        numMaximais[alt[0 + aux][0]][expo - 1] += 1;
      }

      if (infdir == 0) {
        numMaximais[alt[0 + aux][0 + aux]][expo - 1] += 1;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  /* argc é o número de argumentos (na verdade palavras) passados na linha de
   * comando na chamada do programa */
  /* incluindo a chamada do programa */
  if (argc != 3) {
    printf(
        "Este programa exige dois argumentos:  (1) um inteiro N (potência de 2 "
        "e no máximo 1024, a dimensão da matriz que representa a imagem); (2) "
        "o nome do arquivo de entrada (no formato .txt)\n"); /* COMPLETAR */
    exit(1);
  }

  // printf("%s ", argv[0]);
  // printf("%s ", argv[1]);
  // printf("%s\n", argv[2]);

  /* argv[0] tem a chamada do programa */
  /* argv[i] tem os argumentos passados (para i > 0) armazenados na forma de
   * string */
  /* se precisar convertê-los para outro tipo de dado, por ex int, precisa fazer
   * a conversão para esse tipo de dado */
  /* ex: usando a função atoi - note para isso vai precisar de outros include's
   * ... */
  /* COMPLETAR */

  int matrizN = atoi(argv[1]);

  /* se o segundo argumento  for o nome de um arquivo, e você precisa abri-lo:
   */
  char filename[MAX_FILENAME] = "";
  strcpy(filename, argv[2]); /* copia conteúdo de argv[2] para filename */
  FILE *fp = fopen(filename, "r"); /* abre arquivo em modo somente leitura */
  if (fp == NULL) {
    fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filename);
    return -1;
  }
  /* lendo algo do arquivo, por ex um inteiro, seguido de um char */
  // int inteiroLido[matrizN];
  // for (int i = 0; i < matrizN; i++) {
  //   fscanf(fp, "%d", &inteiroLido[i]);
  // }

  // /* conferindo se li certo */
  // for (int i = 0; i < matrizN; i++) {
  //   printf("%d\n", inteiroLido[i]);
  // }

  int expo = 0;
  int aux = matrizN;

  while (aux != 1) {
    aux = aux / 2;
    expo++;
  }

  char num[matrizN][matrizN + 1];
  int pbInt[matrizN][matrizN];

  int **vazioCP = (int **)malloc(matrizN * sizeof(int *));
  for (int i = 0; i < matrizN; i++) {
    vazioCP[i] = (int *)malloc(matrizN * sizeof(int));
  }

  int numMaximais[2][expo + 1];

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < expo + 1; j++) {
      numMaximais[i][j] = 0;
    }
  }

  for (int i = 0; i < matrizN; i++) {
    for (int j = 0; j < matrizN; j++) {
      fscanf(fp, "%1d", &pbInt[i][j]);
    }
  }

  // for (int i = 0; i < matrizN; i++) {
  //   for (int j = 0; j < matrizN; j++) {
  //     printf("int[%d][%d]=%d;\n", i, j, pbInt[i][j]);
  //   }
  // }

  maximais(matrizN, pbInt, vazioCP, expo, expo, numMaximais, matrizN - 1,
           matrizN - 1, 1);

  int pot = matrizN;

  FILE *file;
  file = fopen("saida.txt", "w");

  for (int j = expo; j >= 0; j--) {
    fprintf(file, "%dx%d %d %d", pot, pot, numMaximais[1][j],
            numMaximais[0][j]);
    if (pot != 1) {
      fprintf(file, "\n");
    }
    pot /= 2;
  }

  /* se você for ler char's, para o compilador um char pode ser espaço em
   * branco, newline, etc */
  // char char1, char2, char3;
  // fscanf(fp, "%c", &char1);
  // fscanf(fp, "%c", &char2);
  // fscanf(fp, "%c", &char3);
  // /* conferindo se li certo */
  // printf("char1=%c; char2=%c; char3=%c;\n", char1, char2, char3);
  /* também dá para ler char's usando getchar() - pesquisem!!! */

  /* dá para ler outros tipos de dados também: floats, bools, etc */
}
