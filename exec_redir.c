/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:07:01 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/28 19:22:59 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_file(t_redir *redir)
{
	int fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open(redir->name, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		return (-1);
	}
	if (redir->type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	return (0);
}

void heredoc(t_redir *redir)
{
	char *line;
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return ; //!!!make return error!!!
	pid = fork();
	if (pid < 0)
		return ; //!!!make return error!!!
	if (pid == 0)
	{
		close(fd[0]);
		//dup2(fd[1], STDOUT_FILENO);
		while (1)
		{
			write(1, "heredoc> ", 9);
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, redir->name, ft_strlen(line) - 1) == 0)
			{
				free(line);
				close(fd[1]);
				exit(EXIT_SUCCESS);
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	waitpid(pid, NULL, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void execute_redirect(t_table_cmd *table)
{
	t_redir *redir_file;

	redir_file = table->redirections;
	while (redir_file != NULL)
	{
		if (redir_file->type == 4)
		{
			heredoc(redir_file);
		}
		else
		{
			if (open_file(redir_file) == -1)
			{
				return ;
			}
		}
		redir_file = redir_file->next;
	}
}
