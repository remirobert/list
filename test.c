#include "list/list.h"

struct point {
  int x;
  int y;
};

void display_list(LIST *current_element, void *data) {

  printf("current point x :%d y : %d\n", ((struct point *)current_element->data)->x,
	 ((struct point *)current_element->data)->y);
}

void increment_position(LIST *current_element, void *data) {
  ((struct point *)current_element->data)->x += *((int *)data);
  ((struct point *)current_element->data)->y += *((int *)data);
}

void free_point(void *point) {
  free(point);
}

void add_point_to_list(LIST **list, int x, int y) {
  struct point *new_point = malloc(sizeof(struct point));

  if (new_point) {
    new_point->x = x;
    new_point->y = y;
    LIST_PUSH(list, (void *)new_point, free_point);
  }
}

int check_position_point(void *current_point, void *point) {
  if (((struct point *)current_point)->x == ((struct point *)point)->x &&
      ((struct point *)current_point)->y == ((struct point *)point)->y) {
    return (0);
  }
  return (-1);
}

int main(int argc, char **argv) {

  LIST *list = NULL;

  add_point_to_list(&list, 2, 3);
  add_point_to_list(&list, 3, 4);

  int increment_value = 3;
  MAP_LIST(list, increment_position, &increment_value);
  MAP_LIST(list, display_list, NULL);

  struct point check_point;
  check_point.x = 6;
  check_point.y = 7;
  LIST_REMOVE_WITH_DATA(&list, &check_point, check_position_point);

  MAP_LIST(list, display_list, NULL);
  DELETE_ALL_LIST(list);

  return (0);
}
