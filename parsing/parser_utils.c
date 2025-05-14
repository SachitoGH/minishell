/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:35:26 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:35:27 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	red(t_red *red, t_token *head, t_cmd c)
{
	int	fd;

	if (c.redir_in.invalid || c.redir_out.invalid)
		return (1);
	if (red->file_name)
		free(red->file_name);
	red->file_name = ft_strdup_2(head->next->data);
	if (!ft_strncmp_2(head->data, ">>", 2))
		red->flags = (O_CREAT | O_APPEND | O_RDWR);
	else if (!ft_strncmp_2(head->data, "<<", 2))
		return (red->file_name = NULL, ft_lstadd_back_2(&red->doc,
				ft_lstnew_2(ft_strdup_2(head->next->data))),
			red->flags = -1, 0);
	else if (!ft_strncmp_2(head->data, ">", 1))
		red->flags = (O_CREAT | O_TRUNC | O_RDWR);
	else if (!ft_strncmp_2(head->data, "<", 1))
		red->flags = O_RDONLY;
	fd = open(red->file_name, red->flags, 0644);
	if (fd == -1)
		return (perror(red->file_name), red->invalid = 1, 1);
	else
		close(fd);
	return (0);
}

int	free_cmds(t_cmd *cmds, int nb_cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_cmd)
	{
		j = 0;
		while (cmds[i].av[j])
			free(cmds[i].av[j++]);
		if (cmds[i].av)
			free(cmds[i].av);
		if (cmds[i].redir_in.file_name)
			free(cmds[i].redir_in.file_name);
		if (cmds[i].redir_out.file_name)
			free(cmds[i].redir_out.file_name);
		i++;
	}
	if (cmds)
	{
		free(cmds);
		cmds = NULL;
	}
	return (1);
}

int	free_tokens(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->data);
		(*head)->data = NULL;
		free(*head);
		*head = tmp;
	}
	return (0);
}
