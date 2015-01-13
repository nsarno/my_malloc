/*
** realloc.c for realloc in /home/mesure_a/workspace/c/malloc
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Thu Feb 10 22:26:55 2011 arnaud mesureur
** Last update Sat Feb 12 20:09:48 2011 jose rodrigues
*/

#include <string.h>

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
  void		*new;
  size_t	i;

  i = 0;
  if (!(new = malloc(size)))
    return (NULL);
  pthread_mutex_lock(&mutex);
  if (!ptr)
  {
    pthread_mutex_unlock(&mutex);
    return (new);
  }
  while (i < size)
  {
    ((char*)new)[i] = ((char*)ptr)[i];
    ++i;
  }
  pthread_mutex_unlock(&mutex);
  free(ptr);
  return (new);
}

