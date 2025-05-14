/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomajeru <lomajeru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:12:27 by lmajerus          #+#    #+#             */
/*   Updated: 2023/11/02 13:06:28 by lomajeru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	ans;
	unsigned long	cutoff;

	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (sign < 0)
		cutoff = (unsigned long)-(LONG_MIN + LONG_MAX) + LONG_MAX;
	else
		cutoff = LONG_MAX;
	ans = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ans > cutoff / 10 || (ans == cutoff / 10
				&& (unsigned long)str[i] - 48 > cutoff % 10))
			return (cutoff);
		ans = ans * 10 + (str[i++] - '0');
	}
	return (ans * sign);
}
