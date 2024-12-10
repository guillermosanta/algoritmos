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
#include <stdio.h>
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

  if (size < 0) return NULL;
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
  int j = 0, obs = 0;

  if (!pdict || !key) return ERR;
  /*We check if the table is full*/
  if (pdict->n_data == pdict->size) {
    printf("Table is full\n");
    return obs;
  }

  /*Insertion at the end*/
  obs++; /*No lo tengo claro*/
  pdict->table[pdict->n_data] = key;
  pdict->n_data++;

  if (pdict->order == NOT_SORTED) return obs;

  /*if sorted */
  j = pdict->n_data - 2;
  while (j >= 0 && pdict->table[j] > key) {
    obs++;
    pdict->table[j + 1] = pdict->table[j];
    j--;
  }
  obs++; /*Ultima comprobacion fallida, tampoco lo tengo claro*/
  pdict->table[j + 1] = key;

  return obs;
}

int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys) {
  int i, ret, obs = 0;
  if (!pdict || !keys || n_keys < 0) return ERR;

  for (i = 0; i < n_keys; i++) {
    obs++;
    ret = insert_dictionary(pdict, keys[i]);
    if (ret == 0) return obs;
    obs += ret;
  }

  return obs;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method) {
  if (!pdict || !ppos || !method) return ERR;

  /* Return ERR if method fails else OK */
  return method(pdict->table, 0, pdict->size - 1, key, ppos);
}

int print_dictionary(PDICT pdict) {
  int i = 0, obs = 0;

  if (!pdict) return ERR;

  printf("[");
  for (; i < pdict->size; i++) {
    obs++;
    printf("%d", pdict->table[i]);
    if (i + 1 != pdict->size) printf(", ");
  }
  printf("]\n");
  return obs;
}

/* Search functions of the Dictionary ADT */
int bin_search(int *table, int F, int L, int key, int *ppos) {
  /* TODO: return OBs instead of status */
  int M, obs = 0;

  if (!table || !ppos) return obs;

  /*obs ++; /*No lo tengo claro*/
  if (F < L) {
    *ppos = NOT_FOUND;
    return obs;
  }

  M = floor((L + F) / 2);
  obs++;
  if (table[M] == key) {
    *ppos = M;
    return obs;
  }

  if (table[M] < key) return obs + bin_search(table, F, M - 1, key, ppos);
  return obs + bin_search(table, M + 1, L, key, ppos);
}

int lin_search(int *table, int F, int L, int key, int *ppos) {
  int i, obs = 0;

  if (!table || !ppos || F > L) return ERR;

  for (i = F; i < L; i++) {
    obs++;
    if (table[i] == key) {
      *ppos = i;
      return obs;
    }
  }
  *ppos = NOT_FOUND;
  return obs;
}

int lin_auto_search(int *table, int F, int L, int key, int *ppos) {
  int i, obs = 0, temp;

  if (!table || !ppos || F > L) return ERR;

  for (i = F; i <= L; i++) {
    obs++;
    if (table[i] == key) {
      *ppos = i;
      /*Autoorganización: intercambio si no está en la primera posición*/
      if (i > F) {
        temp = table[i];
        table[i] = table[i - 1];
        table[i - 1] = temp;
      }
      return obs;
    }
  }

  *ppos = NOT_FOUND;
  return obs;
}
