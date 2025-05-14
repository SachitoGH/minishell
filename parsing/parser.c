/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:35:18 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:35:19 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	get_nb_cmd(t_token *head)
{
	int	nb;

	nb = 1;
	while (head)
	{
		if (head->type == PIPE)
			nb++;
		head = head->next;
	}
	return (nb);
}

static void	fill_ac(t_mini *shell, t_token *head)
{
	int		i;
	t_token	*prev;

	i = 0;
	while (i < shell->nb_cmd)
	{
		prev = head;
		shell->cmds[i].ac = 0;
		while (head && head->type != PIPE)
		{
			if (head->type == OTHER && prev->type != RED_IN
				&& prev->type != RED_OUT)
				shell->cmds[i].ac++;
			prev = head;
			head = head->next;
		}
		if (head)
			head = head->next;
		i++;
	}
}

static void	set_names_to_null(t_mini *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_cmd)
	{
		shell->cmds[i].redir_in.file_name = NULL;
		shell->cmds[i].redir_out.file_name = NULL;
		shell->cmds[i].redir_out.flags = 0;
		shell->cmds[i].redir_in.flags = 0;
		shell->cmds[i].redir_in.doc = NULL;
		shell->cmds[i].redir_in.invalid = 0;
		shell->cmds[i].redir_out.invalid = 0;
		i++;
	}
}

static int	create_tab_cmd(t_token *head, t_cmd *c, int i, int j)
{
	while (head)
	{
		c[i].av = malloc(sizeof(char *) * (c[i].ac + 1));
		if (!c[i].av)
			exit(1);
		j = 0;
		c[i].av[c[i].ac] = NULL;
		while (head && head->type != PIPE)
		{
			if (head->type == OTHER)
				c[i].av[j++] = ft_strdup_2(head->data);
			else if (head->type == RED_IN && red(&c[i].redir_in, head, c[i]))
				;
			else if (head->type == RED_OUT && red(&c[i].redir_out, head, c[i]))
				;
			if (head->type == RED_IN || head->type == RED_OUT)
				head = head->next;
			if (head)
				head = head->next;
		}
		if (head)
			head = head->next;
		i++;
	}
	return (0);
}

int	parser(t_mini *shell, char **input)
{
	t_token		*head;

	head = NULL;
	if (!ft_strtok(*input, &head, shell))
		return (ft_error("Syntax error\n", 0));
	shell->nb_cmd = get_nb_cmd(head);
	shell->cmds = malloc(sizeof(t_cmd) * shell->nb_cmd);
	if (!shell->cmds)
		return (0);
	fill_ac(shell, head);
	set_names_to_null(shell);
	create_tab_cmd(head, shell->cmds, 0, 0);
	return (free_tokens(&head));
}
