/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:28:00 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/13 21:57:03 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_init(char *s, char *data);
static int	ft_typecheck(char *data);
static char	*check_quote(char *data, int *quote);

t_list	*ft_lstnew(char *data)
{
	t_list	*toss;
	int		quote;

	if (data == 0)
		error_print(errno);
	data = check_quote(data, &quote);
	toss = (t_list *)malloc(sizeof(t_list) * 1);
	if (toss == 0)
		error_print(errno);
	toss->next = NULL;
	toss->prev = NULL;
	toss->data = data;
	if (ft_init("$|&<>;\\", data) > -1)
		toss->type = ft_typecheck(data);
	else
		toss->type = 0;
	if (toss->type == 5 && quote == 0)
		toss->type = 0;
	return (toss);
}

static int	ft_init(char *s, char *data)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = -1;
		while (data[++j])
			if (s[i] == data[j])
				return (j);
		i++;
	}
	return (-1);
}

static int	ft_typecheck(char *data)
{
	if (ft_strncmp(">", data, 2) == 0)
		return (-1);
	else if (ft_strncmp(">>", data, 3) == 0)
		return (-2);
	else if (ft_strncmp("<", data, 2) == 0)
		return (-3);
	else if (ft_strncmp("<<", data, 3) == 0)
		return (-4);
	else if (ft_strncmp("|", data, 2) == 0)
		return (-5);
	else if (ft_init("$", data) > -1)
		return (5);
	printf("syntax error: %s\n", data);
	return (100);
}

static char	*check_quote(char *data, int *quote)
{
	char	*trim;
	char	sep[3];
	int		i[2];

	sep[0] = '\'';
	sep[1] = '\"';
	sep[2] = 0;
	*quote = ft_init(data, sep);
	if (*quote == -1)
		return (data);
	trim = (char *)malloc(sizeof(char) * ft_strlen(data));
	if (trim == 0)
		error_print(errno);
	i[0] = 0;
	i[1] = 0;
	while (data[i[0]] != 0)
	{
		if (data[i[0]] == sep[*quote])
			i[0]++;
		trim[i[1]++] = data[i[0]++];
	}
	free(data);
	return (trim);
}
