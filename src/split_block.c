/*
** split_block.c for  in /home/rodrig_d/rendu/proj/malloc
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Feb 11 16:47:52 2011 jose rodrigues
** Last update Fri Feb 11 19:10:11 2011 jose rodrigues
*/

#include <stdlib.h>
#include "malloc.h"

static void		*dispatch_block(size_t s_exp, size_t exp)
{
  size_t	block_size;
  t_meta_data	*new_block;
  t_meta_data	*block_to_split;

  new_block = buckets[s_exp];
  buckets[s_exp] = buckets[s_exp]->next;
  new_block->p = exp;
  new_block->magic = MAGIC_MDATA;
  block_to_split = (t_meta_data *)((char *)new_block + (1 << exp));
  block_size = (1 << s_exp) - (1 << exp);
  while (block_size)
  {
    --s_exp;
    block_to_split->next = buckets[s_exp];
    block_to_split->p = s_exp;
    block_to_split->magic = MAGIC_MDATA;
    buckets[s_exp] = block_to_split;
    block_to_split = (t_meta_data *)((char *)block_to_split + (1 << s_exp));
    block_size = block_size - (1 << s_exp);
  }
  return (new_block);
}

void		*split_block(size_t exp)
{
  size_t	s_exp;

  s_exp = exp + 1;
  while (s_exp <= BUCKETS_IDX_MAX)
  {
    if (buckets[s_exp])
      return (dispatch_block(s_exp, exp));
    ++s_exp;
  }
  return (NULL);
}

