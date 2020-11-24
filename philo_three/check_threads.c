/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:45:05 by anasyrov          #+#    #+#             */
/*   Updated: 2020/11/24 13:18:02 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			is_time_to_die(t_vars *vars, int i)
{
	if (get_timestamp(*vars->philo.shared->time_of_start) -
			vars->philo.shared->timestamp_last_meal[i] >
			vars->philo.args.time_to_die)
	{
		return (1);
	}
	return (0);
}

static int			is_finished_eat(t_vars *vars, int current_philo)
{
	if (vars->philo.shared->eat_count[current_philo] >= \
			vars->philo.args.number_of_times_each_philosopher_must_eat)
	{
		return (1);
	}
	if (is_time_to_die(vars, vars->philo.current_philo))
	{
		sem_wait(vars->philo.sem->write_lock);
		print_timestamp(" is died\n", vars->philo.current_philo, \
				*vars->philo.shared->time_of_start);
		return (2);
	}
	return (0);
}

static int			check_die_loop(t_vars *vars)
{
	while (1)
	{
		if (is_time_to_die(vars, vars->philo.current_philo))
		{
			sem_wait(vars->philo.sem->write_lock);
			print_timestamp(" is died\n", vars->philo.current_philo, \
					*vars->philo.shared->time_of_start);
			break ;
		}
		usleep(10);
	}
	return (1);
}

/*
** if is passed number_of_times_each_philosopher_must_eat and
** philo died too soon, then ret == 2 and process exit with EXIT_FAILURE,
** otherwise exit with EXIT_SUCCESS
*/

static void			*check_threads(void *p)
{
	t_vars			*vars;
	int				ret;

	vars = (t_vars *)p;
	if (vars->philo.args.number_of_times_each_philosopher_must_eat == -1)
	{
		ret = check_die_loop(vars);
		pthread_detach(vars->ptr);
	}
	else
	{
		while (!(ret = is_finished_eat(vars, vars->philo.current_philo)))
			;
		pthread_detach(vars->ptr);
	}
	if (ret == 2)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
	return (NULL);
}

int					create_processes_and_threads(t_argv args, \
		t_philosophers *philo, int *child)
{
	int				i;
	t_vars			*vars;
	pthread_t		*ptr;

	if (!(ptr = malloc(sizeof(*ptr) * 2)))
		return (1);
	i = -1;
	while (++i < args.number_of_philosophers)
	{
		if ((child[i] = fork()) < 0)
			return (1);
		if (child[i] == 0)
		{
			if (pthread_create(&(ptr[0]), NULL, &philo_work, &(philo[i])) != 0)
				return (1);
			vars = init_vars_struct(ptr[0], philo[i]);
			if (pthread_create(&(ptr[1]), NULL, &check_threads, vars) != 0)
				return (1);
			if (pthread_join(ptr[1], NULL) != 0)
				return (1);
		}
	}
	free(ptr);
	return (0);
}
