/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:50:33 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/16 21:12:54 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_list		*head;
	char		*line;
	t_container	con;

	(void) ac;
	(void) av;
	//(void) envp;
	while (42)
	{
		line = readline("mish> ");
		if (!line)
			break ;
		add_history(line);
		head = pasing(line);
		if (head != NULL)
		{
			init_container(&con, head, envp);
			//print_container(&con);
			pipex(&con);
			//t_list	*tmp;
			//tmp = head;
			//while (tmp != NULL)
			//{
			//	printf("data: [%s] type: [%d] \n", tmp->data, tmp->type);
			//	tmp = tmp->next;
			//}
		}
		ft_lstclear(&head, free);
		free(line);
	}
	return (0);
}
