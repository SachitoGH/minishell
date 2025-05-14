/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomajeru <lomajeru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:16:51 by lmajerus          #+#    #+#             */
/*   Updated: 2023/10/18 22:47:16 by lomajeru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*calloc;

	calloc = malloc(nmemb * size);
	if (!calloc)
		return (NULL);
	ft_bzero(calloc, nmemb * size);
	return (calloc);
}
