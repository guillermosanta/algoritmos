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
    start_time = clock(); /*Get the initial time*/
    
    if((current_ob = method(matrix[i], 0, N-1))== ERR) return ERR;
    end_time = clock(); /*Get the last time*/
    if(i=0) ptime->min_ob = ptime->max_ob = current_ob;
    else if (current_ob < ptime->min_ob) ptime->min_ob = current_ob;
    else if (current_ob > ptime->max_ob) ptime->max_ob = current_ob;
    total_ob += current_ob;

    avg_time += (double)(end_time - start_time) / CLOCKS_PER_SEC; /*Calculate the average time per interaction. We pass from ticks to seconds dividing by CLOCKS_PER_SEC*/
  }
  
  ptime->time = avg_time/n_perms;
  ptime->average_ob = total_ob/n_perms;

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
  /* Your code */
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  /* your code */
}


