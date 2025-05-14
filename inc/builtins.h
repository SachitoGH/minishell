/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:13:10 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:30:55 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <signal.h>
# include "minishell.h"
# include "exec.h"

int		ft_pwd(int pfd);
int		ft_cd(char **cmd, char **env);
int		ft_echo(char **cmd, int pfd);
int		ft_unset(char ***env, char **cmd);
int		ft_export(char ***env, char **cmd);
int		ft_env(char **env, char **cmd, int pfd);
void	ft_exit(t_mini *shell, int i);

//utils
int		print_cpy(char **cpy);
char	**env_dup(char **env);
int		ft_switch(char **s1, char **s2);
size_t	ft_env_count(char **env);

#endif
