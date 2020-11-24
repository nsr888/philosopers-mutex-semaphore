/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:39:06 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/20 21:03:16 by anasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			take_forks(t_philosophers *philo)
{
	if (sem_wait(philo->sem->steward) < 0)
		return (1);
	if (sem_wait(philo->sem->forks) < 0)
		return (1);
	if (print_timestamp_philo(" has taken a fork\n", philo))
		return (1);
	if (sem_wait(philo->sem->forks) < 0)
		return (1);
	if (print_timestamp_philo(" has taken a fork\n", philo))
		return (1);
	if (sem_post(philo->sem->steward) < 0)
		return (1);
	return (0);
}

static int			do_eating(t_philosophers *philo)
{
	if (take_forks(philo))
		return (1);
	philo->shared->timestamp_last_meal[philo->current_philo] =
		get_timestamp(*philo->shared->time_of_start);
	if (print_timestamp_philo(" is eating\n", philo))
		return (1);
	ft_usleep(philo->args.time_to_eat);
	if (sem_post(philo->sem->forks) < 0)
		return (1);
	if (sem_post(philo->sem->forks) < 0)
		return (1);
	if (philo->args.number_of_times_each_philosopher_must_eat != -1)
		philo->shared->eat_count[philo->current_philo] += 1;
	return (0);
}

static int			do_sleeping(t_philosophers *philo)
{
	if (print_timestamp_philo(" is sleeping\n", philo))
		return (1);
	ft_usleep(philo->args.time_to_sleep);
	if (print_timestamp_philo(" is thinking\n", philo))
		return (1);
	return (0);
}

void				*philo_work(void *ptr)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)ptr;
	while (!do_eating(philo) && !do_sleeping(philo))
		;
	while (1)
		;
	return (NULL);
}
