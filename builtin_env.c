#include "minishell.h"

void	builtin_env(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		printf("%s\n", s[i]);
		i++;
	}
}