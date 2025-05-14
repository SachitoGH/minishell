/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmajerus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:25:12 by lmajerus          #+#    #+#             */
/*   Updated: 2021/02/11 15:25:29 by lmajerus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	if (!lst || !(*del))
		return ;
	current = *lst;
	while (current)
	{
		(*del)(current->content);
		current = current->next;
		free(*lst);
		*lst = current;
	}
	lst = NULL;
}
