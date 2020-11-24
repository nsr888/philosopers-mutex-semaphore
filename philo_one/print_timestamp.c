/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_timestamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:11:34 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/20 13:29:39 by anasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long			get_current_time_in_ms(void)
{
	struct timeval	tv;
	long long		time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_mill);
}

int					get_timestamp(long long time_of_start)
{
	long long		time_in_ms;

	time_in_ms = get_current_time_in_ms();
	return ((int)(time_in_ms - time_of_start));
}

static int			is_can_print(t_philosophers *philo)
{
	if (philo->args.number_of_times_each_philosopher_must_eat != -1)
	{
		if (philo->shared->eat_count[philo->current_philo] >=
			philo->args.number_of_times_each_philosopher_must_eat)
		{
			return (0);
		}
	}
	return (1);
}

void				print_timestamp(char *s, int current_philo, int timestamp)
{
	char			*tmp2;
	char			*tmp0;
	char			*tmp1;

	tmp0 = ft_itoa(timestamp);
	tmp2 = ft_strjoin(tmp0, " ");
	free(tmp0);
	tmp1 = ft_itoa(current_philo + 1);
	tmp0 = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	free(tmp2);
	tmp2 = ft_strjoin(tmp0, s);
	free(tmp0);
	write(1, tmp2, ft_strlen(tmp2));
	free(tmp2);
}

int					print_timestamp_philo(char *s, t_philosophers *philo)
{
	int				timestamp;

	if (pthread_mutex_lock(&philo->mtx->mutex_write_lock))
		return (1);
	timestamp = 0;
	if (is_can_print(philo))
	{
		timestamp = get_timestamp(*philo->shared->time_of_start);
		print_timestamp(s, philo->current_philo, timestamp);
	}
	if (pthread_mutex_unlock(&philo->mtx->mutex_write_lock))
		return (1);
	return (0);
}
