## Makefile for lib malloc in /home/mesure_a/workspace/c/malloc
## 
## Made by arnaud mesureur
## Login   <mesure_a@epitech.net>
## 
## Started on  Thu Feb  3 13:09:02 2011 arnaud mesureur
## Last update Sat Feb 12 19:08:28 2011 jose rodrigues
##

SHELL		=	/bin/sh

SRCDIR		=	src
OBJDIR		=	obj
HDRDIR		=	inc

VPATH		=	$(SRCDIR)

CC		=	gcc
CFLAGS		+=	-Wextra -Wall -ansi -pedantic
CFLAGS		+=	-D_BSD_SOURCE
LDFLAGS		+=	-shared
INCLUDE		=	-I. -I$(HDRDIR)

NAME		=	libmy_malloc.so
SRCS		=	malloc.c	\
			realloc.c	\
			free.c		\
			split_block.c	\
			show_alloc_mem.c
OBJS		=	$(SRCS:%.c=$(OBJDIR)/%.o)

RM		=	rm -f
TAGS		=	etags

$(NAME)		: $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all

$(OBJDIR)/%.o	: %.c
		$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDE) -o $@ -c $<
