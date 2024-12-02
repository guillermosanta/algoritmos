#include "search.h"

int main() {
  PDICT dict = init_dictionary(5, SORTED);
  insert_dictionary(dict, 3);
  insert_dictionary(dict, 5);
  insert_dictionary(dict, 2);
  insert_dictionary(dict, 1);
  insert_dictionary(dict, 4);
  print_dictionary(dict);
  return OK;
}