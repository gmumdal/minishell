#include "minishell.h"

int	check_builtin(char *s)
{
	if (ft_strncmp(s, "cd", 3) == 0 || ft_strncmp(s, "echo", 5) == 0
	|| ft_strncmp(s, "pwd", 4) == 0 || ft_strncmp(s, "env", 4) == 0
	|| ft_strncmp(s, "unset", 6) == 0 || ft_strncmp(s, "exit", 5) == 0
	|| ft_strncmp(s, "export", 7) == 0)
		return (0);
	return (1);
}

void	execute_builtin(char **cmds, t_container *con)
{
	if (ft_strncmp(cmds[0], "cd", 3) == 0)
		builtin_cd(cmds, con);
	else if (ft_strncmp(cmds[0], "pwd", 4) == 0)
		printf("%s\n", con->pwd);
	else if (ft_strncmp(cmds[0], "unset", 6) == 0)
		builtin_unset(cmds, con);
}

int	get_2d_arr_len(char	**s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}
