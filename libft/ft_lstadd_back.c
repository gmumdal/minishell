/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 21:00:43 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/14 15:44:17 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ms_type_check(t_list *new);

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == 0 || new == 0)
		return (0);
	if (*lst == 0)
	{
		*lst = new;
		return (1);
	}
	last = ft_lstlast(*lst);
	new->prev = last;
	last->next = new;
	new->type = ms_type_check(new);
	return (1);
}

static int	ms_type_check(t_list *new)
{
	t_list	*tmp;

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
