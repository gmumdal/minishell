/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:31:23 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 22:29:40 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_option_check(char *cmd);
static void	echo_print(int print_flag, int option_flag, char **cmds, int i);

int	builtin_echo(char **cmds)
{
	int	option_flag;
	int	print_flag;
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	if (i == 1)
	{
		printf("\n");
		return (0);
	}
	option_flag = 0;
	print_flag = 0;
	if (i > 1 && echo_option_check(cmds[1]))
		option_flag = 1;
	else
		print_flag = 1;
	i = 1;
	echo_print(print_flag, option_flag, cmds, i);
	return (0);
}

static int	echo_option_check(char *cmd)
{
	int	i;

	if (cmd[0] != '-')
		return (0);
	i = 1;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	echo_print(int print_flag, int option_flag, char **cmds, int i)
{
	while (cmds[i])
	{
		if (echo_option_check(cmds[i]) == 0)
			print_flag = 1;
		if (print_flag == 1)
			ft_putstr_fd(cmds[i], 1);
		if (cmds[i + 1] == 0 && option_flag == 0)
			ft_putstr_fd("\n", 1);
		else if (cmds[i + 1] != 0
			&& (echo_option_check(cmds[i]) == 0 || print_flag == 1))
			ft_putstr_fd(" ", 1);
		i++;
	}
}
