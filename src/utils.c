/*
** utils.c for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Mon May 02 13:45:45 2016 Florian Videau
** Last update Tue May 10 18:03:06 2016 Florian Videau
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "my_ftp.h"

int	display_errno(void)
{
  return (fprintf(stderr, "%s\n", strerror(errno)), 1);
}

int	my_is_number(char *nbr)
{
  while (*nbr && (*nbr >= '0' && *(nbr++) <= '9'));
  return (*nbr ? 0 : 1);
}

int	my_count_space(const char *str)
{
  int	i;

  i = 0;
  while (*str)
    if (*(str++) == ' ')
      i++;
  return (i);
}
