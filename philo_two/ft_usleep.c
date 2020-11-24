/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasyrov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:30:16 by anasyrov          #+#    #+#             */
/*   Updated: 2020/11/24 09:03:10 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				ft_usleep(int ms)
{
	long long		start_time;
	long long		end_time;
	int				elapsed_time;

	start_time = get_current_time_in_ms();
	end_time = get_current_time_in_ms();
	elapsed_time = end_time - start_time;
	while (elapsed_time < ms)
	{
		usleep(10);
		end_time = get_current_time_in_ms();
		elapsed_time = end_time - start_time;
	}
}
