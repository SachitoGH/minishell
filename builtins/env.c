/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:10:24 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:30:06 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	ft_env(char **env, char **cmd, int pfd)
{
	int	i;

	if (cmd[1])
	{
		write(2, "minishell: env: too many arguments\n", 35);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], pfd);
		i++;
	}
	return (0);
}
