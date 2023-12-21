/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:35:12 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 20:59:55 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	size_t	index;
	char	*toss;

	index = 0;
	if (s1 == 0)
		total_len = ft_strlen(s2);
	else
		total_len = ft_strlen(s1) + ft_strlen(s2);
	toss = (char *)ft_calloc(total_len + 1, sizeof(char));
	if (s1 != 0)
		ft_strlcat(toss, s1, total_len + 1);
	ft_strlcat(toss, s2, total_len + 1);
	return (toss);
}
