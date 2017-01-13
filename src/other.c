/*
** other.c for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/src
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Tue May 10 10:00:07 2016 Florian Videau
** Last update Sat May 14 18:35:18 2016 Florian Videau
*/

#include <unistd.h>
#include "cmd.h"

void	help(const char *cmd __attribute__((__unused__)),
	     t_info *info)
{
  if (!info->username || !info->passwd)
    write(info->fd, "530 Please login with USER and PASS.\r\n", 38);
  else
    {
      write(info->fd, "214-The following commands are implemented.\r\n", 45);
      write(info->fd, "USER PASS CWD CDUP QUIT DELE PWD PASV PORT HELP NOOP",
	    52);
      write (info->fd, " RETR STOR LIST\r\n214 help OK\r\n", 30);
    }
}

void	noop(const char *cmd __attribute__((__unused__)),
	     t_info *info)
{
  if (!info->username || !info->passwd)
    write(info->fd, "530 Please login with USER and PASS.\r\n", 38);
  else
    write(info->fd, "200 NOOP ok\r\n", 13);
}
