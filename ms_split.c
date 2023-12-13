/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:02:17 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/13 20:33:05 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_split(char *cmd)
{
	char	**toss;
	int		count;
	int		index;
	int		wordlen;

	wordlen = ft_strlen(cmd);
	toss = (char **)ft_calloc(wordlen + 1, sizeof(char *));
	if (toss == 0)
		error_print(errno);
	count = 0;
	while (count < wordlen && *cmd != 0)
	{
		index = 0;
		toss[count] = (char *)ft_calloc(wordlen + 1, sizeof(char));
		if (toss[count] == 0)
			error_print(errno);
		if (ms_split_input(toss[count], &cmd, "<>|&();") == -1)
			return (NULL);
		count++;
	}
	return (toss);
}

int	ms_split_input(char *toss, char **cmd, char *oper)
{
	int		i;

	i = 0;
	while (**cmd == ' ')
			(*cmd)++;
	if (ms_split_first(toss, cmd, oper) > 0)
		return (0);
	while (ms_init(**cmd, oper) == -1 && **cmd != ' ' && **cmd != 0)
	{
		if (**cmd == '\"' || **cmd == '\'')
		{
			if (ms_split_plus(toss, &i, cmd) == -1)
				return (-1);
			continue ;
		}
		toss[i++] = *(*cmd)++;
	}
	while (**cmd == ' ')
		(*cmd)++;
	return (0);
}

int	ms_split_first(char *toss, char **cmd, char *oper)
{
	int		i;

	i = 0;
	while (ms_init(**cmd, oper) > -1)
		toss[i++] = *(*cmd)++;
	while (**cmd == ' ')
		(*cmd)++;
	return (i);
}

int	ms_split_plus(char *toss, int *i, char **cmd)
{
	char	sep;

	sep = *(*cmd);
	toss[(*i)++] = *(*cmd)++;
	while (**cmd != sep && **cmd != 0)
		toss[(*i)++] = *(*cmd)++;
	toss[(*i)++] = *(*cmd);
	if (**cmd != sep)
	{
		printf("syntax error: %c\n", sep);
		return (-1);
	}
	(*cmd)++;
	return (0);
}

int	ms_init(char c, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}
