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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CrearHeap(int* array, int n);
int OrdenarHeap(int* array, int n);
int Heapify(int* array, int n, int i);
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

/***************************************************/
/* Function: max    Date:  10/15/2024              */
/* Authors: Javier Moreno & Guillermo Santaolalla  */
/*                                                 */
/* Given an array and three indeces,               */
/* returns the index with the highest integer      */
/*                                                 */
/* Input:                                          */
/* int* array: array of integers                   */
/* int n: number of elements in array              */
/* int first: first index                          */
/* int second: second index                        */
/* int third: third index                          */
/* Output:                                         */
/* int: The index that points                      */
/* to the greatest integer                         */
/***************************************************/
int max(int* array, int n, int first, int second, int third) {
  if (!array || n <= 0 || n <= first || n <= second || n <= third) return ERR;

  return array[first] > array[second] ? (array[first] > array[third] ? first : third)
                                      : (array[second] > array[third] ? second : third);
}

int HeapSort(int* array, int ip, int iu) {
  int ob_counter = 0, ret;
  if (!array || ip > iu) return ERR;

  ret = CrearHeap(array, iu - ip + 1);
  if (ret == ERR) return ERR;
  ob_counter += ret;

  ret = OrdenarHeap(array, iu - ip + 1);
  if (ret == ERR) return ERR;
  ob_counter += ret;

  return ob_counter;
}

int CrearHeap(int* array, int n) {
  int i, ob_counter = 0, ret;
  if (!array || n <= 0) return ERR;

  for (i = (n / 2) - 1; i >= 0; i--) {
    ret = Heapify(array, n, i);
    if (ret == ERR) return ERR;
    ob_counter += ret;
  }
  return ob_counter;
}

int OrdenarHeap(int* array, int n) {
  int i, temp, ob_counter = 0, ret;

  if (!array || n <= 0) return ERR;

  for (i = n - 1; i > 0; i--) {
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;

    ret = Heapify(array, i, 0);
    if (ret == ERR) return ERR;
    ob_counter += ret;
  }
  return ob_counter;
}

int Heapify(int* array, int n, int i) {
  int ind, temp, ob_counter = 0;
  if (!array || n <= 0 || i < 0 || i >= n) return ERR;

  while (2 * i + 1 < n) {
    if (2 * i + 2 < n) {
      ind = max(array, n, i, 2 * i + 1, 2 * i + 2);
      ob_counter += 2;
    } else {
      ind = array[i] > array[2 * i + 1] ? i : 2 * i + 1;
      ob_counter++;
    }

    if (ind == ERR) return ERR;

    if (ind != i) {
      temp = array[i];
      array[i] = array[ind];
      array[ind] = temp;

      i = ind;
    } else
      return ob_counter;
  }
  return ob_counter;
}

int merge(int* array, int ip, int iu, int imedio) {
  int *aux, i, j, k, counter = 0;

  if (!array || ip > iu || ip > imedio || imedio > iu) return ERR;

  if ((aux = (int*)calloc((iu - ip + 1), sizeof(int))) == NULL) return ERR;

  for (i = ip, j = imedio + 1, k = 0; i <= imedio && j <= iu; k++, counter++) {
    if (array[i] < array[j]) {
      aux[k] = array[i];
      i++;
    } else {
      aux[k] = array[j];
      j++;
    }
  }

  if (i > imedio) {
    for (; j <= iu; j++, k++) {
      aux[k] = array[j];
    }
  } else if (j > iu) {
    for (; i <= imedio; i++, k++) {
      aux[k] = array[i];
    }
  }

  memcpy(array + ip, aux, (iu - ip + 1) * sizeof(int));

  free(aux);
  return counter;
}

/***************************************************/
/* Function: MergeSort    Date:  11/09/2024        */
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
int MergeSort(int* array, int ip, int iu) {
  int mid, n1 = 0, n2 = 0, n3 = 0;

  if (!array || ip > iu) return ERR;

  if (ip == iu) return 0;

  mid = (ip + iu) / 2;
  if ((n1 = MergeSort(array, ip, mid)) == ERR) return ERR;
  if ((n2 = MergeSort(array, mid + 1, iu)) == ERR) return ERR;
  if ((n3 = merge(array, ip, iu, mid)) == ERR) return ERR;
  return n1 + n2 + n3;
}
