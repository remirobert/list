/*
  The MIT License (MIT)

  Copyright (c) 2014 rémi ROBERT

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/*
** #############################################################################
** @(#)File:           $RCSfile: list.h $
** @(#)Version:        $Revision: 1.0 $
** @(#)Last changed:   $Date: 18/10/2014 $
** @(#)Author:         ROBERT Remi
** #############################################################################
*/

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

# define FREE_DATA_ELEM(current_elem)		\
  do {						\
    if ((LIST *)current_elem != NULL &&		\
	((LIST *)current_elem)->free != NULL)	\
      current_elem->free(current_elem->data);	\
  } while(0)					\

# define FIRST_ELEM_REMOVE_LIST(head_list, node)		\
  do {								\
    LIST		*tmp_elem;				\
    tmp_elem = *head_list;					\
    if ((tmp_elem)->next == NULL)				\
      {								\
	FREE_DATA_ELEM(tmp_elem);				\
        *head_list = NULL;					\
      }								\
    else if ((void *)((*head_list))->data == (void *)node)	\
      {								\
	FREE_DATA_ELEM(tmp_elem);				\
        *head_list = ((*head_list))->next;			\
      }								\
    free(tmp_elem);						\
  } while(0)							\

/*
** #############################################################################
** list_remove_with_data - remove element in the list, with match data.
** @param (parameter list) (the list)
** @param (parameter node) (the data, which will be compare,
** to delete the element)
** @param (parameter match_fct) (the function pointer, for match data)
** @return (void)
** #############################################################################
*/
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
	    FREE_DATA_ELEM(current_elem->next);				\
	    current_elem->next = current_elem->next->next;		\
	    free(tmp_elem);						\
	    break ;							\
	  }								\
	current_elem = current_elem->next;				\
      }									\
  } while(0)								\

/*
** #############################################################################
** list_pop - remove the first element of the list.
** @param (parameter list) (the list)
** @return (void)
** #############################################################################
*/
# define LIST_POP(list)				\
  do {						\
    void			*ptmp;		\
    if (list == NULL || *list == NULL) break;	\
    if ((*list)->next == NULL)			\
      {						\
	if ((*list)->free != NULL)		\
	  (*list)->free((*list)->data);		\
	free(*list);				\
	*list = NULL;				\
	break ;					\
      }						\
    if ((*list)->free != NULL)			\
      (*list)->free((*list)->data);		\
    ptmp = *list;				\
    *list = (*list)->next;			\
    free(ptmp);					\
  } while(0)					\

/*
** #############################################################################
** list_delete - remove all elements in the list.
** @param (parameter list) (the list)
** @return (void)
** #############################################################################
*/
# define DELETE_ALL_LIST(list)			\
    do {					\
      LIST		*current_elem;		\
      void			*ptmp;		\
      if (list == NULL) break;			\
      current_elem = list;			\
      while (current_elem != NULL)		\
	{					\
	  FREE_DATA_ELEM(current_elem);		\
	  ptmp = current_elem;			\
	  current_elem = current_elem->next;	\
	  free(ptmp);				\
	}					\
      list = NULL;				\
    } while(0)					\

/*
** #############################################################################
** list_push - add an element in the head of the list, and add an optional
** function pointer for free the data..
** @param (parameter list) (the list)
** @param (parameter data) (the data, that will be stored in the element)
** @param (parameter function) (the function pointer for free the element)
** @return (void)
** #############################################################################
*/
# define LIST_PUSH(list, data_element, function)	\
    do {						\
      LIST		*current_elem;			\
      LIST		*new_elem;			\
      if ((void *)data_element == NULL) break;		\
      if (*list == NULL)				\
	{						\
	  if ((*list = malloc(sizeof(LIST))) == NULL)	\
	    break ;					\
	  (*list)->data = (void *)data_element;		\
	  (*list)->free = (free_function)function;	\
	  (*list)->next = NULL;				\
	  break ;					\
	}						\
      if ((new_elem = malloc(sizeof(LIST))) == NULL)	\
	break ;						\
      new_elem->data = (void *)data_element;		\
      new_elem->free = (free_function)function;		\
      new_elem->next = NULL;				\
      current_elem = *list;				\
      while (current_elem->next != NULL)		\
	current_elem = current_elem->next;		\
      current_elem->next = new_elem;			\
    } while(0)						\

/*
** #############################################################################
** map_list - allow to apply a function in each element of the list.
** @param (parameter list) (the list)
** @param (parameter map_fct) (the function that will handle all list items)
** @param (parameter arg) (optional argument to pass in your function)
** @return (void)
** #############################################################################
*/
# define MAP_LIST(list, map_fct, arg)			\
    do {						\
      LIST		*current_elem;			\
      if (list == NULL || map_fct == NULL) break;	\
      current_elem = list;				\
      while (current_elem != NULL)			\
	{						\
	  map_fct(current_elem, arg);			\
	  current_elem = current_elem->next;		\
	}						\
    } while(0)						\

/*
** #############################################################################
** map_list_with_break - browse the list, and apply the map_function
** for the first elements that match with the match_function.
** @param (parameter list) (the list)
** @param (parameter map_fct) (the function that will handle all list items,
** and match the element)
** @param (parameter arg) (optional argument to pass in your function)
** @return (void)
** #############################################################################
*/
# define MAP_LIST_WITH_BREAK(list, map_fct, arg)	\
    do {						\
      LIST		*current_elem;			\
      if (list == NULL || map_fct == NULL) break;	\
      current_elem = list;				\
      while (current_elem != NULL)			\
	{						\
	  if (map_fct(current_elem, arg) == 0) return ;	\
	  current_elem = current_elem->next;		\
	}						\
    } while(0)						\

/*
** #############################################################################
** map_list_with_match - browse the list, and apply the map_function for all
** elements that match with the match_function.
** @param (parameter list) (the list)
** @param (parameter map_fct) (the function that will handle all list items)
** @param (parameter match_fct) (the function pointer, for match data,
** for each element)
** @param (parameter arg) (optional argument to pass in your function)
** @return (void)
** #############################################################################
*/
# define MAP_LIST_WITH_MATCH(list, map_fct, match_fct, arg)	\
    do {							\
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
