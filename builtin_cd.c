#include "minishell.h"

int	builtin_cd(char **cmds, t_container *con)
{
	char	*path;
	char	*tmp;
	int		is_error;

	is_error = 0;
	tmp = (char *)malloc(sizeof(char) * MAXSIZE);
	if (tmp == NULL)
		perror_exit("malloc()", 1);
	path = cmds[1];
	if (getcwd(tmp, MAXSIZE) == NULL)
	{
		if (errno == ENOENT)
			path = find_env_value("HOME=", con->envp);
		else
			error_print(errno);
		return (1);
	}
	//if (cmds[1] == NULL)
	//	cd_home(path, cmds, con);
	//else
	//{
	if (chdir(path) == -1)
		is_error = print_execute_error("cd", path, strerror(errno));
	else
	{
		free(con->old_pwd);
		con->old_pwd = con->pwd;
		if (find_env_value("OLDPWD=", con->envp) != NULL)
			replace_env_value("OLDPWD=", con->old_pwd, con);
		if (getcwd(tmp, MAXSIZE) == NULL)
		{
			error_print(errno);
			return (1);
		}
		free(con->pwd);
		con->pwd = tmp;
		if (find_env_value("PWD=", con->envp) != NULL)
			replace_env_value("PWD=", con->pwd, con);
	}
}
