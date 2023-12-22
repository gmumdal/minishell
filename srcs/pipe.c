/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:25:31 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/22 13:21:45 by jongmlee         ###   ########.fr       */
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
	int	result;
	int	error_num;

	error_num = errno;
	i = 0;
	while (1)
	{
		result = wait(&wstatus);
		if (result == -1)
			break ;
		if (result == info->last_pid)
			con->exit_code = check_exitcode(wstatus);
	}
	ms_sigset(sig_newline, SIG_IGN);
	set_input_mode(&con->new_term);
	delete_all_heredoc_tmpfile(con->head);
	return (error_num);
}

int	check_exitcode(int wstatus)
{
	int	exitcode;

	exitcode = 0;
	if (WIFEXITED(wstatus) != 0)
		exitcode = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus) != 0)
	{
		exitcode = WTERMSIG(wstatus) + 128;
		if (exitcode == 131)
			printf("Quit: %d\n", exitcode - 128);
		else
			printf("\n");
	}
	return (exitcode);
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
		error_print(wait_children(info, con));
	if (info->last_pid == 0)
	{
		reset_input_mode(&con->old_term);
		ms_sigset(SIG_DFL, SIG_DFL);
		open_file(info, con);
		close_pipe(info);
		redirect(info);
		execute_cmd(info, con);
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
