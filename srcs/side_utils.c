/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:33:16 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 10:18:24 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(char *s, char *data)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = -1;
		while (data[++j])
			if (s[i] == data[j])
				return (j);
		i++;
	}
	return (-1);
}

char	*exit_expend(char *expend)
{
	char	*toss;
	char	*itoa_exit;

	itoa_exit = ft_itoa(g_exit_code);
	toss = ft_strjoin(itoa_exit, expend + 2);
	free(itoa_exit);
	free(expend);
	return (toss);
}

int	check_token(t_token	*head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type < 0 && tmp->type > -5 && tmp->next == NULL)
			return (print_syntax_error("newline", &head));
		else if (tmp->type < 0 && tmp->type > -5 && tmp->next != NULL
			&& tmp->next->type < 0 && tmp->next->type > -5)
			return (print_syntax_error(tmp->data, &head));
		else if (tmp->type == -5 && (tmp->next == NULL
				|| (tmp->next != NULL && tmp->next->type == -5)))
			return (print_syntax_error("|", &head));
		else if (tmp->type == -5 && (tmp->prev == NULL
				|| (tmp->prev != NULL && tmp->prev->type < 0)))
			return (print_syntax_error("|", &head));
		tmp = tmp->next;
	}
	return (0);
}
