/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomajeru <lomajeru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:59:03 by lmajerus          #+#    #+#             */
/*   Updated: 2023/10/18 21:43:22 by lomajeru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		needle_len;

	if (!*needle)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	needle_len = ft_strlen(needle);
	while (*haystack && len)
	{
		if (*haystack == *needle && len >= needle_len)
			if (!ft_strncmp(haystack, needle, needle_len))
				return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
