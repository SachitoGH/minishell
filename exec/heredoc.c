/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssenas-y <ssenas-y@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:12:01 by ssenas-y          #+#    #+#             */
/*   Updated: 2024/06/10 22:30:33 by ssenas-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"

static int	process_heredoc(t_here *doc, int fd)
{
	char	*input;
	int		len;

	len = ft_strlen(doc->delimiter) + 1;
	while (1)
	{
		signal(SIGINT, signal_handler_heredoc);
		input = readline("<");
		if (!input)
		{
			close(fd);
			unlink("heredoc");
			exit(1);
		}
		if (!ft_strncmp(input, doc->delimiter, len))
		{
			free(input);
			close(fd);
			fd = open("heredoc", O_RDONLY, 0666);
			unlink("heredoc");
			return (fd);
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
}

int	handle_heredoc(t_mini *shell, t_pipes *p, int i)
{
	t_here	*tmp;
	int		hd_fd;
	int		fd;

	tmp = shell->cmds[i].redir_in.doc;
	while (tmp)
	{
		hd_fd = open("heredoc", O_CREAT | O_WRONLY, 0666);
		if (!shell->cmds[i].av[0])
		{
			fd = process_heredoc(tmp, hd_fd);
			close(fd);
		}
		else
			p->fd_in = process_heredoc(tmp, hd_fd);
		tmp = tmp->next;
	}
	if (!shell->cmds[i].av[0])
		exit(0);
	return (0);
}
