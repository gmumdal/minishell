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
	int		envp_idx;
	int		ret_idx;
	char	**ret;

	if (check_identifier(cmds[1]) != 0)
	{
		print_execute_error("unset", cmds[1], "not a valid identifier");
		return (1);
	}
	ret = (char **)ft_calloc(sizeof(char *), get_2d_arr_len(con->envp));
	envp_idx = 0;
	ret_idx = 0;
	while (con->envp[envp_idx] != NULL)
	{
		if (ft_strncmp(con->envp[envp_idx], cmds[1], ft_strlen(cmds[1])) == 0)
		{
			free(con->envp[envp_idx++]);
			continue ;
		}
		ret[ret_idx++] = con->envp[envp_idx++];
	}
	free(con->envp);
	con->envp = ret;
	return (0);
}
