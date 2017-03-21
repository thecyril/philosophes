/*
** philosophe.h for philosophe in /home/prost_m/Rendu/Semestre_4/PSU_2016_philo/include/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Wed Mar 15 19:01:14 2017 Matthias Prost
** Last update Wed Mar 15 20:51:49 2017 Matthias Prost
*/

#ifndef _PHILOSOPHE_H_
#define _PHILOSOPHE_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

typedef struct			s_values
{
  int				nb_philo;
  int				rice;
}				t_values;

typedef struct			s_philo
{
  int				rice;
  int				state;
  int       id;
  struct s_philo		*hand;
  pthread_mutex_t		mutex;
  t_values			*val;
}				t_philo;

void				*state_loop(void *arg);
void				rest(t_philo *philo);
int				my_str_is_num(char *str);

#endif
