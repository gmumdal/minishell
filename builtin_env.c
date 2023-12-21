#include "minishell.h"

int	builtin_env(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		printf("%s\n", s[i]);
		i++;
	}
	return (0);
}
