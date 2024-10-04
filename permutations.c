/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Javier Moreno & Guillermo Santaolalla
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>

/***************************************************/
/* Function: random_num Date: 09/20/2024           */
/* Authors: Javier Moreno & Guillermo Santaolalla  */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  if(inf > sup) return ERR;
  return inf + (int)((double)(sup - inf + 1)*rand()/(RAND_MAX+1.0));
}

/***************************************************/
/* Function: generate_perm Date: 09/27/2024        */
/* Authors: Javier Moreno & Guillermo Santaolalla  */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int i, temp, random, *arr;
  
  if(N <= 0) return NULL;
  arr = (int *) malloc(N * sizeof(int));
  if (arr == NULL) return NULL;

  for (i = 1; i <= N; i++) {
    arr[i - 1] = i;
  }

  for (i = 0; i < N; i++) {
    random = random_num(0, N - 1);
    if (random == ERR) {
      free(arr);
      return NULL;
    }
    
    temp = arr[i];
    arr[i] = arr[random];
    arr[random] = temp;    
  }
  return arr;
}

/***************************************************/
/* Function: generate_permutations Date: 09/27/2024*/
/* Authors: Javier Moreno & Guillermo Santaolalla  */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int **matrix = NULL, i;
  
  if(n_perms <=0 || N<= 0) return NULL;
  if(!(matrix = (int**) calloc(n_perms, sizeof(int*)))) return NULL;

  for(i=0; i<n_perms; i++){
    if(!(matrix[i] = generate_perm(N))){
      for(i--; i>=0; i--){
        free(matrix[i]);
      }
    }
  }

  return matrix;
}
