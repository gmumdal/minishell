#include "minishell.h"

char	**ms_2d_arr_dup(char **s)
{
	char	**result;
	int		len;
	int		i;

	len = 0;
	while (s[len] != NULL)
		len++;
	result = (char **)ft_calloc((len + 1), sizeof(char *));
	i = 0;
	while (i < len)
	{
		result[i] = ft_strdup(s[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
