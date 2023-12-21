/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:13 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 14:24:37 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	char	*toss;
	int		len;

	len = ft_strlen(s1);
	toss = (char *)ft_calloc((len + 1), sizeof(char));
	toss[len] = 0;
	while (len-- > 0)
		toss[len] = s1[len];
	return (toss);
}
