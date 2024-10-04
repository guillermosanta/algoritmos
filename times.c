/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "permutations.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort method, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  int **matrix = NULL, i, current_ob = 0;
  double total_ob = 0.0, avg_time = 0.0;
  clock_t start_time, end_time;

  if(!method || n_perms <= 0 || N <= 0 || !ptime) return ERR;

  ptime->n_elems = n_perms;
  ptime->N = N;

  if(!(matrix = generate_permutations(n_perms, N))) return ERR;
  for(i=0; i<n_perms; i++){
    if((start_time = clock()) == ERR) return ERR; 
    if((current_ob = method(matrix[i], 0, N-1))== ERR) return ERR;
    if((end_time = clock()) == ERR) return ERR;

    if (i==0) ptime->min_ob = ptime->max_ob = current_ob;
    else if (current_ob < ptime->min_ob) ptime->min_ob = current_ob;
    else if (current_ob > ptime->max_ob) ptime->max_ob = current_ob;
    
    total_ob += current_ob;
    avg_time += (double)(end_time - start_time) / CLOCKS_PER_SEC; /*Calculate the average time per interaction. We pass from ticks to seconds dividing by CLOCKS_PER_SEC*/
  }
  
  ptime->time = avg_time/n_perms;
  ptime->average_ob = total_ob/n_perms;

  for(i=0; i<n_perms; i++){
    free(matrix[i]);
  }
  free(matrix);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  PTIME_AA ptime;
  int i;
  
  /* We check that the increment is greater than or equal to 0 to avoid infinite loops */
  if (!method || !file || num_min > num_max || incr <= 0 || n_perms <= 0) return ERR;

  ptime = (PTIME_AA) malloc(ceil((num_max - num_min + 1) / incr) * sizeof(TIME_AA));
  if (!ptime) {printf("A");return ERR;}
  

  for (i = num_min; i <= num_max; i+=incr) {
    if (average_sorting_time(method, n_perms, i, ptime + i) == ERR) {
      free(ptime);
      return ERR;
    }
  }

  if (save_time_table(file, ptime, ceil((num_max - num_min + 1) / incr)) == ERR) {
    free(ptime);
    return ERR;
  }
  
  free(ptime);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{    

    FILE *f;
    int i = 0;

    f = fopen(file, "w");
    if (!f) return ERR;

    for (i = 0; i < n_times; i++) {
      fprintf(f, "%d  %lf %lf %d  %d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime->min_ob);
    }

    fclose(f);
    return OK;
}


