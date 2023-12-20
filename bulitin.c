/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:55:45 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/20 16:12:46 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bulitin_exit(int exitcode)
{
	printf("exit\n");
	exit(exitcode);
}

void	bulitin_echo(t_container *con)
