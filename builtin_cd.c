#include "minishell.h"

void	set_pwd_and_oldpwd(t_container *con)
{
	char	*cur_pwd;
	char	*old_pwd;
	char	*tmp;

	tmp = malloc(sizeof(char) * MAXSIZE);
	if (getcwd(tmp, MAXSIZE) == -1)
		con->tmp_pwd;
	cur_pwd = ft_strjoin("PWD=", getcwd(tmp, MAXSIZE));
	old_pwd = ft_strjoin("OLDPWD=", find_value("PWD", ));
	check_export(cur_pwd, );
	check_export(old_pwd, );
	free(cur_pwd);
	free(old_pwd);
}

void	builtin_cd(char **cmds, t_container *con)
{
	char	*path;
	char	*tmp;
	int		is_error;

	path = NULL;
	is_error = 0;
	if (cmds[1] == NULL || (cmds[1][0] == '~' && cmds[1][1] == '\0'))
		cd_home(path, cmds, con);
	else
	{
		path = cmds[1];
		if (chdir(path) == -1)
			is_error = print_execute_error("cd", path, strerror(errno));
		tmp = ft_strjoin();
		set_pwd_and_oldpwd(con);
	}
}
