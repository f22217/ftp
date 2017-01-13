/*
** array.h for myftp in /home/videau_f/rendu/PSU/PSU_2015_myftp/include
** 
** Made by Florian Videau
** Login   <videau_f@epitech.net>
** 
** Started on  Wed May 11 15:13:25 2016 Florian Videau
** Last update Sun May 15 18:43:33 2016 Florian Videau
*/

#ifndef ARRAY_H_
# define ARRAY_H_
array = (__typeof(*array)[24]){{"USER ", 5, user}, {"PASS ", 5, pass},
    {"PASS\n", 5, pass}, {"PASS\r\n", 6, pass}, {"CWD ", 4, cwd},
    {"CDUP\r\n", 6, cdup}, {"CDUP\n", 5, cdup}, {"DELE ", 5, dele},
    {"PWD\r\n", 5, pwd}, {"PWD\n", 4, pwd}, {"PASV\r\n", 6, pasv},
    {"PASV\n", 5, pasv}, {"PORT ", 5, port}, {"HELP ", 5, help},
    {"HELP\r\n", 6, help}, {"HELP\n", 5, help}, {"NOOP\r\n", 6, noop},
    {"NOOP\n", 5, noop}, {"RETR ", 5, retr}, {"STOR ", 5, stor},
    {"LIST ", 5, list}, {"LIST\r\n", 6, list}, {"LIST\n", 5, list},
    {NULL, 0, NULL}};
#endif /*!ARRAY_H*/
