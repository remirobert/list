#include "list.h"
#include <stdio.h>

void display_list(t_list *current_element, void *data) {

  printf("data %s\n", (char *)current_element->data);
}

int main(int argc, char **argv) {

  t_list *list = NULL;

  list_push(&list, &"salut", NULL);
  list_push(&list, &"salut1", NULL);
  list_push(&list, &"salut2", NULL);
  list_push(&list, &"salut3", NULL);

  map_list(list, display_list, NULL);

  return (0);
}
