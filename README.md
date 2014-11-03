<h1 align="center">List</h1>

This document is written for C programmers. Since you’re reading this, chances are that you know a list is used for store items in a mutable way. This software provides complete list system.

This is just a single header file: list.h. All you need to do is copy the header file into your project, and:
```C
#include "list.h"
```
Since list is a header file only, you don't need to link any code. It's very portable, easy to use, and very fast integration.

<h4 align="center">Features</h4>
```C
LIST_PUSH(list, data_element, function)
MAP_LIST(list, map_fct, arg)
MAP_LIST_WITH_BREAK(list, map_fct, arg)
MAP_LIST_WITH_MATCH(list, map_fct, match_fct, arg)
DELETE_ALL_LIST(list)
LIST_POP(list)
LIST_REMOVE_WITH_DATA(head_list, node, match_fct)
```

<h4 align="center">Overview</h4>

Each item has a free function for free the data only.
```C
typedef struct s_list t_list;

typedef struct          s_list
{
  void                  *data;
  free_function         free;
  struct s_list         *next;
}                       t_list;
```
For more informations, check out test.c.

Some good features are comming, keep an eye on it.
