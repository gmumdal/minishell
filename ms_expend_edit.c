/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expend_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:18:05 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/21 15:03:11 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_expend(char *expend, char *data, int *i, int type);
static int	quote_edit(char c, int *quote, int type);
static char	*env_expend(char *expend, char **envp);
static char	*join_expend(char **expend, int j);

char	*expend_list(char *data, char **envp)
{
	char	**expend;
	int		i;
	int		j;

	i = 0;
	j = 0;
	expend = (char **)ft_calloc(ft_strlen(data) + 1, sizeof(char *));
	if (expend == 0)
		error_print(errno);
	while (data[i])
	{
		expend[j] = (char *)ft_calloc(ft_strlen(data) + 1, sizeof(char));
		if (expend[j] == 0)
			error_print(errno);
		if (make_expend(expend[j], data, &i, 0) == 1)
			expend[j] = env_expend(expend[j], envp);
		j++;
	}
	free(data);
	return (join_expend(expend, j));
}

static int	make_expend(char *expend, char *data, int *i, int type)
{
	static int	quote;
	int			j;

	j = 0;
	while (data[*i])
	{
		if (quote == 0 && type == 0 && (data[*i] == '\'' || data[*i] == '\"')
			&& (*i)++ > -1)
			quote = 1 * (data[*i - 1] == '\'') + 2 * (data[*i - 1] == '\"');
		if ((quote == 0 || quote == 2) && data[*i] == '$' && j > 0)
			break ;
		if ((quote == 0 || quote == 2) && data[*i] == '$' && j == 0)
			type = 1;
		if (type == 0 && ((quote == 1 && data[*i] == '\'')
				|| (quote == 2 && data[*i] == '\"')) && (*i)++ > -1)
		{
			quote = 0;
			continue ;
		}
		if (type == 1 && j > 0 && ((data[*i] == '$' || data[*i] == ' '
					|| data[*i] == 0 || data[*i] == '\"' || data[*i] == '\'')))
			break ;
		expend[j++] = data[(*i)++];
	}
	return (quote_edit(data[*i], &quote, type));
}

static int	quote_edit(char data, int *quote, int type)
{
	if (data == 0)
		*quote = 0;
	return (type);
}

static char	*env_expend(char *expend, char **envp)
{
	char	*tmp;
	int		len;

	if (ft_strncmp(expend, "$", 2) == 0 || ft_strncmp(expend, "\"$\"", 4) == 0)
		return (expend);
	if (ft_strncmp(expend, "$?", 2) == 0)
		return (exit_expend(expend));
	tmp = ft_strjoin(&expend[1], "=");
	if (tmp == 0)
		error_print(errno);
	len = ft_strlen(tmp);
	free(expend);
	while (*envp && ft_strncmp(*envp, tmp, len) != 0)
		envp++;
	free(tmp);
	if (*envp == 0)
		return (NULL);
	expend = ft_strdup(*envp + len);
	if (expend == 0)
		error_print(errno);
	return (expend);
}

static char	*join_expend(char **expend, int j)
{
	char	*toss;
	char	*tmp;
	int		i;

	i = 0;
	if (expend[0])
		toss = ft_strdup(expend[0]);
	else
		toss = ft_strdup("");
	if (toss == 0)
		error_print(errno);
	while (i + 1 < j)
	{
		if (expend[i + 1] != 0)
			tmp = ft_strjoin(toss, expend[i + 1]);
		else
			tmp = ft_strdup(toss);
		free(toss);
		if (tmp == 0)
			error_print(errno);
		toss = tmp;
		i++;
	}
	free_2d_array(expend);
	return (toss);
}
