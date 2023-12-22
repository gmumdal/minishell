/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:29:33 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 12:29:42 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_2d_arr_dup(char **s)
{
	char	**result;
	int		len;
	int		i;

	len = 0;
	while (s[len] != NULL)
		len++;
	result = (char **)ft_calloc((len + 1), sizeof(char *));
	i = 0;
	while (i < len)
	{
		result[i] = ft_strdup(s[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	get_2d_arr_len(char	**s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int	check_empty(char *s)
{
	while (*s)
	{
		if (*s != 32)
			return (0);
		s++;
	}
	return (1);
}
