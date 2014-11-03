#ifndef LIST2_H
# define LIST2_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list LIST;

typedef void (*free_function)(void *);
typedef int (*match_function)(void *, void *);
typedef void (*map_function)(LIST *, void *);
typedef int (*map_function_ret)(LIST *, void *);

# define FREE_DATA_ELEM(current_elem)					\
  do {									\
    if ((LIST *)current_elem != NULL &&					\
	((LIST *)current_elem)->free != NULL)				\
      current_elem->free(current_elem->data);				\
  } while(0)								\

# define FIRST_ELEM_REMOVE_LIST(head_list, node)			\
  do {									\
    LIST		*tmp_elem;					\
    tmp_elem = *((LIST **)head_list);					\
    if ((LIST *)(*head_list)->next == NULL)				\
      {									\
	FREE_DATA_ELEM((LIST *)*head_list);				\
	(LIST *)*head_list = NULL;					\
      }									\
    else if ((void *)((LIST *)(*head_list))->data == (void *)node)	\
      {									\
	FREE_DATA_ELEM((LIST *)*head_list);				\
	(LIST *)*head_list = ((LIST *)(*head_list))->next;		\
      }									\
    free(tmp_elem);							\
  } while(0)								\

# define LIST_REMOVE_WITH_DATA(head_list, node, match_fct)		\
  do {									\
    LIST		*current_elem;					\
    LIST		*tmp_elem;					\
    if (head_list == NULL || *head_list == NULL)			\
      break ;								\
    current_elem = *head_list;						\
    if (match_fct((*head_list)->data, (void *)node) == 0)		\
      {									\
        FIRST_ELEM_REMOVE_LIST(head_list, (void *)node);		\
	break ;								\
      }									\
    while (current_elem->next != NULL)					\
      {									\
	if (match_fct(current_elem->next->data, (void *)node) == 0)	\
	  {								\
	    tmp_elem = current_elem->next;				\
	    FREE_DATA_ELEM((LIST *)current_elem->next);			\
	    current_elem->next = current_elem->next->next;		\
	    free(tmp_elem);						\
	    break ;							\
	  }								\
	current_elem = current_elem->next;				\
      }									\
  } while(0)								\

# define LIST_POP(list)							\
  do {									\
    void			*ptmp;					\
    if (list == NULL || *list == NULL) break;				\
    if ((*list)->next == NULL)						\
      {									\
	if ((*list)->free != NULL)					\
	  (*list)->free((*list)->data);					\
	free(*list);							\
	*list = NULL;							\
	break ;								\
      }									\
    if ((*list)->free != NULL)						\
      (*list)->free((*list)->data);					\
    ptmp = *list;							\
    *list = (*list)->next;						\
    free(ptmp);								\
  } while(0)								\

# define DELETE_ALL_LIST(list)						\
    do {								\
      LIST		*current_elem;					\
      void			*ptmp;					\
      if (list == NULL) break;						\
      current_elem = list;						\
      while (current_elem != NULL)					\
	{								\
	  FREE_DATA_ELEM(current_elem);					\
	  ptmp = current_elem;						\
	  current_elem = current_elem->next;				\
	  free(ptmp);							\
	}								\
      list = NULL;							\
    } while(0)								\

# define LIST_PUSH(list, data_element, function)			\
    do {								\
      LIST		*current_elem;					\
      LIST		*new_elem;					\
      if ((void *)data_element == NULL) break;				\
      if (*list == NULL)						\
	{								\
	  if ((*list = malloc(sizeof(LIST))) == NULL)			\
	    break ;							\
	  (*list)->data = (void *)data_element;				\
	  (*list)->free = (free_function)function;			\
	  (*list)->next = NULL;						\
	  break ;							\
	}								\
      if ((new_elem = malloc(sizeof(LIST))) == NULL)			\
	break ;								\
      new_elem->data = (void *)data_element;				\
      new_elem->free = (free_function)function;				\
      new_elem->next = NULL;						\
      current_elem = *list;						\
      while (current_elem->next != NULL)				\
	current_elem = current_elem->next;				\
      current_elem->next = new_elem;					\
    } while(0)								\

# define MAP_LIST(list, map_fct, arg)					\
    do {								\
	LIST		*current_elem;					\
	if (list == NULL || map_fct == NULL) break;			\
	current_elem = list;						\
	while (current_elem != NULL)					\
	  {								\
	    map_fct(current_elem, arg);					\
	    current_elem = current_elem->next;				\
	  }								\
    } while(0)								\

# define MAP_LIST_WITH_BREAK(list, map_fct, arg)			\
    do {								\
      LIST		*current_elem;					\
      if (list == NULL || map_fct == NULL) break;			\
      current_elem = list;						\
      while (current_elem != NULL)					\
	{								\
	  if (map_fct(current_elem, arg) == 0) return ;			\
	  current_elem = current_elem->next;				\
	}								\
    } while(0)								\

# define MAP_LIST_WITH_MATCH(list, map_fct, match_fct, arg)		\
	   do {								\
	     t_list		*current_elem;				\
	     if (list == NULL || match_fct == NULL) break;		\
	     current_elem = list;					\
	     while (current_elem != NULL)				\
	       {							\
		 if (match_fct(current_elem->data, arg))		\
		   {							\
		     if (map_fct != NULL)				\
		       map_fct(current_elem, arg);			\
		     break ;						\
		   }							\
		 current_elem = current_elem->next;			\
	       }							\
	   } while(0)							\

typedef struct	        s_list
{
  void			*data;
  free_function	        free;
  struct s_list		*next;
}		        LIST;

#endif // LIST
