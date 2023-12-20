/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:33:16 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/20 21:59:10 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_print(int flag)
{
	ft_putstr_fd("mish: ", 2);
	if (flag == 2)
		ft_putstr_fd("input: ", 2);
	ft_putstr_fd(strerror(flag), 2);
	ft_putstr_fd("\n", 2);
	if (flag == 126)
		exit(126);
	exit(1);
}

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

int	syntax_error_print(char *error_char, t_token **head)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error_char, 2);
	ft_putstr_fd("\'\n", 2);
	exit_code = 258;
	ms_tokenclear(head, free);
	return (1);
}
