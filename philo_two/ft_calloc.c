/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:00:15 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/17 21:37:41 by anasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, int n)
{
	char	*str;
	int		i;

	str = s;
	i = -1;
	while (++i < n)
		str[i] = '\0';
}

void	*ft_calloc(size_t count, int size)
{
	void	*ret;

	ret = (void *)malloc(count * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}
