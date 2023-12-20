/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:36:41 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/20 15:10:55 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sigset(void (*sigint_func)(int), void (*sigquit_func)(int))
{
	signal(SIGINT, (*sigint_func));
	signal(SIGQUIT, (*sigquit_func));
}

void	sig_newline(int signum)
{
	(void)signum;
	exit_code = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_heredoc(int signum)
{
	exit(128 + signum);
}
