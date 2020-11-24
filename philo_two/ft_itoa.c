/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 11:54:28 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/17 21:50:33 by anasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	count_size(int n, int sign)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	len = len + sign;
	return (len);
}

static void	fill_ret(char *ret, int n, int len, int sign)
{
	while (n > 9)
	{
		ret[len] = (char)(n % 10) + '0';
		n = n / 10;
		len--;
	}
	ret[len] = (char)n + '0';
	if (sign)
		ret[--len] = '-';
}

char		*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*ret;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -1 * n;
	}
	len = count_size(n, sign);
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	len--;
	fill_ret(ret, n, len, sign);
	return (ret);
}
