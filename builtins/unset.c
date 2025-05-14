/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:11:19 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:30:19 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	ft_unset(char ***env, char **cmd)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (cmd[++i])
	{
		len = ft_strlen(cmd[i]);
		j = -1;
		while ((*env)[++j])
		{
			if (ft_strlen((*env)[j]) >= len && (*env)[j][len] == '='
			&& !ft_strncmp(cmd[i], (*env)[j], len))
			{
				free((*env)[j]);
				while ((*env)[j + 1])
				{
					(*env)[j] = (*env)[j + 1];
					j++;
				}
				(*env)[j] = NULL;
			}
		}
	}
	return (0);
}
