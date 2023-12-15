/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:28:19 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/15 13:37:09 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipe(t_info *info)
{
	if (info->cnt != 1)
	{
		if (pipe(info->pipe_fds[info->cur]) == -1)
			perror_exit("pipe()", 1);
	}
}

void	close_pipe(t_info *info)
{
	int	i;

	i = -1;
	if (info->idx == 0)
		close(info->pipe_fds[info->cur][0]);
	else if (info->idx == info->cnt - 1)
		close(info->pipe_fds[!info->cur][1]);
	else
	{
		close(info->pipe_fds[!info->cur][1]);
		close(info->pipe_fds[info->cur][0]);
	}
}

void	open_file(t_info *info)
{
	if (info->data->infile != NULL)
	{
		info->infile_fd = open(info->data->infile, O_RDONLY);
		if (info->infile_fd == -1)
			perror_exit(ft_strjoin("minishell: ", info->data->infile), 1);
	}
	if (info->data->outfile != NULL)
	{
		if (info->data->is_append == 1)
			info->outfile_fd = open(info->data->outfile,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			info->outfile_fd = open(info->data->outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (info->outfile_fd == -1)
			perror_exit(ft_strjoin("minishell: ", info->data->outfile), 1);
	}
}

void	close_all_pipe(t_info *info)
{
	close(info->pipe_fds[0][0]);
	close(info->pipe_fds[0][1]);
	close(info->pipe_fds[1][0]);
	close(info->pipe_fds[1][1]);
}

void	redirect(t_info *info)
{
	if (info->idx == 0 && info->cnt != 1)
		dup2(info->pipe_fds[info->cur][1], STDOUT_FILENO);
	else if (info->idx == info->cnt - 1 && info->cnt != 1)
		dup2(info->pipe_fds[!info->cur][0], STDIN_FILENO);
	else if (info->cnt != 1)
	{
		dup2(info->pipe_fds[!info->cur][0], STDIN_FILENO);
		dup2(info->pipe_fds[info->cur][1], STDOUT_FILENO);
	}
	if (info->data->infile != NULL)
		dup2(info->infile_fd, STDIN_FILENO);
	if (info->data->outfile != NULL)
		dup2(info->outfile_fd, STDOUT_FILENO);
}
