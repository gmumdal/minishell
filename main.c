/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:50:33 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/19 16:40:34 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum);
void	ms_readline(char **envp, t_container *con);

int	main(int ac, char **av, char **envp)
{
	t_container		con;

	(void) ac;
	(void) av;
	ms_sigset(sig_newline, SIG_IGN);
	save_input_mode(&con.old_term);
	set_input_mode(&con.new_term);
	ms_readline(envp, &con);
	reset_input_mode(&con.old_term);
	return (0);
}

void	ms_readline(char **envp, t_container *con)
{
	t_token		*head;
	char		*line;

	con->envp = ms_2d_arr_dup(envp);
	while (42)
	{
		line = readline("mish> ");
		if (!line)
			break ;
		if (!line[0])
			continue ;
		add_history(line);
		head = parsing(line, con->envp);
		if (head == NULL)
			error_print(errno);
		if (init_container(con, head) == 0)
			continue ;
		pipex(con);
		ms_tokenclear(&head, free);
		free(line);
	}
}
