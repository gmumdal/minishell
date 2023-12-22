/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokennew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:28:00 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 12:56:32 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_typecheck(char *data);

t_token	*ms_tokennew(char *data, t_container *con)
{
	t_token	*toss;

	if (ft_init(data, "$") > -1)
		data = expend_list(data, con);
	if (data == NULL)
		return (NULL);
	toss = (t_token *)ft_calloc(1, sizeof(t_token));
	toss->next = NULL;
	toss->prev = NULL;
	toss->data = data;
	if (data != 0 && ft_init(data, "|<>&;\\") > -1
		&& ft_init(data, "\'\"") == -1)
		toss->type = ms_typecheck(data);
	else
		toss->type = 0;
	return (toss);
}

static int	ms_typecheck(char *data)
{
	if (ft_strncmp(">", data, 2) == 0)
		return (-1);
	else if (ft_strncmp(">>", data, 3) == 0)
		return (-2);
	else if (ft_strncmp("<", data, 2) == 0)
		return (-3);
	else if (ft_strncmp("<<", data, 3) == 0)
		return (-4);
	else if (ft_strncmp("|", data, 2) == 0)
		return (-5);
	return (100);
}
