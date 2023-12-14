/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 21:17:51 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/08 15:20:19 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*cur;
	void	*tempcon;

	if (lst == 0)
		return (0);
	head = 0;
	while (lst != NULL)
	{
		tempcon = f(lst->data);
		cur = ft_lstnew(tempcon);
		ft_lstadd_back(&head, cur);
		if (cur == 0)
		{
			del(tempcon);
			ft_lstclear(&head, del);
			return (0);
		}
		lst = lst->next;
	}
	return (head);
}