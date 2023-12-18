/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:25:31 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/18 15:54:40 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(t_info *info, t_container *con)
{
	int	i;

	i = 0;
	info->data = con->head;
	info->cnt = con->cnt;
	info->envp = con->envp;
	info->idx = -1;
	info->cur = 0;
	while (i < 2)
	{
		info->pipe_fds[i][i] = -1;
		info->pipe_fds[i][(i + 1) % 2] = -1;
		i++;
	}
}

int	wait_children(t_info *info, t_data *head)
{
	int	i;
	int	wstatus;
	int	exit_code;
	int	result;

	i = 0;
	exit_code = 0;
	while (1)
	{
		result = wait(&wstatus);
		if (result == -1)
			break ;
		if (result == info->last_pid)
		{
			if (WIFEXITED(wstatus) != 0)
				exit_code = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus) != 0)
				exit_code = WTERMSIG(wstatus);
		}
	}
	delete_all_heredoc_tmpfile(head);
	return (exit_code);
}

void	child(t_info *info, t_container *con)
{
	if (info->idx != 0)
		info->data = info->data->next;
	info->cur = info->idx % 2;
	close(info->pipe_fds[info->cur][0]);
	close(info->pipe_fds[info->cur][1]);
	if (info->idx != info->cnt - 1)
		open_pipe(info);
	info->last_pid = fork();
	if (info->last_pid == -1)
	{
		wait_children(info, con->head);
		perror_exit("fork()", 1);
	}
	if (info->last_pid == 0)
	{
		open_file(info);
		close_pipe(info);
		redirect(info);
		if (execute_cmd(info) == -1)
			perror_exit("execve()", 1);
	}
}

int	pipex(t_container *con)
{
	t_info	info;

	init_info(&info, con);
	while (++info.idx < info.cnt)
		child(&info, con);
	close_all_pipe(&info);
	return (wait_children(&info, con->head));
}
