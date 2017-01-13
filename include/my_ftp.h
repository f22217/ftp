/*
** my_ftp.h for my_ftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/include
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Mon May 02 13:05:54 2016 Florian Videau
** Last update Wed May 11 18:30:12 2016 Florian Videau
*/

#ifndef MY_FTP_H_
# define MY_FTP_H_

# define print_err(...)		fprintf (stderr, __VA_ARGS__)

extern	int g_fd;
extern	int g_client_fd[950];
extern	int g_client_pid[950];

/*
**child.c
*/
void	child(const int, const char *);
/*
**signals.c
**/
void	get_sigint(int);
void	get_sigint_child(int);
/*
**utils.c
*/
int	display_errno(void);
int	my_is_number(char *);
int	my_count_space(const char *);

#endif /*!MY_FTP_H_*/
