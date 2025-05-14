/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:28:45 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:37:08 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

size_t	ft_env_count(char **env)
{
	size_t	count;

	count = 0;
	while (env[count])
		count++;
	return (count + 1);
}

char	**env_dup(char **env)
{
	int		i;
	char	**cpy;

	i = ft_env_count(env);
	cpy = malloc(i * sizeof(char *));
	if (!cpy)
		exit(1);
	i = 0;
	while (env[i])
	{
		cpy[i] = env[i];
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

int	print_cpy(char **cpy)
{
	int	i;

	i = 0;
	while (cpy[i])
	{
		write(1, "declare -x ", 11);
		ft_putendl_fd(cpy[i], 1);
		i++;
	}
	return (0);
}

int	ft_switch(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
	return (0);
}
