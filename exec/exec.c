/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:11:49 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:30:29 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

static void	handle_dup(t_mini *shell, t_pipes *p, int i)
{
	if (p->fd_out != 1)
		dup2(p->fd_out, 1);
	if (p->fd_in != 0)
		dup2(p->fd_in, 0);
	if (i > 0)
	{
		dup2(p->old_fd[0], p->fd_in);
		close_pipe(p->old_fd);
	}
	if (i < shell->nb_cmd - 1)
	{
		dup2(p->fd[1], p->fd_out);
		close_pipe(p->fd);
	}
}

static int	exec(t_mini *shell, int i, t_pipes *p)
{
	char	*cmd_path;

	p->fd_in = 0;
	p->fd_out = 1;
	if (handle_redir(shell, p, i))
		return (1);
	handle_dup(shell, p, i);
	if (ft_isbuiltin(shell->cmds[i].av[0]))
		return (ft_exec_builtin(shell, i, p->fd_out, 0));
	cmd_path = ft_cmd_path(shell->cmds[i].av[0], shell->env);
	execve(cmd_path, shell->cmds[i].av, shell->env);
	if (errno == 20)
	{
		perror(cmd_path);
		return (126);
	}
	if (cmd_path[0] != '/')
	{
		write(2, cmd_path, ft_strlen(cmd_path));
		write(2, ": command not found\n", 20);
	}
	else
		perror(cmd_path);
	return (127);
}

static void	handle_process(t_mini *shell, pid_t *pids, t_pipes *p, int i)
{
	if (pids[i] == 0)
	{
		signal(SIGINT, signal_handler);
		exit(exec(shell, i, p));
	}
	else
	{
		signal(SIGINT, signal_handler_parent);
		if (i > 0)
			close_pipe(p->old_fd);
		if (i < shell->nb_cmd - 1)
		{
			p->old_fd[0] = p->fd[0];
			p->old_fd[1] = p->fd[1];
		}
	}
}

int	wait_pids(pid_t *pids, int nb_pids)
{
	int	status;
	int	i;

	i = 0;
	while (i < nb_pids)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			g_es = WEXITSTATUS(status);
		i++;
	}
	free(pids);
	return (0);
}

void	ft_exec_cmd(t_mini *shell, int i, pid_t *pids)
{
	t_pipes	p;

	pids = malloc(sizeof(pid_t) * shell->nb_cmd);
	if (!pids)
		return (ft_putstr_fd("malloc error\n", 2), ft_exit(shell, -1));
	if (shell->nb_cmd == 1 && ft_isbuiltin(shell->cmds[0].av[0]))
		return (exec_solo(shell, &p, 0));
	while (++i < shell->nb_cmd)
	{
		signal(SIGQUIT, signal_handler);
		if (i < shell->nb_cmd - 1 && pipe(p.fd) == -1)
		{
			perror("pipe");
			ft_exit(shell, -1);
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			ft_exit(shell, -1);
		}
		handle_process(shell, pids, &p, i);
	}
	wait_pids(pids, shell->nb_cmd);
}
