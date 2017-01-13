/*
** data.c for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/src
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Tue May 10 09:51:01 2016 Florian Videau
** Last update Sun May 15 18:41:25 2016 Florian Videau
*/

#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "cmd.h"

void		pasv(const char *cmd __attribute__((__unused__))
		     , t_info *info)
{
  s_protoent	*pe;
  s_sockaddr_in	addr;
  s_sockaddr_in new_addr;
  char		ports[12];

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  if (!(pe = getprotobyname("TCP")) || (addr.sin_port = 0) ||
  (info->data_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1 ||
  setsockopt(info->data_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
	     &(int){1}, sizeof(int)) == -1)
    return ((void)write(info->fd, "451 local error\r\n", 25));
   if (bind(info->data_fd, (const s_sockaddr *) &addr,
	   sizeof(s_sockaddr_in)) == -1)
    return ((void)write(info->fd, "451 local error\r\n", 25));
  if (listen(info->data_fd, 1) == -1 ||
      getsockname(info->data_fd, (s_sockaddr *) &new_addr,
		  &(socklen_t){sizeof(s_sockaddr_in)}) == -1)
    return ((void)write(info->fd, "451 local error\r\n", 25));
  snprintf(ports, 12, "%03d, %03d)\r\n", new_addr.sin_port % 256,
	   new_addr.sin_port / 256);
  write(info->fd, "227 Entering passive mode(127, 0, 0, 1, ", 40);
  write(info->fd, ports, 11);
}

void	port(const char *cmd, t_info *info)
{
  s_protoent	*pe;
  s_sockaddr_in	addr;

  if (!info->username || !info->passwd)
    return ((void)
	    write(info->fd, "530 Please login with USER and PASS.\r\n", 38));
  if (!(pe = getprotobyname("TCP")) || (addr.sin_port = 0) ||
      (info->data_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1 ||
      setsockopt(info->data_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
		 &(int){1}, sizeof(int)) == -1)
    return ((void)write(info->fd, "451 local error\r\n", 25));
  (void)cmd;
  write(info->fd, "200 Active mode\r\n", 17);
}
