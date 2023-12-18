/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:50:33 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/18 21:15:19 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum);
void	ms_readline(char **envp);

int	main(int ac, char **av, char **envp)
{
	struct termios	old_term;
	struct termios	new_term;

	(void) ac;
	(void) av;
	signal(SIGINT, handler);
	save_input_mode(&old_term);
	set_input_mode(&new_term);
	ms_readline(envp);
	reset_input_mode(&old_term);
	return (0);
}

void	ms_readline(char **envp)
{
	t_token		*head;
	char		*line;
	t_container	con;

	con.envp = ms_2d_arr_dup(envp);
	while (42)
	{
		line = readline("mish> ");
		if (!line)
			break ;
		add_history(line);
		head = parsing(line, con.envp);
		if (head == NULL)
			error_print(errno);
		init_container(&con, head, envp);
		pipex(&con);
		ms_tokenclear(&head, free);
		free(line);
	}
}

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}
