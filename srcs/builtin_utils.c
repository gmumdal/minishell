/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:27:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 22:32:37 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *s)
{
	if (ft_strncmp(s, "cd", 3) == 0 || ft_strncmp(s, "echo", 5) == 0
		|| ft_strncmp(s, "pwd", 4) == 0 || ft_strncmp(s, "env", 4) == 0
		|| ft_strncmp(s, "unset", 6) == 0 || ft_strncmp(s, "exit", 5) == 0
		|| ft_strncmp(s, "export", 7) == 0)
		return (0);
	return (1);
}

int	execute_builtin(char **cmds, t_container *con, int flag)
{
	if (ft_strncmp(cmds[0], "cd", 3) == 0)
		return (builtin_cd(cmds, con));
	else if (ft_strncmp(cmds[0], "pwd", 4) == 0)
	{
		ft_putstr_fd(con->pwd, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (ft_strncmp(cmds[0], "unset", 6) == 0)
		return (builtin_unset(cmds, con));
	else if (ft_strncmp(cmds[0], "exit", 5) == 0)
		return (builtin_exit(cmds, flag));
	else if (ft_strncmp(cmds[0], "export", 7) == 0)
		return (builtin_export(cmds, con));
	else if (ft_strncmp(cmds[0], "env", 4) == 0)
		return (builtin_env(con->envp));
	else if (ft_strncmp(cmds[0], "echo", 5) == 0)
		return (builtin_echo(cmds));
	return (0);
}

int	execute_builtin_one_case(t_container *con)
{
	int	in_fd;
	int	out_fd;
	int	stdin;
	int	stdout;

	in_fd = 2147483647;
	out_fd = 2147483646;
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (con->head->infile != NULL)
	{
		in_fd = open(con->head->infile, O_RDONLY);
		if (in_fd == -1)
			print_file_error(con->head->infile);
		dup2(in_fd, STDIN_FILENO);
	}
	if (con->head->outfile != NULL)
	{
		if (con->head->is_append == 1)
			out_fd = open(con->head->outfile,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			out_fd = open(con->head->outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (out_fd == -1)
			error_print(errno);
		dup2(out_fd, STDOUT_FILENO);
	}
	exit_code = execute_builtin(con->head->cmd_arr, con, 0);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(in_fd);
	close(out_fd);
	close(stdin);
	close(stdout);
	return (exit_code);
}

int	get_2d_arr_len(char	**s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}
