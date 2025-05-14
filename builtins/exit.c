/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:10:54 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/11 00:37:53 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

static int	ft_str_isnum(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9' || s[i] == '\'' || s[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_mini *shell, int i)
{
	write(1, "exit\n", 5);
	if (i != -1 && shell->cmds[i].av[1] && shell->cmds[i].av[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_es = 1;
	}
	else if (i != -1 && shell->cmds[i].av[1])
	{
		if (ft_str_isnum(shell->cmds[i].av[1]))
			g_es = ft_atoi(shell->cmds[i].av[1]);
		else
		{
			write(2, "minishell: exit: ", 17);
			ft_putstr_fd(shell->cmds[i].av[1], 2);
			write(2, ": numeric argument required\n", 28);
			g_es = 255;
		}
	}
	else
		g_es = 0;
	if (shell->nb_cmd > 0)
		free_cmds(shell->cmds, shell->nb_cmd);
	free_env(shell->env);
	exit(g_es);
}
