/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:27:38 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 08:03:23 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier(char *cmd)
{
	int	i;

	if (ft_isdigit(cmd[0]) == 1 || cmd[0] == '\0')
		return (1);
	i = -1;
	while (cmd[++i] != '\0')
	{
		if (ft_isalnum(cmd[i]) == 1 || cmd[i] == '#')
			continue ;
		return (1);
	}
	return (0);
}

int	builtin_unset(char **cmds, t_container *con)
{
	int	i;

	i = 0;
	if (cmds[1] == NULL)
		return (0);
	while (cmds[++i] != NULL)
	{
		if (check_identifier(cmds[i]) != 0)
			return (print_execute_error("unset", cmds[i],
					"not a valid identifier"));
		con->envp = sub_env(con, cmds[i]);
	}
	return (0);
}

char	**sub_env(t_container *con, char *cmd)
{
	char	**ret;
	int		envp_idx;
	int		ret_idx;

	ret = (char **)ft_calloc(sizeof(char *), get_2d_arr_len(con->envp) + 1);
	envp_idx = 0;
	ret_idx = 0;
	while (con->envp[envp_idx] != NULL)
	{
		if (ft_strncmp(con->envp[envp_idx], cmd, ft_strlen(cmd)) == 0)
		{
			free(con->envp[envp_idx++]);
			continue ;
		}
		ret[ret_idx++] = con->envp[envp_idx++];
	}
	free(con->envp);
	return (ret);
}
