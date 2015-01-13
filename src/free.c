/*
 ** free.c for malloc in /home/mesure_a/workspace/c/malloc
 **
 ** Made by arnaud mesureur
 ** Login   <mesure_a@epitech.net>
 **
 ** Started on  Thu Feb 10 15:01:08 2011 arnaud mesureur
 ** Last update Thu Feb 17 11:39:07 2011 arnaud mesureur
 */

#include "malloc.h"

t_meta_data *buckets[BUCKETS_SIZE];

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


void		free(void *ptr)
{
  t_meta_data	*md;

  pthread_mutex_lock(&mutex);
  if (ptr <= (void*)0)
  {
    pthread_mutex_unlock(&mutex);
    return;
  }
  md = (t_meta_data*)ptr - 1;
  if (md->magic != MAGIC_MDATA)
  {
    pthread_mutex_unlock(&mutex);
    return;
  }
  if (!_is_not_free(md))
  {
    pthread_mutex_unlock(&mutex);
    return;
  }
  md->next = buckets[md->p];
  buckets[md->p] = md;
  pthread_mutex_unlock(&mutex);
}

