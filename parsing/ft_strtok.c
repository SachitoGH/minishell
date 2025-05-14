/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:35:31 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:35:32 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

static char	*remove_unwanted_quotes(char *str, int i, int j)
{
	char	*tmp;
	char	quotes;

	tmp = malloc(sizeof(char) * ft_strlen_2(str) + 1);
	if (!tmp)
		exit(1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quotes = str[i];
			i++;
			while (str[i] && str[i] != quotes)
				tmp[j++] = str[i++];
			i++;
		}
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	str = ft_substr_2(tmp, 0, ft_strlen_2(tmp));
	free(tmp);
	return (str);
}

static int	check_syntax(t_token *token)
{
	if (!token->next && (token->type == PIPE
			|| token->type == RED_OUT || token->type == RED_IN))
		return (0);
	if ((token->type == RED_IN || token->type == RED_OUT)
		&& token->next && token->next->type != OTHER)
		return (0);
	if (token->type == PIPE && token->next && token->next->type == PIPE)
		return (0);
	return (1);
}

static int	trim_tokens(t_token *head)
{
	if (head && head->type == PIPE)
		return (0);
	while (head)
	{
		if (!check_syntax(head))
			return (0);
		head->data = remove_unwanted_quotes(head->data, 0, 0);
		head = head->next;
	}
	return (1);
}

static int	identify_type(char *str, t_token *tmp)
{
	if (!ft_strncmp_2(str, "|", 1))
		return (tmp->type_size = 1, PIPE);
	if (!ft_strncmp_2(str, ">>", 2))
		return (tmp->type_size = 2, RED_OUT);
	if (!ft_strncmp_2(str, ">", 1))
		return (tmp->type_size = 1, RED_OUT);
	if (!ft_strncmp_2(str, "<<", 2))
		return (tmp->type_size = 2, RED_IN);
	if (!ft_strncmp_2(str, "<", 1))
		return (tmp->type_size = 1, RED_IN);
	if (!ft_strncmp_2(str, "\t", 1))
		return (tmp->type_size = 1, 4);
	if (!ft_strncmp_2(str, "\n", 1))
		return (tmp->type_size = 1, 4);
	if (!ft_strncmp_2(str, "\r", 1))
		return (tmp->type_size = 1, 4);
	if (!ft_strncmp_2(str, "\v", 1))
		return (tmp->type_size = 1, 4);
	if (!ft_strncmp_2(str, "\f", 1))
		return (tmp->type_size = 1, 4);
	if (!ft_strncmp_2(str, " ", 1))
		return (tmp->type_size = 1, 4);
	return (tmp->type_size = 0, OTHER);
}

int	ft_strtok(char *str, t_token **head, t_mini *shell)
{
	char	*tmp;
	t_token	tmp_token;

	tmp = str;
	while (str && *str)
	{
		tmp_token.type = identify_type(str, &tmp_token);
		if (tmp_token.type && tmp != str)
			token_add_back(head, create_token(tmp_token, tmp, str - tmp, 1));
		if (tmp_token.type)
		{
			if (tmp_token.type != 4)
				token_add_back(head,
					create_token(tmp_token, str, tmp_token.type_size, 0));
			str += tmp_token.type_size;
			tmp = str;
		}
		else if ((*str == '\"' || *str == '\'') && !find_next_quotes(&str))
			return (0);
		else
			str++;
	}
	if (tmp != str)
		token_add_back(head, create_token(tmp_token, tmp, str - tmp, 1));
	return (check_env_var(*head, shell, 0) && trim_tokens(*head));
}
