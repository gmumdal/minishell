/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:58:55 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/08 15:06:10 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
