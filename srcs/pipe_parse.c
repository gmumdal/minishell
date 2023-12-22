/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:27:54 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/22 13:51:35 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], PATH, 5) == 0)
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (NULL);
}

char	*make_cmd_path(char const *path, char const *cmd)
{
	char	*ret_str;
	char	*ret_tmp;

	if (path == NULL && cmd == NULL)
		return (NULL);
	ret_tmp = ft_calloc((ft_strlen(path) + ft_strlen(cmd) + 2), sizeof(char));
	ret_str = ret_tmp;
	while (*path != '\0')
	{
		*ret_tmp = *path;
		ret_tmp++;
		path++;
	}
	*ret_tmp = '/';
	ret_tmp++;
	while (*cmd != '\0')
	{
		*ret_tmp = *cmd;
		ret_tmp++;
		cmd++;
	}
	*ret_tmp = '\0';
	return (ret_str);
}

char	*get_valid_path(char **cmds, char *env_path)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	if (cmds[0][0] == 0)
		return (NULL);
	if (env_path == NULL)
		exit(1);
	paths = ft_split(env_path, ':');
	free(env_path);
	i = -1;
	while (paths[++i] != NULL)
	{
		cmd_path = make_cmd_path(paths[i], cmds[0]);
		if (cmd_path == NULL)
			exit(1);
		if (access(cmd_path, F_OK) == 0)
		{
			free_2d_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_2d_array(paths);
	return (NULL);
}

int	execute_cmd(t_info *info, t_container *con)
{
	char	**cmds;
	char	*env_path;
	char	*valid_path;

	cmds = info->data->cmd_arr;
	if (cmds[0] == NULL)
		exit(0);
	if (check_builtin(cmds[0]) == 0)
		exit(execute_builtin(cmds, con, 1));
	env_path = get_env_path(info->envp);
	if (env_path == NULL)
		env_path = ft_strdup(BASIC_PATH);
	cmds = info->data->cmd_arr;
	if (access(cmds[0], F_OK) == 0 && ft_strchr(cmds[0], '/') == 0)
		valid_path = get_valid_path(cmds, env_path);
	else if (access(cmds[0], F_OK) == 0 && ft_strchr(cmds[0], '/') != 0)
		valid_path = cmds[0];
	else
		valid_path = get_valid_path(cmds, env_path);
	if (valid_path == NULL)
		print_command_error(cmds[0], con);
	if (execve(valid_path, cmds, info->envp) == -1)
		print_execve_error(cmds[0], con);
	return (0);
}
