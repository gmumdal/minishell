#include "minishell.h"

void	print_arr(char *s)
{
	if (s == NULL)
		printf("널인디용\n");
	printf("\n====print_arr====\n");
		printf("s -> %s\n", s);
}

void	print_2d_arr(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
		printf("널인디용\n");
	printf("\n====print_2d_arr====\n");
	while (s[i] != NULL)
	{
		printf("s[%d] -> %s\n", i, s[i]);
		i++;
	}
	printf("s[%d] -> %s\n\n", i, s[i]);
}

void	print_3d_arr(char ***s)
{
	if (s == NULL)
		printf("널인디용\n");
	printf("\n====print_3d_arr====\n");
	int i = 0;
	while (s[i] != NULL)
	{
		int j = 0;
		while (s[i][j] != NULL)
		{
			printf("s[%d][%d] -> %s\n", i, j, s[i][j]);
			j++;
		}
		printf("s[%d][%d] -> %s\n", i, j, s[i][j]);
		printf("\n");
		i++;
	}
}

void	print_node(t_token *list)
{
	printf("\n====print_node====\n");
	while (list != NULL)
	{
		printf("list->data -> %s\n", list->data);
		printf("list->type -> %d\n\n", list->type);
		list = list->next;
	}
}

void	print_data_node(t_data *data)
{
	printf("infile -> %s\n", data->infile);
	printf("outfile -> %s\n", data->outfile);
	printf("delimeter -> %s\n", data->delimeter);
	printf("data->is_append -> %d\n", data->is_append);
	print_2d_arr(data->cmd_arr);
}

void	print_data(t_data *data)
{
	print_data_node(data);
	while (data->next != NULL)
	{
		data = data->next;
		print_data_node(data);
	}
}

void	print_container(t_container *con)
{
	printf("con->cnt -> %d\n", con->cnt);
	print_data(con->head);
}

void	print_pwd_oldpwd(t_container *con)
{
	printf("\ncon->pwd : %s\n", con->pwd);
	printf("$PWD : %s\n", get_env_value("PWD=", con->envp));
	printf("$OLDPWD : %s\n\n", get_env_value("OLDPWD=", con->envp));
}