/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:55:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/20 16:56:08 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bulitin_exit(char **cmds, t_container *con)
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
		if (ft_isalpha(cmds[1][j++]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required", cmds[1]);
			exit(255);
		}
	}
	if (i > 2)
	{
		printf("minishell: exit: too many arguments");
		return ;
	}
	exit(ft_atoi(cmds[1]));
}
