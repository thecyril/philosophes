/*
** thread.c for PSU_2016_philo
**
** Made by	Cyril Puccio
** Login	cyril.puccio@epitech.eu
**
** Started on	Tue Mar 14 15:43:59 2017 Cyril Puccio
** Last update	Wed Mar 15 17:27:25 2017 Cyril Puccio
*/

#include "extern.h"
#include "philosophe.h"

int		stop = 0;

void            eat(t_philo *philo)
{
  philo->rice = philo->rice - 1;
  philo->state = 1;
  lphilo_take_chopstick(&philo->mutex);
  lphilo_take_chopstick(&philo->hand->mutex);
  lphilo_eat();
  lphilo_release_chopstick(&philo->mutex);
  lphilo_release_chopstick(&philo->hand->mutex);
  pthread_mutex_unlock(&philo->mutex);
  pthread_mutex_unlock(&philo->hand->mutex);
}

void            think(t_philo *philo, int a)
{
  if (a == 0)
    lphilo_take_chopstick(&philo->mutex);
  else
    lphilo_take_chopstick(&philo->hand->mutex);
  philo->state = 0;
  lphilo_think();
  if (a == 0)
    {
      lphilo_release_chopstick(&philo->mutex);
      pthread_mutex_unlock(&philo->mutex);
    }
  else
    {
      lphilo_release_chopstick(&philo->hand->mutex);
      pthread_mutex_unlock(&philo->hand->mutex);
    }
}

void            rest(t_philo *philo)
{
  lphilo_sleep();
  philo->state = 2;
}

void		action(t_philo *philo)
{
  int		a;
  int		b;

  if (philo->state == 0)
    {
      a = pthread_mutex_trylock(&philo->mutex);
      b = pthread_mutex_trylock(&philo->hand->mutex);
      if (a == 0 && b != 0)
        pthread_mutex_unlock(&philo->mutex);
      else if (b == 0 && a != 0)
        pthread_mutex_unlock(&philo->hand->mutex);
      else if (b == 0 && a == 0)
        eat(philo);
    }
  else if (philo->state == 2)
    {
      a = pthread_mutex_trylock(&philo->mutex);
      if (a != 0)
	b = pthread_mutex_trylock(&philo->hand->mutex);
      if (a == 0 || b == 0)
	think(philo, a);
    }
  else if (philo->state == 1)
    rest(philo);
}

void		*state_loop(void *arg)
{
  t_philo	*philo;

  philo = (t_philo*)arg;
  while (philo->rice != 0 && stop == 0)
    {
      usleep(rand() % 5000);
      action(philo);
    }
  stop = 1;
  return (NULL);
}
