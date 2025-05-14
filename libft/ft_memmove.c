/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:37:47 by lmajerus          #+#    #+#             */
/*   Updated: 2021/02/11 15:38:13 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dest || src)
	{
		d = dest;
		s = src;
		if (d == s)
			return (dest);
		if (d < s)
			while (n--)
				*d++ = *s++;
		else
			while (n--)
				d[n] = s[n];
	}
	return (dest);
}
