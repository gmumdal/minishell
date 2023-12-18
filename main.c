/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:50:33 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/18 14:56:34 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_token		*head;
	t_token	*tmp;
	char		*line;
	t_container	con;

	(void) ac;
	(void) av;
	con.envp = ms_2d_arr_dup(envp);
	while (42)
	{
		line = readline("mish> ");
		if (!line)
			break ;
		add_history(line);
		head = parsing(line, con.envp);
		if (head != NULL)
		{
			init_container(&con, head, envp);
			tmp = head;
			while (tmp != NULL)
			{
				printf("data: [%s] type: [%d] \n", tmp->data, tmp->type);
				tmp = tmp->next;
			}
			pipex(&con);
		}
		ms_tokenclear(&head, free);
		free(line);
	}
	return (0);
}
