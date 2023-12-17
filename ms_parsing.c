/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:20:48 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/16 21:12:44 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parsing(char *line, char **envp)
{
	t_token	*head;
	t_token	*tmp;
	char	**command;
	int		i;

	head = 0;
	command = ms_split(line);
	if (command == 0)
		return (NULL);
	i = 0;
	while (command[i])
	{
		tmp = ms_tokennew(ft_strdup(command[i++]), envp);
		if (ms_tokenadd_back(&head, tmp) == 0)
			error_print(errno);
		if (tmp->type == 100)
		{
			ms_tokenclear(&head, free);
			break ;
		}
	}
	split_free(command);
	return (head);
}

void	split_free(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		free(command[i++]);
	free(command);
}
