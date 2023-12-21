/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:33:16 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 15:05:41 by jongmlee         ###   ########.fr       */
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

	itoa_exit = ft_itoa(exit_code);
	toss = ft_strjoin(itoa_exit, expend + 2);
	free(itoa_exit);
	free(expend);
	return (toss);
}

int	check_token(t_token	*head)
{
	while (head)
	{
		if (head->type < 0 && head->type > -5 && head->next == NULL)
			return (print_syntax_error("newline", &head));
		else if (head->type < 0 && head->type > -5 && head->next != NULL
			&& head->next->type < 0 && head->next->type > -5)
			return (print_syntax_error(head->data, &head));
		else if (head->type == -5 && (head->next == NULL
				|| (head->next != NULL && head->next->type == -5)))
			return (print_syntax_error("|", &head));
		else if (head->type == -5 && (head->prev == NULL
				|| (head->prev != NULL && head->prev->type < 0)))
			return (print_syntax_error("|", &head));
		head = head->next;
	}
	return (0);
}
