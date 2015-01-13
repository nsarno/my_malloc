/* -*- C -*-
** malloc.h for malloc in /home/mesure_a/workspace/c/malloc
**
** Made by arnaud mesureur
** Login   <mesure_a@epitech.net>
**
** Started on  Thu Feb 10 14:52:43 2011 arnaud mesureur
** Last update Sat Feb 12 18:52:41 2011 jose rodrigues
*/

#ifndef	MALLOC_H_
#define	MALLOC_H_

#include <stddef.h>
#include <pthread.h>

#define BUCKETS_IDX_MIN	4
#define BUCKETS_IDX_MAX	31
#define BUCKETS_SIZE	32
#define	MAGIC_MDATA	0x31333337

typedef			struct s_meta_data
{
  unsigned int		magic;
  unsigned int		p;
  struct s_meta_data	*next;
}			t_meta_data;

extern t_meta_data	*buckets[BUCKETS_SIZE];
extern pthread_mutex_t	mutex;

void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void *split_block(size_t exp);
void show_alloc_mem();

#endif	/* !MALLOC_H_ */
