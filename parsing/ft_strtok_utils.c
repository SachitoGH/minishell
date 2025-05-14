/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:35:37 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:35:38 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	find_next_quotes(char **str)
{
	char	quotes;

	quotes = **str;
	(*str)++;
	while (**str)
	{
		if (**str == quotes)
			return (1);
		(*str)++;
	}
	return (0);
}

t_token	*last_token(t_token *head)
{
	while (head)
	{
		if (!head->next)
			return (head);
		head = head->next;
	}
	return (head);
}

void	token_add_back(t_token **head, t_token *new)
{
	if (!*head)
		*head = new;
	else
		last_token(*head)->next = new;
}

t_token	*create_token(t_token tmp, char *str, int size, int x)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit(1);
	new->data = ft_substr_2(str, 0, size);
	new->data_size = size;
	if (!x)
		new->type = tmp.type;
	else
		new->type = OTHER;
	new->type_size = tmp.type_size;
	new->next = NULL;
	return (new);
}
