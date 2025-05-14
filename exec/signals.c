/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:28:55 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:28:56 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

void	signal_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_es = 1;
	}
	if (signum == SIGQUIT)
	{
		ioctl(0, TIOCNOTTY);
		write(1, "Quit: 3\n", 8);
	}
}
