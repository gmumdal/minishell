/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:13 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/12 14:37:30 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	char	*toss;
	int		len;

	len = ft_strlen(s1);
	toss = (char *)malloc(sizeof(char) * (len + 1));
	if (toss == 0)
		return (0);
	toss[len] = 0;
	while (len-- > 0)
		toss[len] = s1[len];
	return (toss);
}
