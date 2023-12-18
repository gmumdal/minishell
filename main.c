/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:50:33 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/18 21:11:24 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_init_container(t_container *con, char **envp)
{
	char	*buffer;
	char	*cur_path;

	buffer = (char *)malloc(sizeof(char) * MAXSIZE);
	if (buffer == NULL)
		perror_exit("malloc()", 1);
	cur_path = getcwd(buffer, MAXSIZE);
	if (cur_path == NULL)
		perror_exit("getcwd()", 1);
	con->old_pwd = cur_path;
	con->pwd = ft_strdup(cur_path);
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
	return (0);
}
