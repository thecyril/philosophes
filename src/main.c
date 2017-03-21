/*
** main.c for philosophe in /home/prost_m/Rendu/Semestre_4/PSU_2016_philo/src/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Wed Mar 15 19:01:22 2017 Matthias Prost
** Last update Fri Mar 17 13:26:52 2017 Cyril
*/

#include "extern.h"
#include "philosophe.h"

int		 cleanup_thread(t_philo *philo)
{
  if (pthread_mutex_destroy(&philo->mutex) != 0)
    fprintf(stderr, "ERROR: Failed to destroy a mutex\n");
  free(philo);
  return (0);
}

int		init_thread(t_philo *philo)
{
  pthread_t	threads[philo->val->nb_philo];
  int		i;

  (void)threads;
  i = -1;
  while (++i != philo->val->nb_philo)
    {
      if (pthread_create(&threads[i], NULL, &state_loop, &philo[i]))
      	{
      	  fprintf(stderr, "ERROR: Thread creation failed\n");
      	  return (-1);
      	}
    }
  i = -1;
  while (++i != philo->val->nb_philo)
    pthread_join(threads[i], NULL);
  cleanup_thread(philo);
  return (0);
}

int		fill_tab(t_values *values)
{
  t_philo	*philo;
  int		i;

  i = -1;
  if (values->nb_philo < 2)
    {
      fprintf(stderr, "ERROR: insufisant number of philosopher\n");
      return (-1);
    }
  if ((philo = malloc(sizeof(t_philo) * values->nb_philo)) == NULL)
    return (-1);
  philo->val = values;
  while (++i != values->nb_philo)
    {
      philo[i].id = i;
      if (rand() % 2 == 0)
        philo[i].state = 0;
      else
        philo[i].state = 2;
      philo[i].rice = values->rice;
      philo[i].hand = &philo[i + 1];
      philo[i].mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    }
  philo[values->nb_philo - 1].hand = &philo[0];
  return (init_thread(philo));
}

int		verif(t_values *value, int ac, char **av)
{
  int		i;

  i = 0;
  while (++i != ac)
    {
      if (strcmp(av[i], "-p") == 0)
	{
	  if ((value->nb_philo = my_str_is_num(av[++i])) == -1)
	    return (fprintf(stderr, "Error: argument -p is invalid\n"));
	}
      else if (strcmp(av[i], "-e") == 0)
	{
	  if ((value->rice = my_str_is_num(av[++i])) == -1)
	    return (fprintf(stderr, "Error: argument -e is invalid\n"));
	}
      else
	return (fprintf(stderr, "USAGE: ./philo -p [nbr] -e [nbr]\n"));
    }
  return (2);
}

int		main(int ac, char **av)
{
  t_values	value;

  if (ac != 5)
    return (fprintf(stderr, "USAGE: ./philo -p [nbr] -e [nbr]\n"));
  if (verif(&value, ac, av) != 2)
    return (0);
  RCFStartup(ac, av);
  if (fill_tab(&value) == -1)
    return (0);
  RCFCleanup();
  return (0);
}
