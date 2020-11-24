/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:45:05 by anasyrov          #+#    #+#             */
/*   Updated: 2020/11/24 10:28:39 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			is_time_to_die(t_vars *vars, int i)
{
	int				timestamp_current;
	int				timestamp_last_meal;

	timestamp_current = get_timestamp(*vars->shared->time_of_start);
	timestamp_last_meal = vars->shared->timestamp_last_meal[i];
	if (timestamp_current - timestamp_last_meal > vars->args.time_to_die)
		return (1);
	return (0);
}

static void			print_last_philo_died(t_vars *vars, int i)
{
	int				timestamp_current;

	pthread_mutex_lock(&vars->mtx->mutex_write_lock);
	timestamp_current = get_timestamp(*vars->shared->time_of_start);
	print_timestamp(" is died\n", i, timestamp_current);
}

static int			is_all_finished_eat(t_vars *vars)
{
	int				finished_philo_count;
	int				i;

	finished_philo_count = 0;
	i = 0;
	while (i < vars->args.number_of_philosophers)
	{
		if (is_time_to_die(vars, i))
		{
			print_last_philo_died(vars, i);
			return (1);
		}
		if (vars->shared->eat_count[i++] >= \
				vars->args.number_of_times_each_philosopher_must_eat)
		{
			finished_philo_count++;
		}
	}
	if (finished_philo_count == vars->args.number_of_philosophers)
		return (1);
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
			print_last_philo_died(vars, i);
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
		i = 0;
		while (i < vars->args.number_of_philosophers)
			pthread_detach(vars->ptr[i++]);
	}
	else
	{
		while (!is_all_finished_eat(vars))
			;
		i = 0;
		while (i < vars->args.number_of_philosophers)
			pthread_detach(vars->ptr[i++]);
	}
	return (NULL);
}
