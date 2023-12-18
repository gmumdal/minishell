/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:28:00 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/18 14:56:44 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*toss;

	toss = (t_list *)malloc(sizeof(t_list) * 1);
	if (toss == 0)
		return (0);
	toss->next = NULL;
	toss->content = content;
	return (toss);
}
