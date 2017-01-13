/*
** directory.c for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/src
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Tue May 10 09:39:44 2016 Florian Videau
** Last update Sat May 14 18:34:33 2016 Florian Videau
*/

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmd.h"

void	cwd(const char *cmd, t_info *info)
{
  char	curr_dir[PATH_MAX];
  char	*go_to;
  char	new_dir[PATH_MAX];

  if (!info->username || !info->passwd)
    return ((void)
	    write(info->fd, "530 Please login with USER and PASS.\r\n", 38));
  if (strlen(cmd) == 6)
    return ((void)write(info->fd, "501 Syntax error\r\n", 18));
  if (!getcwd(curr_dir, PATH_MAX))
    return ((void)write(info->fd, "451 local error\r\n", 25));
  if (!(go_to = strdup(cmd + 4)))
    return ((void)write(info->fd, "451 local error\r\n", 25));
  go_to[go_to[strlen(go_to) - 2] == '\r' ? strlen(go_to) - 2 :
    strlen(go_to) - 1] = 0;
  if (chdir(go_to) == -1)
    return (write(info->fd, "550 access not allowed.\r\n", 25), free(go_to));
  free(go_to);
  if (!getcwd(new_dir, PATH_MAX))
    return ((void)write(info->fd, "451 local error\r\n", 25));
  if (strncmp(new_dir, info->home, strlen(info->home)))
    return (chdir(curr_dir),
	   (void)write(info->fd, "550 access not allowed.\r\n", 25));
  write(info->fd, "250, Directory successfully changed\r\n", 37);
}

void	cdup(const char *cmd __attribute__((unused)),
	     t_info *info)
{
  char	curr_dir[PATH_MAX];

  if (!info->username || !info->passwd)
    return ((void)
	    write(info->fd, "530 Please login with USER and PASS.\r\n", 38));
  if (!getcwd(curr_dir, PATH_MAX))
    return ((void)write(info->fd, "451 local error\r\n", 25));
  if (strlen(curr_dir) == strlen(info->home))
    return ((void)write(info->fd, "550 access not allowed.\r\n", 25));
  chdir("..");
  write(info->fd, "200 Directory successfully changed.\r\n", 37);
}

void	pwd(const char *cmd __attribute__((unused)),
	    t_info *info)
{
  char	curr_dir[PATH_MAX];

  if (!info->username || !info->passwd)
    return ((void)
	    write(info->fd, "530 Please login with USER and PASS.\r\n", 38));
  if (!getcwd(curr_dir, PATH_MAX))
    return ((void)write(info->fd, "451 local error\r\n", 25));
  write(info->fd, "257 /", 5);
  if (strlen(curr_dir) != strlen(info->home))
    write(info->fd, curr_dir + strlen(info->home) + 1,
	  strlen(curr_dir + strlen(info->home) + 1));
  write(info->fd, "\r\n", 2);
}
