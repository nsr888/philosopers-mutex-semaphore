/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:39:00 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/25 15:46:24 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Open all semaphores n times before close, otherwise it will be locked forever
*/

void				destroy_semaphores(t_sem *sem, int number_of_philosophers)
{
	int				i;

	i = -1;
	while (++i < number_of_philosophers)
		sem_post(sem->forks);
	sem_close(sem->forks);
	i = -1;
	while (++i < number_of_philosophers)
		sem_post(sem->steward);
	sem_close(sem->steward);
	i = -1;
	while (++i < number_of_philosophers)
		sem_post(sem->write_lock);
	sem_close(sem->write_lock);
}

static t_vars		*init_vars_struct(t_argv args, t_philosophers *philo, \
		pthread_t *ptr)
{
	t_vars			*vars;

	if (!(vars = malloc(sizeof(*vars))))
		return (NULL);
	vars->ptr = ptr;
	vars->args = args;
	vars->sem = philo[0].sem;
	vars->shared = philo[0].shared;
	return (vars);
}

static void			clean_all(t_philosophers *philo, pthread_t *ptr)
{
	free(philo[0].sem);
	free(philo[0].shared->mute_messages);
	free(philo[0].shared->time_of_start);
	free(philo[0].shared->eat_count);
	free(philo[0].shared->timestamp_last_meal);
	free(philo[0].shared);
	free(philo);
	free(ptr);
}

static int			is_input_has_errors(int argc, char **argv)
{
	char			*s1;

	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) < 2)
	{
		s1 = "Incorrect number of arguments\n";
		write(2, s1, ft_strlen(s1));
		return (1);
	}
	return (0);
}

int					main(int argc, char **argv)
{
	t_philosophers	*philo;
	t_argv			args;
	t_vars			*vars;
	pthread_t		*ptr;
	int				i;

	if (is_input_has_errors(argc, argv))
		return (1);
	args = init_args_struct(++argv);
	philo = init_philo_struct(args);
	if (!(ptr = malloc(sizeof(*ptr) * (args.number_of_philosophers + 1))))
		return (1);
	i = -1;
	while (++i < args.number_of_philosophers)
		if (pthread_create(&(ptr[i]), NULL, &philo_work, &(philo[i])) != 0)
			return (1);
	vars = init_vars_struct(args, philo, ptr);
	if (pthread_create(&(ptr[i]), NULL, &check_threads, vars) != 0)
		return (1);
	if (pthread_join(ptr[i], NULL) != 0)
		return (1);
	clean_all(philo, ptr);
	return (0);
}
