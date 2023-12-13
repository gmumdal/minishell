/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pasing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:20:48 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/11 18:36:32 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*pasing(char *line)
{
	t_list	*head;
	t_list	*tmp;
	char	**command;
	int		i;

	head = 0;
	command = ms_split(line);
	if (command == 0)
		return (NULL);
	i = 0;
	while (command[i])
	{
		tmp = ft_lstnew(ft_strdup(command[i++]));
		if (ft_lstadd_back(&head, tmp) == 0)
			error_print(errno);
		if (tmp->type == 100)
		{
			ft_lstclear(&head, free);
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
