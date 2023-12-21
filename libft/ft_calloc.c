/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:28:53 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 14:23:40 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*toss;
	size_t	max;

	max = -1;
	if (count * size == 0)
		return (malloc(0));
	if (size >= max / count)
		return (0);
	toss = malloc(count * size);
	if (toss == 0)
		exit(1);
	ft_bzero(toss, count * size);
	return (toss);
}
