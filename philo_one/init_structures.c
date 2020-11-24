/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:45:45 by anasyrov          #+#    #+#             */
/*   Updated: 2020/11/20 13:29:22 by anasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t		*init_forks(int number_of_philosophers)
{
	pthread_mutex_t *forks;
	int				i;

	if (!(forks = malloc(sizeof(*forks) * number_of_philosophers)))
		return (NULL);
	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

t_mtx				*init_mtx_struct(int number_of_philosophers)
{
	t_mtx			*mtx;

	if (!(mtx = malloc(sizeof(*mtx))))
		return (NULL);
	if (pthread_mutex_init(&mtx->mutex_write_lock, NULL))
		return (NULL);
	if (!(mtx->forks = init_forks(number_of_philosophers)))
		return (NULL);
	return (mtx);
}

t_argv				init_args_struct(char **argv)
{
	t_argv			args;

	args.number_of_philosophers = ft_atoi(argv[0]);
	args.time_to_die = ft_atoi(argv[1]);
	args.time_to_eat = ft_atoi(argv[2]);
	args.time_to_sleep = ft_atoi(argv[3]);
	args.number_of_times_each_philosopher_must_eat = (argv[4] != NULL) ?\
		ft_atoi(argv[4]) : -1;
	return (args);
}

t_shared			*init_shared_struct(int number_of_philosophers)
{
	t_shared		*shared;

	if (!(shared = ft_calloc(1, sizeof(*shared))))
		return (NULL);
	if (!(shared->time_of_start = ft_calloc(1, sizeof(*shared->time_of_start))))
		return (NULL);
	*shared->time_of_start = get_current_time_in_ms();
	if (!(shared->eat_count =
				ft_calloc(number_of_philosophers, sizeof(*shared->eat_count))))
		return (NULL);
	if (!(shared->timestamp_last_meal = ft_calloc(number_of_philosophers,
					sizeof(*shared->timestamp_last_meal))))
		return (NULL);
	return (shared);
}

t_philosophers		*init_philo_struct(t_argv args)
{
	t_philosophers	*philo;
	t_mtx			*mtx;
	t_shared		*shared;
	int				i;

	if (!(philo = malloc(sizeof(*philo) * args.number_of_philosophers)))
		return (NULL);
	if (!(mtx = init_mtx_struct(args.number_of_philosophers)))
		return (NULL);
	if (!(shared = init_shared_struct(args.number_of_philosophers)))
		return (NULL);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		philo[i].current_philo = i;
		philo[i].number_of_times_current_philosopher_eat = 0;
		philo[i].args = args;
		philo[i].mtx = mtx;
		philo[i].shared = shared;
		i++;
	}
	return (philo);
}
