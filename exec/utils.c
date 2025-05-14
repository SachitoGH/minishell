/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:12:11 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:30:47 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

void	close_pipe(int *end)
{
	if (close(end[0]) == -1)
	{
		perror("close");
		exit(1);
	}
	if (close(end[1]) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		unlink("heredoc");
		exit(1);
	}
}

int	handle_redir(t_mini *shell, t_pipes *p, int i)
{
	if (shell->cmds[i].redir_in.invalid || shell->cmds[i].redir_out.invalid)
		return (1);
	if (shell->cmds[i].redir_in.doc)
		handle_heredoc(shell, p, i);
	if (shell->cmds[i].redir_in.file_name)
	{
		p->fd_in = open(shell->cmds[i].redir_in.file_name,
				shell->cmds[i].redir_in.flags);
		if (p->fd_in < 0)
		{
			perror(shell->cmds[i].redir_in.file_name);
			return (1);
		}
	}
	if (shell->cmds[i].redir_out.file_name)
	{
		p->fd_out = open(shell->cmds[i].redir_out.file_name,
				shell->cmds[i].redir_out.flags);
		if (p->fd_out < 0)
		{
			perror(shell->cmds[i].redir_out.file_name);
			return (1);
		}
	}
	return (0);
}

char	*ft_get_env(char *env[], char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(str, env[i], len))
			return (ft_substr(env[i], len, ft_strlen(env[i])));
		i++;
	}
	return (0);
}

char	*ft_cmd_path(char *cmd, char **env)
{
	int		i;
	char	**split_path;
	char	*cmd_path;
	char	*tmp;

	if (!access(cmd, F_OK) && !access(cmd, X_OK))
		return (cmd);
	split_path = ft_split(ft_get_env(env, "PATH="), ':');
	if (!split_path)
		return (cmd);
	tmp = ft_strjoin("/", cmd);
	i = 0;
	while (split_path[i])
	{
		cmd_path = ft_strjoin(split_path[i], tmp);
		if (!access(cmd_path, F_OK) && !access(cmd_path, X_OK))
		{
			free(tmp);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(tmp);
	return (cmd);
}
