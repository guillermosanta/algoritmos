/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Javier Moreno & Guillermo Santaolalla
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "permutations.h"
#include "search.h"

int cceil(double x) {
  int integer_part = (int)x;
  if (x > integer_part) return integer_part + 1;
  return integer_part;
}

/***************************************************/
/* Function: average_search_time Date: 19/11/2024  */
/* Authors: Javier Moreno & Guillermo Santaolalla  */
/*                                                 */
/* Rutine                                          */
/*                                                 */
/*                                                 */
/* Input:                                          */
/* pfunc_search metodo                             */
/* pfunc_key_generator generator                   */
/* int order                                       */
/* int N                                           */
/* int n_times                                     */
/* PTIME_AA ptime                                  */
/* Output:                                         */
/* short: OK or ERR                                */
/***************************************************/
short average_search_time(pfunc_search metodo, pfunc_key_generator generator, int order, int N,
                          int n_times, PTIME_AA ptime) {
  PDICT pdict = NULL;
  int *perm = NULL;
  int *keys = NULL;
  int i, j, ppos, obs, total_obs = 0;
  int min_ob = __INT_MAX__, max_ob = 0;
  clock_t start, end;

  if (!metodo || !generator || N <= 0 || n_times <= 0 || !ptime) {
    printf("Error with params\n");
    return ERR;
  }

  /*7*/
  ptime->N = N;
  ptime->n_elems = N * n_times;

  /*1*/
  pdict = init_dictionary(N, order);
  if (!pdict) {
    printf("Error initializing dictionary of size %d\n", N);
    return ERR;
  };

  /*2*/
  perm = generate_perm(N);
  if (!perm) {
    printf("Error generating perm of size %d\n", N);
    free_dictionary(pdict);
    return ERR;
  }

  /*3*/
  if (massive_insertion_dictionary(pdict, perm, N) == ERR) {
    printf("Error inserting keys into dict of size %d\n", N);
    free(perm);
    free_dictionary(pdict);
    return ERR;
  }

  /*4*/
  keys = (int *)calloc(N * n_times, sizeof(int));
  if (!keys) {
    printf("Error allocating memory for keys\n");
    free(perm);
    free_dictionary(pdict);
    return ERR;
  }

  /*5*/
  generator(keys, N * n_times, N); /*== ERR) {
    free(perm);
    free(keys);
    free_dictionary(pdict);
    return ERR;
  }*/

  /*6*/
  if ((start = clock()) == ERR) {
    printf("Error starting clock\n");
    free(perm);
    free(keys);
    free_dictionary(pdict);
    return ERR;
  }

  for (i = 0; i < n_times; i++) {
    for (j = 0; j < N; j++) {
      obs = metodo(pdict->table, 0, pdict->n_data - 1, keys[i * N + j], &ppos);
      if (obs == ERR) {
        printf("Error counting OBs from method\n");
        free(perm);
        free(keys);
        free_dictionary(pdict);
        return ERR;
      }
      if (ppos == NOT_FOUND) {
        printf("Key not found in dict!\n");
        free(perm);
        free(keys);
        free_dictionary(pdict);
        return ERR;
      }
      total_obs += obs;
      if (obs < min_ob) min_ob = obs;
      if (obs > max_ob) max_ob = obs;
    }
  }
  if ((end = clock()) == ERR) {
    printf("Error stopping clock\n");
    free(perm);
    free(keys);
    free_dictionary(pdict);
    return ERR;
  }

  /*7*/
  ptime->time = ((double)(end - start)) / CLOCKS_PER_SEC;
  ptime->average_ob = (double)total_obs / (N * n_times);
  ptime->min_ob = min_ob;
  ptime->max_ob = max_ob;

  /*8*/
  free(perm);
  free(keys);
  free_dictionary(pdict);

  return OK;
}

short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order,
                            char *file, int num_min, int num_max, int incr, int n_times) {
  PTIME_AA ptime;
  short ret;
  int i;

  if (!method || !generator || (order != SORTED && order != NOT_SORTED) || !file ||
      num_min > num_max || incr <= 0 || n_times <= 0)
    return ERR;

  ptime = (PTIME_AA)malloc((int)cceil((num_max - num_min + 1) / (double)incr) * sizeof(TIME_AA));
  if (!ptime) {
    printf("Error allocating memory\n");
    return ERR;
  }

  for (i = num_min; i <= num_max; i += incr) {
    ret = average_search_time(method, generator, order, i, n_times, ptime + (i - num_min) / incr);
    if (ret == ERR) {
      printf("Error in average_search_time for i = %d\n", i);
      free(ptime);
      return ERR;
    }
  }

  ret = save_time_table(file, ptime, (int)cceil((num_max - num_min + 1) / (double)incr));
  if (ret == ERR) {
    free(ptime);
    return ERR;
  }

  free(ptime);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date: 10/04/2024      */
/* Authors: Javier Moreno & Guillermo Santaolalla  */
/*                                                 */
/* Rutine                                          */
/*                                                 */
/*                                                 */
/* Input:                                          */
/* char* file:                                     */
/* PTIME_AA ptime: pointer to time structure where */
/* data is stored                                  */
/* int n_times:                                    */
/* Output:                                         */
/* short: OK or ERR                                */
/***************************************************/
short save_time_table(char *file, PTIME_AA ptime, int n_times) {
  FILE *f;
  int i = 0;

  f = fopen(file, "w");
  if (!f) return ERR;

  for (i = 0; i < n_times; i++) {
    fprintf(f, "%d  %f %f %d  %d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob,
            ptime[i].max_ob, ptime[i].min_ob);
  }

  fclose(f);
  return OK;
}