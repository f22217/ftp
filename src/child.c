/*
** child.c for myftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/src
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Wed May 04 12:59:13 2016 Florian Videau
* Last update Mon May 09 16:39:43 2016 Florian Videau
*/

#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include "my_ftp.h"
#include "my_types.h"
#include "cmd.h"

static int exec_cmd(char *buff, t_info *info)
{
  t_cmd		*array;
  int		i;

  if (!strcasecmp(buff, "QUIT\n") || !strcasecmp(buff, "QUIT\r\n"))
    return (1);
#include "array.h"
 i = 0;
  while (array[i].cmd && strncasecmp(array[i].cmd, buff, array[i].len))
    i++;
  if (!array[i].cmd)
    write(info->fd, "502 Command not implemented\r\n", 29);
  else if (buff[strlen(buff) - 1] != '\n')
    write(info->fd, "500 End of line not OK\r\n", 24);
  else
    array[i].fct(buff, info);
  free(buff);
  return (0);
}

static void	free_info(t_info *info, const int nbr, char *to_send)
{
  write(info->fd, "221 Goodbye\r\n", 13);
  if (shutdown(info->fd, SHUT_RDWR) || close(info->fd))
    display_errno();
  g_client_fd[nbr] = 0;
  if (info->username)
    free(info->username);
  if (info->home)
    free(info->home);
  free(to_send);
}

static int	init_info(t_info *info, const int nbr, const char home[PATH_MAX])
{
  signal(SIGINT, get_sigint_child);
  info->username = NULL;
  info->passwd = FALSE;
  info->fd = g_client_fd[nbr];
  if (!(info->home = strdup(home)))
    return (write(info->fd, "451 local error\r\n", 25), 1);
  info->data_fd = 0;
  write(info->fd, "220 Service ready for new user\r\n", 32);
  return (0);
}

void		child(const int nbr, const char home[PATH_MAX])
{
  char		*buff;
  char		*to_send;
  int		len;
  int		quit;
  t_info	info;

  quit = init_info(&info, nbr, home);
  if (!(to_send = calloc(1, sizeof(char))))
    return ((void)display_errno());
  while (!quit && !(len = 0))
    if (ioctl(g_client_fd[nbr], FIONREAD, &len) == -1)
      return ((void)display_errno());
    else if (len)
      {
	if (!(buff = calloc(len + 1, sizeof(char))) ||
	    read(g_client_fd[nbr], buff, len) == -1 ||
	    !(to_send = realloc(to_send, strlen(to_send) + strlen(buff) + 1)) ||
	    !strcat(to_send, buff))
	  return ((void)display_errno());
	if (to_send[strlen(to_send) - 1] == '\n')
	  if (!((quit = exec_cmd(to_send, &info)) || 1) ||
	      !(to_send = calloc(1, sizeof(char))))
	    return ((void)display_errno);
	free(buff);
      }
  free_info(&info, nbr, to_send);
}
