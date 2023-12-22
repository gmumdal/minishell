/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:50:33 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 13:40:27 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_container		con;

	if (ac != 1)
		return (0);
	(void) av;
	g_signal = 0;
	ms_sigset(sig_newline, SIG_IGN);
	save_input_mode(&con.old_term);
	set_input_mode(&con.new_term);
	pre_init_container(&con, envp);
	ms_readline(&con, NULL);
	free(con.pwd);
	free_2d_array(con.envp);
	printf("\033[u\033[1B\033[1Aexit\n");
	reset_input_mode(&con.old_term);
	return (con.exit_code);
}

void	pre_init_container(t_container *con, char **envp)
{
	char	*cur_path;

	cur_path = getcwd(NULL, MAXSIZE);
	con->pwd = cur_path;
	con->envp = ms_2d_arr_dup(envp);
	con->exit_code = 0;
}

void	ms_readline(t_container *con, char *line)
{
	t_token		*head;

	while (42)
	{
		free(line);
		line = readline("minishell> \033[s");
		if (!line)
			break ;
		if (!line[0] || check_empty(line))
			continue ;
		add_history(line);
		head = parsing(line, con);
		if (head == NULL || check_token(head, con))
			continue ;
		if (init_container(con, head) == 0)
			continue ;
		if (con->cnt == 1 && con->head->cmd_arr[0] != NULL
			&& check_builtin(con->head->cmd_arr[0]) == 0)
			con->exit_code = execute_builtin_one_case(con);
		else
			pipex(con);
		line_clear(&head, con);
	}
}

void	line_clear(t_token **token, t_container *con)
{
	ms_tokenclear(token, free);
	data_lstclear(&con->head, free);
}
