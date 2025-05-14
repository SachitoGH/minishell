/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:11:37 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/11 00:36:03 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	ft_isbuiltin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		||!ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

void	exec_solo(t_mini *shell, t_pipes *p, int i)
{
	p->fd_out = 1;
	if (handle_redir(shell, p, i))
		g_es = 1;
	else
		g_es = ft_exec_builtin(shell, i, p->fd_out, 1);
	if (p->fd_out != 1)
		close(p->fd_out);
}

int	ft_exec_builtin(t_mini *shell, int i, int pfd, int solo)
{
	if (!solo)
		pfd = 1;
	if (!ft_strncmp(shell->cmds[i].av[0], "echo", 5))
		return (ft_echo(shell->cmds[i].av, pfd));
	if (!ft_strncmp(shell->cmds[i].av[0], "cd", 3))
		return (ft_cd(shell->cmds[i].av, shell->env));
	if (!ft_strncmp(shell->cmds[i].av[0], "pwd", 4))
		return (ft_pwd(pfd));
	if (!ft_strncmp(shell->cmds[i].av[0], "export", 7))
		return (ft_export(&shell->env, shell->cmds[i].av));
	if (!ft_strncmp(shell->cmds[i].av[0], "unset", 6))
		return (ft_unset(&shell->env, shell->cmds[i].av));
	if (!ft_strncmp(shell->cmds[i].av[0], "env", 4))
		return (ft_env(shell->env, shell->cmds[i].av, pfd));
	if (!ft_strncmp(shell->cmds[i].av[0], "exit", 5))
		ft_exit(shell, i);
	return (0);
}
