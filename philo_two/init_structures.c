/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:45:45 by anasyrov          #+#    #+#             */
/*   Updated: 2020/11/24 12:51:02 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_sem				*init_sem_struct(int number_of_philosophers)
{
	t_sem			*sem;

	if (!(sem = malloc(sizeof(*sem))))
		return (NULL);
	sem->forks = sem_open("/mysem", O_CREAT | O_EXCL, 0644, \
			number_of_philosophers);
	if (sem->forks == SEM_FAILED)
		return (NULL);
	sem_unlink("/mysem");
	sem->write_lock = sem_open("/mysem_write_lock", O_CREAT | O_EXCL, 0644, 1);
	if (sem->write_lock == SEM_FAILED)
		return (NULL);
	sem_unlink("/mysem_write_lock");
	sem->steward = sem_open("/mysem_steward", O_CREAT | O_EXCL, 0644, 1);
	if (sem->steward == SEM_FAILED)
		return (NULL);
	sem_unlink("/mysem_steward");
	return (sem);
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
	if (!(shared->mute_messages = ft_calloc(1, sizeof(*shared->mute_messages))))
		return (NULL);
	*shared->mute_messages = 0;
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
	t_sem			*sem;
	t_shared		*shared;
	int				i;

	if (!(philo = malloc(sizeof(*philo) * args.number_of_philosophers)))
		return (NULL);
	if (!(sem = init_sem_struct(args.number_of_philosophers)))
		return (NULL);
	if (!(shared = init_shared_struct(args.number_of_philosophers)))
		return (NULL);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		philo[i].current_philo = i;
		philo[i].number_of_times_current_philosopher_eat = 0;
		philo[i].args = args;
		philo[i].sem = sem;
		philo[i].shared = shared;
		i++;
	}
	return (philo);
}
