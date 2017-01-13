/*
** signals.c for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/src
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Tue May 03 15:51:26 2016 Florian Videau
** Last update Thu May 12 10:52:36 2016 Florian Videau
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include "my_ftp.h"

void	get_sigint(int __attribute__((unused))signal)
{
  int	i;

  printf("Closing fds\n");
  if (close(g_fd) == -1)
    display_errno();
  i = -1;
  while (++i < 950)
    {
      if (g_client_fd[i] && (shutdown(g_client_fd[i], SHUT_RDWR) ||
			     close(g_client_fd[i])))
	display_errno();
      if (g_client_pid[i])
	waitpid(g_client_pid[i], NULL, 0);
    }
  printf("Server exiting\n");
  exit(0);
}

void	get_sigint_child(int __attribute__((unused))signal)
{
  exit(EXIT_SUCCESS);
}
