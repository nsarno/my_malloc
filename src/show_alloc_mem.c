/*
** show_alloc_mem.c for  in /home/rodrig_d/rendu/proj/malloc
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Sat Feb 12 18:39:09 2011 jose rodrigues
** Last update Thu Feb 17 11:46:10 2011 arnaud mesureur
*/

#include <stdio.h>
#include <unistd.h>
#include "malloc.h"

static int	_is_not_free(t_meta_data *data)
{
  t_meta_data	*freelist;

  freelist = buckets[data->p];
  while (freelist)
  {
    if (freelist == data)
      return (0);
    freelist = freelist->next;
  }
  return (1);
}

void		show_alloc_mem()
{
  static char	*start_brk = NULL;
  char		*actual_brk;
  char		*brk;

  if (!start_brk)
    start_brk = sbrk(0);

  actual_brk = sbrk(0);
  brk = start_brk;
  while (brk + sizeof(t_meta_data) < actual_brk)
  {
    if (_is_not_free((t_meta_data *)brk))
    {
      if (((t_meta_data *)brk)->magic == MAGIC_MDATA)
        printf("%p - %p : %u octets\n", brk, brk
            + (1 << ((t_meta_data *)brk)->p),
            (1 << ((t_meta_data *)brk)->p));
    }
    brk += (1 << ((t_meta_data *)brk)->p);
  }
}
