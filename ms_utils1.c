#include "minishell.h"

char	**ms_2d_arr_dup(char **s)
{
	char	**result;
	int		len;
	int		i;

	len = 0;
	while (s[len] != NULL)
		len++;
	result = (char **)malloc((len + 1) * sizeof(char *));
	if (result == NULL)
		exit(1); // TODO: error handling
	i = 0;
	while (i < len)
	{
		result[i] = ft_strdup(s[i]);
		if (result[i] == NULL)
			exit(1); // TODO: error handling
		i++;
	}
	result[i] = NULL;
	return (result);
}
