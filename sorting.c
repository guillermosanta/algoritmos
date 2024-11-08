/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Javier Moreno & Guillermo Santaolalla
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"

/***************************************************/
/* Function: SelectSort    Date:  09/27/2024       */
/* Authors: Javier Moreno & Guillermo Santaolalla  */
/*                                                 */
/* Rutine that sorts an array via BubbleSort       */
/*                                                 */
/* Input:                                          */
/* int* array: lower limit                         */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* Output:                                         */
/* int: number of bos done                         */
/***************************************************/
int BubbleSort(int* array, int ip, int iu) {
  int i, j, temp, ob_counter = 0;

  if (!array || ip > iu) return ERR;
  for (i = iu; i >= ip + 1; i--) {
    for (j = ip; j <= i - 1; j++) {
      ob_counter++;
      if (array[j] > array[j + 1]) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
  return ob_counter;
}

/***************************************************/
/* Function: SelectSort    Date:  09/27/2024       */
/* Authors: Javier Moreno & Guillermo Santaolalla  */
/*                                                 */
/* Rutine that sorts an array via BubbleSort       */
/* with a flag that stops if the array is          */
/* already sorted                                  */
/*                                                 */
/* Input:                                          */
/* int* array: lower limit                         */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* Output:                                         */
/* int: number of bos done                         */
/***************************************************/
int BubbleSortFlag(int* array, int ip, int iu) {
  int i, j, temp, ob_counter = 0, flag = 1;

  if (!array || ip > iu) return ERR;
  for (i = iu; flag == 1 && i >= ip + 1; i--) {
    flag = 0;
    for (j = ip; j <= i - 1; j++) {
      ob_counter++;
      if (array[j] > array[j + 1]) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        flag = 1;
      }
    }
  }
  return ob_counter;
}


int CrearHeap(int* array, int n) {
  int i;
  if (!array || n <= 0) return ERR;

  for (i = (n / 2) - 1; i <= 0; i--) {
    Heapify(array, n, i);
  }
}

int OrdenarHeap(int* array, int n) {
  int i, temp;
  if (!array || n <= 0) return ERR;
  
  for (i = n - 1; i <= 0; i--) {
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;
    Heapify(array, i, 0);
  }
}

int max (int *array, int n, int first, int second, int third) {
  if (!array || n <= 0 || n <= first || n <= second || n <= third) return ERR;
  
  return array[first] > array[second] ? (array[first] > array[third] ? first : third) : (array[second] > array[third] ? second : third);
} 

int Heapify(int* array, int n, int i) {
  int ind, temp;
  if (!array || n <= 0 || i < 0 || i >= n) return ERR;

  while (2 * i + 2 <= n) {
    ind = max(array, n, i, i * 2 + 1, i * 2 + 2);
    if (ind == ERR) return ERR;

    if (ind != i) {
      temp = array[i];
      array[i] = array[ind];
      array[ind] = temp;

      i = ind;
    } else return OK;
  }
}


int heapsort(int* array, int ip, int iu) {
  if (!array || ip > iu) return ERR;
  CrearHeap(array, iu - ip + 1);
  OrdenarHeap(array, iu - ip + 1);
  return OK;
}
