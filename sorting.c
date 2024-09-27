/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"

/***************************************************/
/* Function: SelectSort    Date:  27/09/2024       */
/*                                                 */
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

int BubbleSortFlag(int* array, int ip, int iu)
{
  return ERR;
}



