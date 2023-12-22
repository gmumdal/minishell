/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expend_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:18:05 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 12:57:03 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_expend(char *expend, char *data, int *i, int type);
static int	quote_edit(char c, int *quote, int type);
static char	*env_expend(char *expend, t_container *con);
static char	*join_expend(char **expend, int j);

char	*expend_list(char *data, t_container *con)
{
	char	**expend;
	int		i;
	int		j;

	i = 0;
	j = 0;
	expend = (char **)ft_calloc(ft_strlen(data) + 1, sizeof(char *));
	while (data[i])
	{
		expend[j] = (char *)ft_calloc(ft_strlen(data) + 1, sizeof(char));
		if (make_expend(expend[j], data, &i, 0) == 1)
			expend[j] = env_expend(expend[j], con);
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
		if (quote == 0 && type == 0 && (data[*i] == '\'' || data[*i] == '\"'))
			quote = 1 * (data[*i] == '\'') + 2 * (data[*i] == '\"');
		if ((quote == 0 || quote == 2) && data[*i] == '$' && j > 0)
			break ;
		if ((quote == 0 || quote == 2) && data[*i] == '$' && j == 0)
			type = 1;
		if (type == 0 && j > 0 && ((quote == 1 && data[*i] == '\'')
				|| (quote == 2 && data[*i] == '\"')))
			quote = 0;
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

static char	*env_expend(char *expend, t_container *con)
{
	char	*tmp;
	int		len;
	int		index;

	if (ft_strncmp(expend, "$", 2) == 0 || ft_strncmp(expend, "\"$\"", 4) == 0)
		return (expend);
	if (ft_strncmp(expend, "$?", 2) == 0)
		return (exit_expend(expend, con));
	tmp = ft_strjoin(&expend[1], "=");
	len = ft_strlen(tmp);
	free(expend);
	index = 0;
	while (con->envp[index] && ft_strncmp(con->envp[index], tmp, len) != 0)
		index++;
	free(tmp);
	if (con->envp[index] == 0)
		return (NULL);
	expend = ft_strdup(con->envp[index] + len);
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
		toss = 0;
	while (i + 1 < j)
	{
		if (expend[i + 1] != 0)
			tmp = ft_strjoin(toss, expend[i + 1]);
		else
			tmp = ft_strdup(toss);
		free(toss);
		toss = tmp;
		i++;
	}
	free_2d_array(expend);
	return (toss);
}
