/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:33:16 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 11:37:23 by hyeongsh         ###   ########.fr       */
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
	if (itoa_exit == 0)
		error_print(errno);
	toss = ft_strjoin(itoa_exit, expend + 2);
	if (toss == 0)
		error_print(errno);
	free(itoa_exit);
	free(expend);
	return (toss);
}

int	check_token(t_token	*head)
{
	while (head)
	{
		if (head->type < 0 && head->type > -5 && head->next == NULL)
			return (syntax_error_print("newline", &head));
		else if (head->type < 0 && head->type > -5 && head->next != NULL
			&& head->next->type < 0 && head->next->type > -5)
			return (syntax_error_print(head->data, &head));
		else if (head->type == -5 && (head->next == NULL
				|| (head->next != NULL && head->next->type == -5)))
			return (syntax_error_print("|", &head));
		else if (head->type == -5 && (head->prev == NULL
				|| (head->prev != NULL && head->prev->type < 0)))
			return (syntax_error_print("|", &head));
		head = head->next;
	}
	return (0);
}
