/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:50:33 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/19 11:45:40 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_token		*head;
	char		*line;
	t_container	con;

	(void) ac;
	(void) av;
	pre_init_container(&con, envp);
	con.envp = ms_2d_arr_dup(envp);
	while (42)
	{
		print_pwd_oldpwd(&con);
		line = readline("mish> ");
		if (!line)
			break ;
		add_history(line);
		head = parsing(line, con.envp);
		if (head == NULL)
			error_print(errno);
		init_container(&con, head);
		if (con.cnt == 1 && check_builtin(con.head->cmd_arr[0]) == 0)
			execute_builtin(con.head->cmd_arr, &con);
		else
			pipex(&con);
		ms_tokenclear(&head, free);
		free(line);
	}
	return (0);
}
