/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:28:15 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 13:47:38 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_print(int flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(strerror(flag), 2);
	ft_putstr_fd("\n", 2);
	if (flag == 126)
		exit(126);
	exit(1);
}

void	print_command_error(char *cmd, t_container *con)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", 2);
	con->exit_code = 127;
	exit(127);
}

void	print_file_error(char *file, t_container *con)
{
	struct stat	buf;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	if (stat(file, &buf) == -1)
		ft_putstr_fd("No such file or directory\n", 2);
	else
		ft_putstr_fd("Permission denied\n", 2);
	con->exit_code = 1;
	exit(1);
}

void	print_execve_error(char *cmd, t_container *con)
{
	struct stat buf;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (stat(cmd, &buf) == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		exit(127);
	}
	else if (S_ISDIR(buf.st_mode) == 1)
		ft_putstr_fd("is a directory\n", 2);
	else
		ft_putstr_fd("Permission denied\n", 2);
	con->exit_code = 126;
	exit(126);
}
