/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomajeru <lomajeru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:29:41 by lmajerus          #+#    #+#             */
/*   Updated: 2023/10/18 22:25:51 by lomajeru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*new;
	void	*f_content;

	if (!f || !del)
		return (NULL);
	begin = NULL;
	while (lst)
	{
		f_content = f(lst->content);
		new = ft_lstnew(f_content);
		if (!new)
		{
			del(f_content);
			ft_lstclear(&begin, (*del));
			return (NULL);
		}
		ft_lstadd_back(&begin, new);
		lst = lst->next;
	}
	return (begin);
}
