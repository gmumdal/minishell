/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:25:31 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/20 17:04:51 by jongmlee         ###   ########.fr       */
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

int	wait_children(t_info *info, t_container *con)
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
			exit_code = check_exitcode(wstatus);
	}
	ms_sigset(sig_newline, SIG_IGN);
	set_input_mode(&con->new_term);
	delete_all_heredoc_tmpfile(con->head);
	return (exit_code);
}

int	check_exitcode(int wstatus)
{
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(wstatus) != 0)
		exit_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus) != 0)
	{
		exit_code = WTERMSIG(wstatus);
		if (exit_code == 3)
			printf("Quit: %d\n", exit_code);
		else
			printf("\n");
	}
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
	ms_sigset(SIG_IGN, SIG_IGN);
	info->last_pid = fork();
	if (info->last_pid == -1)
	{
		wait_children(info, con);
		perror_exit("fork()", 1);
	}
	if (info->last_pid == 0)
	{
		reset_input_mode(&con->old_term);
		ms_sigset(SIG_DFL, SIG_DFL);
		open_file(info);
		close_pipe(info);
		redirect(info);
		if (execute_cmd(info, con) == -1)
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
	return (wait_children(&info, con));
}
