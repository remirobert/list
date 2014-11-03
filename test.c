#include "list.h"

struct position {
  int x;
};

void  free_data(LIST *list, void *data) {
  printf("ok\n");
  printf("current number : %d\n", ((struct position *)list->data)->x);
}

int main() {

  struct  position ok;
  ok.x = 4;

 struct  position ok2;
  ok2.x = 904;

  LIST *list = NULL;
  int a = 43;

  LIST_PUSH(&list, (void *)&ok, NULL);
  LIST_PUSH(&list, (void *)&ok2, NULL);

  MAP_LIST(list, free_data, NULL);
  DELETE_ALL_LIST(list);

  printf("ok delete");
  do {
  } while (0);

  return (0);
}
