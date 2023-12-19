#include "minishell.h"

int	check_builtin(char *s)
{
	if (!ft_strncmp(s, "cd", 3) || !ft_strncmp(s, "echo", 5)
	|| !ft_strncmp(s, "pwd", 4) || !ft_strncmp(s, "env", 4)
	|| !ft_strncmp(s, "unset", 6) || !ft_strncmp(s, "exit", 5)
	|| !ft_strncmp(s, "export", 7))
		return (0);
	return (1);
}

int	execute_builtin(char **cmds, t_container *con)
{
	if (!ft_strncmp(cmds[0], "cd", 3))
		return (builtin_cd(cmds, con));
	return (0);
}