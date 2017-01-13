/*
** main.c for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/src
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Mon May 02 13:09:22 2016 Florian Videau
** Last update Sun May 15 15:55:42 2016 Florian Videau
*/

#include <arpa/inet.h>
#include <limits.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include "my_ftp.h"
#include "my_types.h"

int	g_fd = 0;
int	g_client_fd[950] = {0};
int	g_client_pid[950] = {0};

static int	my_ftp_loop(char home[PATH_MAX])
{
  s_sockaddr_in	clt_addr;
  int		i;
  int		pid;

  while (1)
    {
      i = -1;
      while (g_client_fd[++i]);
      if ((g_client_fd[i] = accept(g_fd, (s_sockaddr *) &clt_addr,
				   &(socklen_t){sizeof(s_sockaddr_in)})) == -1)
	return (close(g_fd), display_errno());
      if ((pid = fork()) == -1)
	return (close(g_fd), display_errno());
      if (!pid)
	{
	  child(i, home);
	  g_client_pid[i] = 0;
	  exit(EXIT_SUCCESS);
	}
      else
	g_client_pid[i] = pid;
    }
  return (0);
}

static int		init_ftp(int port)
{
  s_protoent	*pe;
  s_sockaddr_in	addr;

  if (!(pe = getprotobyname("TCP")))
    return (print_err("Could not get TCP proto\n"), 1);
  else if ((g_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (display_errno());
  if (setsockopt(g_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
		 &(int){1}, sizeof(int)) == -1)
    return (close(g_fd), display_errno());
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(g_fd, (const s_sockaddr *) &addr, sizeof(s_sockaddr_in)) == -1)
    return (close(g_fd), display_errno());
  if (listen(g_fd, 950) == -1)
    return (close(g_fd), display_errno());
  return 0;
}

int	main(int ac, char **av)
{
  char		absolute_path[PATH_MAX];

  signal(SIGINT, &get_sigint);
  if (ac != 3)
    return (print_err("Usage : %s port path", av[0]), 1);
  if (!my_is_number(av[1]))
    return (print_err("Port must be a number\n"), 1);
  if (init_ftp(atoi(av[1])))
    return (-1);
  if (chdir(av[2]) == -1)
    return (display_errno());
  if (!getcwd(absolute_path, PATH_MAX))
    return (display_errno());
  printf("%s\n", absolute_path);
  my_ftp_loop(absolute_path);
  return (0);
}
