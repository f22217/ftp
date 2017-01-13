/*
** log.c for myftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/src
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Mon May 09 17:34:28 2016 Florian Videau
** Last update Sat May 14 17:03:14 2016 Florian Videau
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cmd.h"

void	user(const char *cmd, t_info *info)
{
  if (my_count_space(cmd) != 1)
    return ((void)(write(info->fd, "501 Syntax error in arguments.\r\n", 32)));
  if (strcasecmp("Anonymous\r\n", cmd + 5) &&
      strcasecmp("Anonymous\n", cmd + 5))
    return ((void)(write(info->fd, "331 This ftp is anonymous only\r\n", 32)));
  info->passwd = FALSE;
  if (!(info->username = strdup("Anonymous")))
    return ((void)(write(info->fd, "451 local error in processing.\r\n", 32)));
  write(info->fd, "331 User name okay, need password.\r\n", 36);
}

void	pass(const char *cmd, t_info *info)
{
  if (!info->username)
    return ((void)(write(info->fd, "530 Login with USER first\r\n", 27)));
  else if (!strcasecmp(info->username, "Anonymous") &&
	   (!strcasecmp(cmd, "PASS\n") || !strcasecmp(cmd, "PASS\r\n") ||
	    !strcasecmp(cmd, "PASS \r\n") || !strcasecmp(cmd, "PASS \n")))
    return (info->passwd = 1,
	    (void)(write(info->fd, "230 User logged in proceed\r\n", 28)));
  return ((void)(write(info->fd, "332 Need account for login.\r\n", 29)));
}
