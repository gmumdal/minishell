/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:50:33 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/20 21:56:21 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_readline(t_container *con, char *line);

void	pre_init_container(t_container *con, char **envp)
{
	char	*cur_path;

	cur_path = getcwd(NULL, MAXSIZE);
	if (cur_path == NULL)
		perror_exit("getcwd()", 1);
	con->pwd = cur_path;
	con->envp = ms_2d_arr_dup(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_container		con;

	if (ac != 1)
		return (0);
	(void) av;
	exit_code = 0;
	ms_sigset(sig_newline, SIG_IGN);
	save_input_mode(&con.old_term);
	set_input_mode(&con.new_term);
	pre_init_container(&con, envp);
	ms_readline(&con, NULL);
	printf("\033[u\033[1B\033[1Aexit\n");
	reset_input_mode(&con.old_term);
	return (exit_code);
}

void	ms_readline(t_container *con, char *line)
{
	t_token		*head;

	while (42)
	{
		free(line);
		line = readline("mish> \033[s");
		if (!line)
			break ;
		if (!line[0])
			continue ;
		add_history(line);
		head = parsing(line, con->envp);
		if (head == NULL || check_token(head))
		{
			continue ;
		}
		if (init_container(con, head) == 0)
			continue ;
		if (con->cnt == 1 && check_builtin(con->head->cmd_arr[0]) == 0)
			execute_builtin(con->head->cmd_arr, con, 0);
		else
			pipex(con);
	}
}
