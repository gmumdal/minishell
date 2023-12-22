/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:28:02 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 09:55:45 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data_lstnew(t_token *line, t_container *con)
{
	t_data	*toss;

	if (line == NULL)
		return (NULL);
	toss = (t_data *)ft_calloc(1, sizeof(t_data));
	init_data_node(toss);
	toss->cmd_arr = make_cmd(line);
	if (check_type_and_dup_data(line, toss, con) == 0)
	{
		free_2d_array(toss->cmd_arr);
		free(toss->infile);
		free(toss->outfile);
		free(toss->delimeter);
		free(toss);
		return (0);
	}
	return (toss);
}

t_data	*data_lstlast(t_data *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	data_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*cur;

	if (lst == NULL || new == NULL)
		return (0);
	if (*lst != NULL)
	{
		cur = data_lstlast(*lst);
		cur->next = new;
	}
	else
		*lst = new;
	return (1);
}

void	data_lstclear(t_data **lst, void (*del)(void *))
{
	t_data	*cur;

	if (lst == 0 || del == 0)
		return ;
	while (*lst != NULL)
	{
		cur = *lst;
		*lst = (*lst)->next;
		free_2d_array(cur->cmd_arr);
		free(cur->delimeter);
		free(cur->infile);
		free(cur->outfile);
		free(cur);
	}
	*lst = 0;
}
