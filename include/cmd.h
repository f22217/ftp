/*
** cmd.h for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/include
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Mon May 09 18:12:46 2016 Florian Videau
** Last update Tue May 10 18:04:46 2016 Florian Videau
*/

#ifndef CMD_H_
# define CMD_H_

#include "my_types.h"

void	user(const char *, t_info *);
void	pass(const char *, t_info *);
void	cwd(const char *, t_info *);
void	cdup(const char *, t_info *);
void	quit(const char *, t_info *);
void	dele(const char *, t_info *);
void	pwd(const char *, t_info *);
void	pasv(const char *, t_info *);
void	port(const char *, t_info *);
void	help(const char *, t_info *);
void	noop(const char *, t_info *);
void	retr(const char *, t_info *);
void	stor(const char *, t_info *);
void	list(const char *, t_info *);

int my_count_space(const char *);
#endif /*!CMD_H_*/
