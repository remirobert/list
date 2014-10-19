#include "list.h"

void		        list_push(t_list **list, void *data,
				  free_function function)
{
  t_list		*current_elem;
  t_list		*new_elem;

  if (*list == NULL)
    {
      if ((*list = malloc(sizeof(t_list))) == NULL)
	return ;
      (*list)->data = data;
      (*list)->free = function;
      (*list)->next = NULL;
      return ;
    }
  if ((new_elem = malloc(sizeof(t_list))) == NULL)
    return ;
  new_elem->data = data;
  new_elem->free = function;
  new_elem->next = NULL;
  current_elem = *list;
  while (current_elem->next != NULL)
    current_elem = current_elem->next;
  current_elem->next = new_elem;
}
