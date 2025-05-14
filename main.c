/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:34:35 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:34:36 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	g_es = 0;

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	return ;
}

static char	**malloc_envp(char **envp, int i)
{
	char	**new;

	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		exit(1);
	new[i] = NULL;
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup_2(envp[i]);
		if (!new[i])
		{
			while (i--)
				free(new[i]);
			free(new);
			return (NULL);
		}
		i++;
	}
	return (new);
}

static void	shell_loop(t_mini *shell, char **input)
{
	while (1)
	{
		shell->nb_cmd = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		*input = readline("Minishell 🐚$ ");
		if (!*input)
			ft_exit(shell, -1);
		if (!**input)
			continue ;
		add_history(*input);
		*input = ft_strtrim_2(*input, " ");
		shell->nb_cmd = 0;
		shell->cmds = NULL;
		if (parser(shell, input))
			continue ;
		if (*input && ft_strncmp(*input, "", 2))
		{
			free(*input);
			ft_exec_cmd(shell, -1, 0);
			*input = NULL;
		}
	}
	if (shell->nb_cmd > 0)
		free_cmds(shell->cmds, shell->nb_cmd);
}

int	main(int argc, char **argv, char *envp[])
{
	t_mini	shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell = (t_mini){0};
	input = NULL;
	g_es = 0;
	shell.env = malloc_envp(envp, 0);
	shell_loop(&shell, &input);
	return (0);
}
