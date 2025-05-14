/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:10:01 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/11 14:13:29 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	update_pwd(char **env, char *pwd)
{
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], pwd, 4))
		{
			free(env[i]);
			env[i] = ft_strjoin(pwd, getcwd(cwd, sizeof(cwd)));
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_cd(char **cmd, char **env)
{
	char	*path;

	if (!cmd[1])
		path = ft_get_env(env, "HOME=");
	else if (!ft_strncmp("-", cmd[1], 2))
		path = ft_get_env(env, "OLDPWD=");
	else if (cmd[1][0] == '~')
		path = ft_strjoin(ft_get_env(env, "HOME="), &cmd[1][1]);
	else
		path = cmd[1];
	update_pwd(env, "OLDPWD=");
	if (chdir(path) != 0)
	{
		perror(path);
		return (1);
	}
	update_pwd(env, "PWD=");
	free(path);
	return (0);
}
