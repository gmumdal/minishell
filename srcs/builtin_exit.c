/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:55:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 12:43:37 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_error_check(char **cmds, int i);

int	builtin_exit(char **cmds, int flag)
{
	int	i;
	int	exitcode;

	if (flag == 0)
		printf("exit\n");
	i = 0;
	while (cmds[i])
		i++;
	if (i == 1)
		exit(0);
	exitcode = exit_error_check(cmds, i);
	if (exitcode == -1)
		return (1);
	exit(exitcode);
}

static int	exit_error_check(char **cmds, int i)
{
	int	j;

	j = 0;
	if (ft_strlen(cmds[1]) > 20 || (ft_strlen(cmds[1]) == 20
			&& ft_strncmp(cmds[1], "9223372036854775807", 20) > 0))
	{
		print_execute_error("exit", cmds[1], "numeric argument required");
		exit(255);
	}
	while (cmds[1][j])
	{
		if (ft_isdigit(cmds[1][j]) == 0 && cmds[1][j] != '+'
			&& cmds[1][j] != '-')
		{
			print_execute_error("exit", cmds[1], "numeric argument required");
			exit(255);
		}
		j++;
	}
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (-1);
	}
	return (ft_atoi(cmds[1]));
}
