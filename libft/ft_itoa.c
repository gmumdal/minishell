/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:29:58 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 14:34:54 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_recur(char *num, long long ln)
{
	if (ln < 0)
	{
		*num = '-';
		ln *= -1;
	}	
	if (ln < 10)
	{
		while (*num != 0)
			num++;
		*num = ln + '0';
	}
	else
	{
		ft_itoa_recur(num, ln / 10);
		while (*num != 0)
			num++;
		*num = ln % 10 + '0';
	}
}

static size_t	ft_power(int n)
{
	size_t	power;

	power = 1;
	if (n <= 0)
		power++;
	while (n != 0)
	{
		n /= 10;
		power++;
	}
	return (power);
}

char	*ft_itoa(int n)
{
	char		*num;
	long long	ln;

	ln = n;
	num = (char *)ft_calloc(ft_power(n), sizeof(char));
	ft_itoa_recur(num, ln);
	return (num);
}
