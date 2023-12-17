/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 21:00:43 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/16 20:43:02 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ms_type_check(t_token *new);
static t_token	*ms_tokenlast(t_token *token);

int	ms_tokenadd_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (token == 0 || new == 0)
		return (0);
	if (*token == 0)
	{
		*token = new;
		return (1);
	}
	last = ms_tokenlast(*token);
	new->prev = last;
	last->next = new;
	new->type = ms_type_check(new);
	return (1);
}

static int	ms_type_check(t_token *new)
{
	t_token	*tmp;

	if (new->type != 0)
		return (new->type);
	tmp = new->prev;
	if (tmp->type == -1)
		return (1);
	else if (tmp->type == -2)
		return (2);
	else if (tmp->type == -3)
		return (3);
	else if (tmp->type == -4)
		return (4);
	else
		return (0);
}

static t_token	*ms_tokenlast(t_token *token)
{
	if (token == 0)
		return (0);
	while (token->next != NULL)
		token = token->next;
	return (token);
}
