#include "list.h"

/*
** #############################################################################
** # Apply a function on each element on the list
** #############################################################################
*/
void			map_list(t_list *list,
				 map_function map_fct, void *arg)
{
  t_list		*current_elem;

  if (list == NULL || map_fct == NULL)
    return ;
  current_elem = list;
  while (current_elem != NULL)
    {
      map_fct(current_elem, arg);
      current_elem = current_elem->next;
    }
}

/*
** #############################################################################
** # Browse the elements and stop to the first match
** #############################################################################
*/
void			map_list_with_break(t_list *list,
					    map_function_ret map_fct, void *arg)
{
  t_list		*current_elem;

  if (list == NULL || map_fct == NULL)
    return ;
  current_elem = list;
  while (current_elem != NULL)
    {
      if (map_fct(current_elem, arg) == 0)
	return ;
      current_elem = current_elem->next;
    }
}

/*
** #############################################################################
** # Browse the elements and apply a function oon all element matched
** #############################################################################
*/
void			map_list_with_match(t_list *list,
					    map_function map_fct,
					    match_function match_fct, void *arg)
{
  t_list		*current_elem;

  if (list == NULL || match_fct == NULL)
    return ;
  current_elem = list;
  while (current_elem != NULL)
    {
      if (match_fct(current_elem->data, arg))
	{
	  if (map_fct != NULL)
	    map_fct(current_elem, arg);
	  return ;
	}
      current_elem = current_elem->next;
    }
}
