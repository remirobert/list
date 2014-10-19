/*
** #############################################################################
** @(#)File:           $RCSfile: list.h $
** @(#)Version:        $Revision: 1.0 $
** @(#)Last changed:   $Date: 18/10/2014 $
** @(#)Author:         ROBERT Remi
** #############################################################################
*/

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct s_list t_list;

typedef void (*free_function)(void *);
typedef int (*match_function)(void *, void *);
typedef void (*map_function)(t_list *, void *);
typedef int (*map_function_ret)(t_list *, void *);

typedef struct		s_list
{
  void			*data;
  free_function	        free;
  struct s_list		*next;
}			t_list;

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
void		        list_remove_with_data(t_list **list, void *node,
					      match_function match_fct);

/*
** #############################################################################
** list_pop - remove the first element of the list.
** @param (parameter list) (the list)
** @return (void)
** #############################################################################
*/
void			list_pop(t_list **list);

/*
** #############################################################################
** list_delete - remove all elements in the list.
** @param (parameter list) (the list)
** @return (void)
** #############################################################################
*/
void			list_delete(t_list *list);

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
void		        list_push(t_list **list, void *data,
				  free_function function);

/*
** #############################################################################
** map_list - allow to apply a function in each element of the list.
** @param (parameter list) (the list)
** @param (parameter map_fct) (the function that will handle all list items)
** @param (parameter arg) (optional argument to pass in your function)
** @return (void)
** #############################################################################
*/
void			map_list(t_list *list, map_function map_fct, void *arg);

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
void			map_list_with_match(t_list *list,
					    map_function map_fct,
					    match_function match_fct, void *arg);

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
void			map_list_with_break(t_list *list,
					    map_function_ret map_fct, void *arg);

#endif // LIST
