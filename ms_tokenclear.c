/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 21:12:19 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/16 20:42:57 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_tokendelone(t_token *token, void (*del)(void *));

void	ms_tokenclear(t_token **token, void (*del)(void *))
{
	t_token	*cur;

	if (token == 0 || del == 0)
		return ;
	while (*token != NULL)
	{
		cur = *token;
		*token = (*token)->next;
		ms_tokendelone(cur, del);
	}
	*token = 0;
}

void	ms_tokendelone(t_token *token, void (*del)(void *))
{
	if (token == 0 || del == 0)
		return ;
	del(token->data);
	free(token);
}
