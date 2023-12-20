/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:27:54 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/20 19:32:11 by jongmlee         ###   ########.fr       */
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
	ret_tmp = malloc((ft_strlen(path) + ft_strlen(cmd) + 2) * sizeof(char));
	if (ret_tmp == NULL)
		perror_exit("malloc()", 1);
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

	if (env_path == NULL)
		exit(1);
	paths = ft_split(env_path, ':');
	if (paths == NULL)
		perror_exit("malloc()", 1);
	free(env_path);
	i = -1;
	while (paths[++i] != NULL)
	{
		cmd_path = make_cmd_path(paths[i], cmds[0]);
		if (cmd_path == NULL)
			exit(1);
		if (access(cmd_path, X_OK) == 0)
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
	if (check_builtin(cmds[0]) == 0)
	{
		execute_builtin(cmds, con);
		exit(exit_code);
	}
	env_path = get_env_path(info->envp);
	if (env_path == NULL)
		env_path = ft_strdup(BASIC_PATH);
	cmds = info->data->cmd_arr;
	if (access(cmds[0], X_OK) == 0 && ft_strchr(cmds[0], '/') != 0)
		valid_path = cmds[0];
	else
		valid_path = get_valid_path(cmds, env_path);
	if (valid_path == NULL)
	{
		ft_putstr_fd(ft_strjoin("minishell: ", cmds[0]), 2);
		ft_putstr_fd(CMD_NOT_FOUND_ERR, 2);
		exit_code = 127;
		exit(exit_code);
	}
	return (execve(valid_path, cmds, info->envp));
}
