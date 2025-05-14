/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:10:14 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:29:57 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

static int	ft_check_n(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_echo_process(char **cmd, int i, int j, int pfd)
{
	while (cmd[i][j])
	{
		if (cmd[i][j] == '\\' && cmd[i][j + 1] == '\\'
			&& cmd[i][j + 2] == 'n')
		{
			write(pfd, "\n", 1);
			j += 2;
		}
		else
			write(pfd, &cmd[i][j], 1);
		j++;
	}
	if (cmd[i + 1])
		write(pfd, " ", 1);
}

int	ft_echo(char **cmd, int pfd)
{
	int	i;
	int	j;
	int	n;

	if (!cmd[1])
	{
		write(pfd, "\n", 1);
		return (0);
	}
	n = 0;
	while (ft_check_n(cmd[n + 1]))
		n++;
	i = 1 + n;
	while (cmd[i])
	{
		j = 0;
		ft_echo_process(cmd, i, j, pfd);
		i++;
	}
	if (!n)
		write(pfd, "\n", 1);
	return (0);
}
