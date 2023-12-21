/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 21:00:43 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 17:31:51 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ms_type_check(t_token *new);
static t_token	*ms_tokenlast(t_token *token);
static char		*rm_quote(char *data);

int	ms_tokenadd_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (token == 0 || new == 0)
		return (0);
	if (*token == 0)
		*token = new;
	else
	{
		last = ms_tokenlast(*token);
		new->prev = last;
		last->next = new;
		new->type = ms_type_check(new);
	}
	if (ft_init(new->data, "\"\'") > -1)
		new->data = rm_quote(new->data);
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
	else if (tmp->type == -4 && ft_init(new->data, "\"\'") == -1)
		return (4);
	else if (tmp->type == -4 && ft_init(new->data, "\"\'") > -1)
		return (5);
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

static char	*rm_quote(char *data)
{
	int		i;
	int		j;
	char	quote;
	char	*toss;

	quote = 0;
	toss = (char *)ft_calloc(ft_strlen(data) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (data[i] != 0)
	{
		if (quote == 0 && (data[i] == '\'' || data[i] == '\"'))
			quote = data[i++];
		if (quote != 0 && data[i] == quote)
		{
			quote = 0;
			i++;
			continue ;
		}
		toss[j++] = data[i++];
	}
	free(data);
	return (toss);
}
