/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:45:05 by anasyrov          #+#    #+#             */
/*   Updated: 2020/11/24 13:11:33 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			print_timestamp_last_philo_died(t_vars *vars, int i)
{
	sem_wait(vars->sem->write_lock);
	*vars->shared->mute_messages = 1;
	print_timestamp(" is died\n", i, *vars->shared->time_of_start);
}

static int			is_time_to_die(t_vars *vars, int i)
{
	if (get_timestamp(*vars->shared->time_of_start) -
			vars->shared->timestamp_last_meal[i] >
			vars->args.time_to_die)
	{
		return (1);
	}
	return (0);
}

static int			is_all_finished_eat(t_vars *vars)
{
	int				finished_philo_count;
	int				i;

	finished_philo_count = 0;
	i = -1;
	while (++i < vars->args.number_of_philosophers)
	{
		if (is_time_to_die(vars, i))
		{
			print_timestamp_last_philo_died(vars, i);
			return (1);
		}
		if (vars->shared->eat_count[i] >= \
				vars->args.number_of_times_each_philosopher_must_eat)
			finished_philo_count++;
	}
	if (finished_philo_count >= vars->args.number_of_philosophers)
	{
		sem_wait(vars->sem->write_lock);
		*vars->shared->mute_messages = 1;
		return (1);
	}
	return (0);
}

static void			check_die_loop(t_vars *vars)
{
	int				i;

	i = 0;
	while (i < vars->args.number_of_philosophers)
	{
		if (is_time_to_die(vars, i))
		{
			print_timestamp_last_philo_died(vars, i);
			break ;
		}
		i++;
		if (i == vars->args.number_of_philosophers)
			i = 0;
	}
}

void				*check_threads(void *p)
{
	t_vars			*vars;
	int				i;

	vars = (t_vars *)p;
	if (vars->args.number_of_times_each_philosopher_must_eat == -1)
	{
		check_die_loop(vars);
		i = -1;
		while (++i < vars->args.number_of_philosophers)
			pthread_detach(vars->ptr[i]);
		destroy_semaphores(vars->sem, vars->args.number_of_philosophers);
	}
	else
	{
		while (!is_all_finished_eat(vars))
			;
		i = -1;
		while (++i < vars->args.number_of_philosophers)
			pthread_detach(vars->ptr[i]);
		destroy_semaphores(vars->sem, vars->args.number_of_philosophers);
	}
	return (NULL);
}
