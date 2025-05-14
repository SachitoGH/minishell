/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:35:03 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:35:04 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

t_here	*ft_lstnew_2(void *content)
{
	t_here	*new;

	new = malloc(sizeof(t_here));
	if (!new)
		exit(1);
	new->delimiter = content;
	new->next = NULL;
	return (new);
}

t_here	*ft_lstlast_2(t_here *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_2(t_here **lst, t_here *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_2(*lst)->next = new;
}

int	cmp(char *s1, char *s2, int n)
{
	if (!s1 || !s2)
		return (1);
	while (n--)
	{
		if (*s1 != *s2 && !*s2 && *s1 == '=')
			return (0);
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (!*s1)
			return (1);
		s1++;
		s2++;
	}
	return (1);
}

char	*ft_getenv(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_2(str);
	while (env[i])
	{
		if (!cmp(env[i], str, len + 1))
			return (ft_substr_2(env[i], len + 1,
					ft_strlen_2(env[i]) - (len + 1)));
		i++;
	}
	return (NULL);
}
