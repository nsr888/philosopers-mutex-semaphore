/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:39:06 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/24 09:06:06 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			lock_forks_mutex(t_philosophers *philo, t_forks *forks)
{
	if (philo->current_philo % 2)
	{
		if (pthread_mutex_lock(&(philo->mtx->forks[forks->left])))
			return (1);
		print_timestamp_philo(" has taken a fork\n", philo);
		if (pthread_mutex_lock(&(philo->mtx->forks[forks->right])))
			return (1);
		print_timestamp_philo(" has taken a fork\n", philo);
	}
	else
	{
		if (pthread_mutex_lock(&(philo->mtx->forks[forks->right])))
			return (1);
		print_timestamp_philo(" has taken a fork\n", philo);
		if (pthread_mutex_lock(&(philo->mtx->forks[forks->left])))
			return (1);
		print_timestamp_philo(" has taken a fork\n", philo);
	}
	return (0);
}

static int			unlock_forks_mutex(t_philosophers *philo, t_forks *forks)
{
	if ((philo->current_philo % 2))
	{
		if (pthread_mutex_unlock(&(philo->mtx->forks[forks->right])))
			return (1);
		if (pthread_mutex_unlock(&(philo->mtx->forks[forks->left])))
			return (1);
	}
	else
	{
		if (pthread_mutex_unlock(&(philo->mtx->forks[forks->left])))
			return (1);
		if (pthread_mutex_unlock(&(philo->mtx->forks[forks->right])))
			return (1);
	}
	return (0);
}

static int			do_eating(t_philosophers *philo)
{
	t_forks			forks;

	forks.left = philo->current_philo;
	forks.right = (forks.left + 1 == philo->args.number_of_philosophers) ?\
		0 : forks.left + 1;
	if (lock_forks_mutex(philo, &forks))
		return (1);
	philo->shared->timestamp_last_meal[philo->current_philo] =
		get_timestamp(*philo->shared->time_of_start);
	if (print_timestamp_philo(" is eating\n", philo))
		return (1);
	ft_usleep(philo->args.time_to_eat);
	if (unlock_forks_mutex(philo, &forks))
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
