/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:53:19 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/22 09:53:20 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data_node(t_data *node)
{
	node->infile = NULL;
	node->outfile = NULL;
	node->delimeter = NULL;
	node->cmd_arr = NULL;
	node->is_append = 0;
	node->next = NULL;
}

int	get_cmd_arr_len(t_token *lst)
{
	int	len;

	len = 0;
	while (lst->type != -5)
	{
		if (lst->type == 0)
			len++;
		lst = lst->next;
	}
	return (len);
}

int	get_data_list_len(t_data *lst)
{
	int	len;

	len = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
