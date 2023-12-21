#include "minishell.h"

char	**add_env(char *var_name, char *var, t_container *con)
{
	char	**ret;
	int		flag;
	int		i;

	ret = (char **)ft_calloc(sizeof(char *), get_2d_arr_len(con->envp) + 2);
	flag = 0;
	i = -1;
	while (con->envp[++i] != NULL)
	{
		ret[i] = con->envp[i];
		if (ft_strncmp(ret[i], var, ft_strlen(var_name) + 1) == 0 && flag == 0)
		{
			free(ret[i]);
			ret[i] = ft_strdup(var);
			flag = 1;
		}
	}
	if (flag == 0)
		ret[i] = ft_strdup(var);
	return (ret);
}

int	builtin_export(char **cmds, t_container *con)
{
	char	*var_name;
	char	**ret;

	if (cmds[1] == NULL)
	{
		builtin_env(con->envp);
		return (0);
	}
	var_name = ft_substr(cmds[1], 0, ft_strchr(cmds[1], '=') - cmds[1]);
	if (check_identifier(var_name) != 0)
	{
		free(var_name);
		print_execute_error("export", cmds[1], "not a valid identifier");
		return (1);
	}
	ret = add_env(var_name, cmds[1], con);
	free(var_name);
	free(con->envp);
	con->envp = ret;
	return (0);
}
