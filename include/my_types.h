/*
** types.h for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/include
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Mon May 09 18:15:58 2016 Florian Videau
** Last update Sun May 15 00:05:48 2016 Florian Videau
*/

#ifndef MY_TYPES_H_
# define MY_TYPES_H_

typedef struct protoent s_protoent;
typedef struct sockaddr s_sockaddr;
typedef struct sockaddr_in s_sockaddr_in;

typedef enum	e_bool
{
  FALSE,
  TRUE
}		t_bool;

typedef struct	s_info
{
  char		*username;
  t_bool	passwd;
  int		fd;
  char		*home;
  int		data_fd;
}		t_info;

typedef struct	s_cmd
{
  char		*cmd;
  int		len;
  void		(*fct) (const char *, t_info *);
}		t_cmd;

#endif /*!MY_TYPES_H_*/
