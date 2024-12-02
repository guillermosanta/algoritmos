/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <math.h>
#include <stdlib.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be
 *				 allocated externally to the function.
 */

/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max) {
  int i;

  for (i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max) {
  int i;

  for (i = 0; i < n_keys; i++) {
    keys[i] = .5 + max / (1 + max * ((double)rand() / (RAND_MAX)));
  }

  return;
}

PDICT init_dictionary(int size, char order) {
  PDICT dict;

  if (!size || !order) return NULL;
  if (!(dict = (PDICT)calloc(1, sizeof(DICT)))) return NULL;

  dict->size = size;
  if (!(dict->table = (int *)calloc(size, sizeof(int)))) return NULL;
  dict->order = order;
  dict->n_data = 0;

  return dict;
}

void free_dictionary(PDICT pdict) {
  if (!pdict) return;

  pdict->size = 0;
  pdict->n_data = 0;
  free(pdict->table);

  free(pdict);
}

int insert_dictionary(PDICT pdict, int key) {
  int j = 0;

  if (!pdict || !key) return ERR;
  /*We check if the table is full*/
  if (pdict->n_data == pdict->size) {
    printf("Table is full\n");
    return ERR;
  }

  /*Insertion at the end*/
  pdict->table[pdict->n_data] = key;
  pdict->n_data++;

  if (pdict->order == 0) { /*IF NOT SORTED*/
    return OK;
  }
  /*IF SORTED*/
  j = pdict->n_data - 1;
  while (j >= pdict->table[0] && pdict->table[j] > key);
  pdict->table[j + 1] = pdict->table[j];
  j--;
  pdict->table[j + 1] = key;

  return OK;
}

int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys) { /* your code */ }

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method) { /* your code */ }

/* Search functions of the Dictionary ADT */
int bin_search(int *table, int F, int L, int key, int *ppos) { /* your code */ }

int lin_search(int *table, int F, int L, int key, int *ppos) { /* your code */ }

int lin_auto_search(int *table, int F, int L, int key, int *ppos) { /* your code */ }
