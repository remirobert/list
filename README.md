<h1 align="center">List</h1>


<h2 align="center">Push list</h2>

```C
struct point {
  int x;
  int y;
};

void free_point(void *point) {
  free(point);
}

void add_point_to_list(t_list **list, int x, int y) {
  struct point *new_point = malloc(sizeof(struct point));

  if (new_point) {
    new_point->x = x;
    new_point->y = y;
    list_push(list, (void *)new_point, free_point);
  }
}

int main(int argc, char **argv) {

  t_list *list = NULL;

  add_point_to_list(&list, 2, 3);
  add_point_to_list(&list, 3, 4);

  return (0);
}
```

<h2 align="center">Map list</h2>

```C
void display_list(t_list *current_element, void *data) {

  printf("current point x :%d y : %d\n", ((struct point *)current_element->data)->x,
	 ((struct point *)current_element->data)->y);
}

void increment_position(t_list *current_element, void *data) {
  ((struct point *)current_element->data)->x += *((int *)data);
  ((struct point *)current_element->data)->y += *((int *)data);
}

/...

int main(int argc, char **argv) {

  t_list *list = NULL;

  //...
  
  int increment_value = 3;
  map_list(list, increment_position, &increment_value);
  map_list(list, display_list, NULL);

  return (0);
}
```

<h2 align="center">Remove list</h2>

```C
int check_position_point(void *current_point, void *point) {
  if (((struct point *)current_point)->x == ((struct point *)point)->x &&
      ((struct point *)current_point)->y == ((struct point *)point)->y) {
    return (0);
  }
  return (1);
}

int main(int argc, char **argv) {

  t_list *list = NULL;

  /...

  struct point check_point;
  check_point.x = 6;
  check_point.y = 7;
  list_remove_with_data(&list, &check_point, check_position_point);

  /...
  
  return (0);
}
```
