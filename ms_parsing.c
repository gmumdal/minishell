/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:20:48 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 20:54:01 by jongmlee         ###   ########.fr       */
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
		if (tmp == NULL)
			continue ;
		ms_tokenadd_back(&head, tmp);
		if (tmp->type == 100)
		{
			print_syntax_error(&tmp->data[ft_strlen(tmp->data) - 1], &head);
			break ;
		}
	}
	free_2d_array(command);
	return (head);
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}