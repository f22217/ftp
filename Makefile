##
## Makefile for myftp in /home/videau_f/rendu/PSU/PSU_2015_myftp
## 
## Made by Florian Videau
## Login   <videau_f@epitech.net>
## 
## Started on  Mon May 02 10:53:33 2016 Florian Videau
## Last update Sun May 15 18:42:49 2016 Florian Videau
##

RM	= rm -f

CFLAGS	+= -W -Wall -Wextra
CFLAGS	+= -I$(INCF)

NAME	= server

SRCF	= src/

INCF	= include/

SRCS	= $(SRCF)child.c	\
	  $(SRCF)data.c		\
	  $(SRCF)directory.c	\
	  $(SRCF)files.c	\
	  $(SRCF)log.c		\
	  $(SRCF)main.c		\
	  $(SRCF)other.c	\
	  $(SRCF)signals.c	\
	  $(SRCF)utils.c

OBJS	= $(SRCS:.c=.o)


$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
