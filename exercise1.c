/**************************************************/
/* Program: exercise1     Date:  20-09-24         */
/* Authors: Javier Moreno & Guillermo Santaolalla */
/*                                                */
/* Program that generates two random nunmbers     */
/* between two given numbers                      */
/*                                                */
/* Input: Command Line                            */
/* -limInf: lower limit                           */
/* -limSup: upper limit                           */
/* -numN: ammount of numbers                      */
/* Output: 0: OK, -1: ERR                          */
/**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "permutations.h"

int main(int argc, char **argv) {
  int i, temp_num;
  unsigned int inf, sup, num, j;
  int *num_frecuency;
  FILE *f;
  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Input parameter error:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -limInf : Lower limit.\n");
    fprintf(stderr, " -limSup : Upper limit.\n");
    fprintf(stderr, " -numN : ammout of mumbers to generate.\n");
    exit(-1);
  }
  printf("Practice no 1, Section 1\n");
  printf("Done by: Javier Moreno y Guillermo Santaolalla\n");
  printf("Grupo: SI\n");

  /* check command line */
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-limInf") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-limSup") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong Parameter %s \n", argv[i]);
    }
  }

  if (inf < 0 || sup < 0 || inf > sup || num <= 0) {
    fprintf(stderr, "Parameters outside valid range\n");
    exit(-1);
  }

  /* allocate memory for the array that stores the frecuency of each number */
  num_frecuency = calloc((sup - inf + 1), sizeof(int));
  if (num_frecuency == NULL) {
    fprintf(stderr, "Error allocating memory for the frecuency array");
    exit(-1);
  }

  /* store data */
  for (j = 0; j < num; j++) {
    temp_num = random_num(inf, sup);
    if (temp_num == ERR) {
      free(num_frecuency);
      exit(-1);
    }

    num_frecuency[temp_num - inf]++;
  }

  f = fopen("results.txt", "w");
  if (f == NULL) {
    fprintf(stderr, "Error opening file to write");
    exit(-1);
  }

  for (i = 0; i < sup - inf + 1; i++) {
    fprintf(f, "%d %d\n", inf + i, num_frecuency[i]);
  }

  fclose(f);
  free(num_frecuency);
  return 0;
}
