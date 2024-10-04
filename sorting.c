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
int BubbleSort(int* array, int ip, int iu)
{
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
int BubbleSortFlag(int* array, int ip, int iu)
{
  int i, j, temp, ob_counter = 0, flag = 1;

  if (!array || ip > iu) return ERR;
  for (i = iu; flag==1 && i >= ip + 1; i--) {
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



