/*
** files.c for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/src
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Tue May 10 09:47:43 2016 Florian Videau
** Last update Sun May 15 18:40:31 2016 Florian Videau
*/

#include <dirent.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "cmd.h"

void	dele(const char *cmd, t_info *info)
{
  char	*to_dele;

  if (!info->username || !info->passwd)
    return ((void)
	    write(info->fd, "530 Please login with USER and PASS.\r\n", 38));
  if (!strcasecmp(info->username, "anonymous"))
    return ((void)write(info->fd, "550 access not allowed.\r\n", 25));
  if (!(to_dele = strdup(cmd + 5)))
    return ((void)write(info->fd, "451 local error\r\n", 25));
  to_dele[to_dele[strlen(to_dele) - 2] == '\r' ? strlen(to_dele) - 2 :
    strlen(to_dele) - 1] = 0;
  if (remove(to_dele) == -1)
    return ((void)write(info->fd, "550 access not allowed.\r\n", 25));
  return ((void)write(info->fd, "250 dele OK\r\n", 13));
}

static char	*check_args(const char *cmd, t_info *info)
{
  char		*to_transfer;

  if (!info->username || !info->passwd)
    return (write(info->fd, "530 Please login with USER and PASS\r\n", 37),
	    NULL);
  if (!info->data_fd)
    return (write(info->fd, "425 use port or pasv first\r\n", 28), NULL);
  if (strlen(cmd) == 7)
    return (write(info->fd, "550 Failed to open file\r\n", 25), NULL);
  if (!(to_transfer = strdup(cmd + 5)))
    return (write(info->fd, "451 local error\r\n", 25), NULL);
  to_transfer[to_transfer[strlen(to_transfer) - 2] == '\r' ?
    strlen(to_transfer) - 2 : strlen(to_transfer) - 1] = 0;
  return (to_transfer);
}

void		retr(const char *cmd, t_info *info)
{
  s_sockaddr_in	clt_addr;
  char		*to_transfer;
  int		f_fd;
  char		*f_data;
  int		size;

  if (!(to_transfer = check_args(cmd, info)))
    return;
  if ((f_fd = open(to_transfer, O_RDONLY)) == -1)
    return ((void) write(info->fd, "550 Failed to open file\r\n", 25));
  if ((size = lseek(f_fd, 0, SEEK_END)) == -1 || lseek(f_fd, -size, SEEK_END)
      == -1 || !(f_data = malloc(size)) || read(f_fd, f_data, size) == -1 ||
      close(f_fd) == -1 ||
      (f_fd = accept(info->data_fd, (s_sockaddr *) &clt_addr,
		     &(socklen_t){sizeof(s_sockaddr_in)})) == -1)
    return ((void)write(info->fd, "451 local error\r\n", 25));
  write(info->fd, "150, sending data\r\n", 19);
  if (write(f_fd, f_data, size) == -1)
    return ((void)write(info->fd, "451 local error\r\n", 25));
  return (close(f_fd), close(info->data_fd), info->data_fd = 0, free(f_data),
	  free(to_transfer), (void) write(info->fd, "226 send OK\r\n", 13));
}

void	stor(const char *cmd, t_info *info)
{
  if (!info->username || !info->passwd)
    return ((void)
	    write(info->fd, "530 Please login with USER and PASS.\r\n", 38));
  if (!info->data_fd)
    return ((void) write(info->fd, "425 use port or pasv first\r\n", 28));
  if (!strcasecmp(info->username, "anonymous"))
    return ((void)write(info->fd, "550 access not allowed.\r\n", 25));
  (void) cmd;
}

void		list(const char *cmd __attribute__((__unused__)),
		     t_info *info)
{
  s_sockaddr_in	clt_addr;
  DIR		*dir;
  struct dirent	*file;
  int		fd;

  if (!info->username || !info->passwd)
    return ((void)
	    write(info->fd, "530 Please login with USER and PASS\r\n", 37));
  if (!info->data_fd)
    return ((void)write(info->fd, "425 use port or pasv first\r\n", 28));
  if (!(dir = opendir(".")))
    return ((void)write(info->fd, "451 local error\r\n", 25));
  if ((fd = accept(info->data_fd, (s_sockaddr *) &clt_addr,
		     &(socklen_t){sizeof(s_sockaddr_in)})) == -1)
    return ((void)write(info->fd, "451 local error\r\n", 25));
  write(info->fd, "150, sending data\r\n", 19);
  while ((file = readdir(dir)))
    {
      write(fd, file->d_name, strlen(file->d_name));
      write(fd, " ", 1);
    }
  return (write(fd, "\r\n", 2), close(fd), close(info->data_fd),
	  info->data_fd = 0, (void) write(info->fd, "226 send OK\r\n", 13));
}
