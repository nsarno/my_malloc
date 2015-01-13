/*
** malloc.c for malloc in /home/mesure_a/workspace/c/malloc
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Thu Feb 10 14:43:44 2011 arnaud mesureur
** Last update Thu Feb 17 15:24:16 2011 arnaud mesureur
*/

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "malloc.h"

static void	*gl_page_mem = NULL;
static size_t	gl_page_mem_size = 0;

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

static size_t	expsize(size_t size)
{
  size_t	exp;

  exp = BUCKETS_IDX_MIN;
  while ((size_t)(1 << exp) < size)
    ++exp;
  return (exp);
}

static int	alloc_new_page(size_t size)
{
  static int	page_size = 0;
  size_t	mem_size;
  void		*mem;

  if (!page_size)
    page_size = getpagesize();
  mem_size = page_size * ((size - 1) / page_size + 1);
  mem = sbrk(mem_size);
  if ((int)mem == -1)
    return (-1);
  gl_page_mem = mem;
  gl_page_mem_size = mem_size;
  return (0);
}

static void	*split_page(size_t size)
{
  t_meta_data	*block;
  size_t	i;

  if (gl_page_mem_size <= 0 || size > gl_page_mem_size)
    return (NULL);
  i = expsize(size);
  block = gl_page_mem;
  block->magic = MAGIC_MDATA;
  block->p = i;
  gl_page_mem_size -= size;
  gl_page_mem = (char*)gl_page_mem + size;
  return (block);
}

static void	*alloc_from_page(size_t size)
{
  t_meta_data	*block;
  size_t	exp;

  exp = expsize(size);
  if (!buckets[exp])
  {
    block = split_block(exp);
    if (block)
      return (block);
    block = split_page(size);
    if (!block)
      return (NULL);
    return (block);
  }
  block = buckets[exp];
  buckets[exp] = block->next;
  return (block);
}

void		*malloc(size_t size)
{
  t_meta_data	*block;
  static int	flag = 0;

  pthread_mutex_lock(&mutex);
  /* if (!flag) */
  /*   { */
  /*     /\* show_alloc_mem(); *\/ */
  /*     flag = 1; */
  /*   } */
  if (size > (size_t)(1 << 31))
  {
    pthread_mutex_unlock(&mutex);
    return (NULL);
  }
  size = (size_t)(1 << expsize(size + sizeof(*block)));
  block = alloc_from_page(size);
  if (!block)
  {
    if (alloc_new_page(size) == -1)
    {
      pthread_mutex_unlock(&mutex);
      return (NULL);
    }
    block = alloc_from_page(size);
  }
  pthread_mutex_unlock(&mutex);
  return (block + 1);
}

