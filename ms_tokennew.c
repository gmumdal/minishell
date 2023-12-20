/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokennew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:28:00 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/20 21:48:21 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_typecheck(char *data);

t_token	*ms_tokennew(char *data, char **envp)
{
	t_token	*toss;

	if (data == 0)
		error_print(errno);
	if (ft_init(data, "$") > -1)
		data = expend_list(data, envp);
	toss = (t_token *)malloc(sizeof(t_token) * 1);
	if (toss == 0)
		error_print(errno);
	toss->next = NULL;
	toss->prev = NULL;
	toss->data = data;
	if (data != 0 && ft_init(data, "|<>&;\\") > -1)
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
