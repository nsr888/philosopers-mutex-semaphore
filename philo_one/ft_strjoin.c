/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <ksinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 10:06:16 by ksinistr          #+#    #+#             */
/*   Updated: 2020/11/10 17:21:39 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t			ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

static void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (dst == NULL && src == NULL)
		return (d);
	i = -1;
	while (++i < n)
	{
		d[i] = s[i];
	}
	return (d);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		dst_len;
	size_t		src_len;
	size_t		result_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len < dstsize)
		result_len = dst_len + src_len;
	else
		return (dstsize + src_len);
	if (src_len + dst_len < dstsize)
	{
		dst[dst_len + src_len] = '\0';
		ft_memcpy(&dst[dst_len], src, src_len);
	}
	else
	{
		dst[dstsize - 1] = '\0';
		ft_memcpy(&dst[dst_len], src, dstsize - dst_len - 1);
	}
	return (result_len);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*ret;
	int			ret_len;

	if (!s1 || !s2)
		return (NULL);
	ret_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)malloc(ret_len * sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	ft_strlcat(ret, s1, ret_len);
	ft_strlcat(ret, s2, ret_len);
	return (ret);
}
