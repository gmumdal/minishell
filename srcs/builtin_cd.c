/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:27:08 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 13:08:52 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_value(char *dst_env, char *src_env, t_container *con)
{
	int	i;

	i = 0;
	while (con->envp[i] != NULL)
	{
		if (ft_strncmp(dst_env, con->envp[i], ft_strlen(dst_env)) == 0)
		{
			free(con->envp[i]);
			con->envp[i] = ft_strjoin(dst_env, src_env);
			return ;
		}
		i++;
	}
}

char	*get_env_value(char *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(env, envp[i], ft_strlen(env)) == 0)
			return (ft_substr(envp[i], ft_strlen(env), ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

int	set_pwd_oldpwd(t_container *con)
{
	char	*tmp;

	if (get_env_value("OLDPWD=", con->envp) != NULL)
		replace_env_value("OLDPWD=", con->pwd, con);
	tmp = getcwd(NULL, MAXSIZE);
	if (tmp == NULL)
	{
		error_print(errno);
		return (1);
	}
	free(con->pwd);
	con->pwd = tmp;
	if (get_env_value("PWD=", con->envp) != NULL)
		replace_env_value("PWD=", con->pwd, con);
	return (0);
}

int	builtin_cd(char **cmds, t_container *con)
{
	char	*path;
	char	*tmp;
	int		is_error;

	is_error = 0;
	path = cmds[1];
	tmp = getcwd(NULL, MAXSIZE);
	if (tmp == NULL)
	{
		if (errno == ENOENT)
			path = get_env_value("HOME=", con->envp);
		else
		{
			error_print(errno);
			return (1);
		}
	}
	free(tmp);
	if (cmds[1] == NULL)
		path = get_env_value("HOME=", con->envp);
	if (chdir(path) == -1)
		return (print_execute_error("cd", path, strerror(errno)));
	return (set_pwd_oldpwd(con));
}
