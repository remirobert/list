#include "list.h"

static void			free_data_elem(t_list *current_elem)
{
  if (current_elem != NULL &&
      current_elem->free != NULL)
    current_elem->free(current_elem->data);
}


static void		first_elem_remove_list(t_list **head_list, void *node)
{
  t_list		*tmp_elem;

  tmp_elem = *head_list;
  if ((*head_list)->next == NULL)
    {
      free_data_elem(*head_list);
      *head_list = NULL;
    }
  else if ((*head_list)->data == node)
    {
      free_data_elem(*head_list);
      *head_list = (*head_list)->next;
    }
  free(tmp_elem);
}

/*
** #############################################################################
** # Delete an element owith a specific data
** #############################################################################
*/
void		        list_remove_with_data(t_list **head_list, void *node,
					      match_function match_fct)
{
  t_list		*current_elem;
  t_list		*tmp_elem;

  if (head_list == NULL || *head_list == NULL)
    return ;
  current_elem = *head_list;
  if (match_fct((*head_list)->data, node) == 0)
    {
      first_elem_remove_list(head_list, node);
      return ;
    }
  while (current_elem->next != NULL)
    {
      if (match_fct(current_elem->next->data, node) == 0)
	{
	  tmp_elem = current_elem->next;
	  free_data_elem(current_elem->next);
	  current_elem->next = current_elem->next->next;
	  free(tmp_elem);
	  return ;
	}
      current_elem = current_elem->next;
    }
}

/*
** #############################################################################
** # Delete the first element of the list
** #############################################################################
*/
void			list_pop(t_list **list)
{
  void			*ptmp;

  if (list == NULL || *list == NULL)
    return ;
  if ((*list)->next == NULL)
    {
      if ((*list)->free != NULL)
	(*list)->free((*list)->data);
      free(*list);
      *list = NULL;
      return ;
    }
  if ((*list)->free != NULL)
    (*list)->free((*list)->data);
  ptmp = *list;
  *list = (*list)->next;
  free(ptmp);
}

/*
** #############################################################################
** # Delete all the list
** #############################################################################
*/
void			list_delete(t_list *list)
{
  t_list		*current_elem;
  void			*ptmp;

  if (list == NULL)
    return ;
  current_elem = list;
  while (current_elem != NULL)
    {
      if (current_elem->free != NULL)
	current_elem->free(current_elem->data);
      ptmp = current_elem;
      current_elem = current_elem->next;
      free(ptmp);
    }
  list = NULL;
}
