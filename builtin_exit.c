/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:55:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/20 17:11:38 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(char **cmds)
{
	int	i;
	int	j;

	printf("exit\n");
	i = 0;
	while (cmds[i])
		i++;
	if (i == 1)
		exit(0);
	j = 0;
	while (cmds[1][j])
	{
		if (ft_isdigit(cmds[1][j++]) == 0)
		{
			print_execute_error("exit", cmds[1], "numeric argument required\n");
			exit(255);
		}
	}
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	exit(ft_atoi(cmds[1]));
}
