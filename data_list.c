#include "minishell.h"

void	init_data_node(t_data *node)
{
	node->infile = NULL;
	node->outfile = NULL;
	node->delimeter = NULL;
	node->cmd_arr = NULL;
	node->is_append = 0;
	node->next = NULL;
}

int		get_cmd_arr_len(t_list *lst)
{
	int	len;

	len = 0;
	while (lst->type != -5)
	{
		if (lst->type == 0)
			len++;
		lst = lst->next;
	}
	return (len);
}

char	**make_cmd(t_list *list)
{
	t_list 	*tmp;
	int		i;
	int		len;
	char	**cmd;

	tmp = list;
	len = 0;
	while (tmp != NULL && tmp->type != -5)
	{
		if (tmp->type == 0)
			len++;
		tmp = tmp->next;
	}
	cmd = (char **)malloc((len + 1) * sizeof(char *));
	if (cmd == NULL)
		exit(1); // TODO: error handling
	i = 0;
	while (i < len)
	{
		if (list->type == 0)
			cmd[i++] = ft_strdup(list->data);
		list = list->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_data	*data_lstnew(t_list *line)
{
	t_data	*toss;

	if (line == NULL)
		return (NULL);
	toss = (t_data *)malloc(sizeof(t_data));
	if (toss == NULL)
		exit(1);
	init_data_node(toss);
	print_node(line);
	toss->cmd_arr = make_cmd(line);
	while (line != NULL && line->type != -5)
	{
		if (line->type == 1 || line->type == 2)
		{
			toss->outfile = ft_strdup(line->data);
			if (line->type == 2)
				toss->is_append = 1;
		}
		else if (line->type == 3)
			toss->infile = ft_strdup(line->data);
		else if (line->type == 4)
			toss->delimeter = ft_strdup(line->data);
		line = line->next;
	}
	return (toss);
}

t_data	*data_lstlast(t_data *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	data_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*cur;
	
	if (lst == NULL || new == NULL)
		return ;
	if (*lst != NULL)
	{
		cur = data_lstlast(*lst);
		cur->next = new;
	}
	else
		*lst = new;
}

t_data	*make_data_list(t_list *line)
{
	t_data	*head;

	head = data_lstnew(line);
	while (line != NULL && line->type != -5)
		line = line->next;
	if (line != NULL)
			line = line->next;
	while (line != NULL)
	{
		data_lstadd_back(&head, data_lstnew(line));
		while (line != NULL && line->type != -5)
			line = line->next;
		if (line != NULL)
			line = line->next;
	}
	return (head);
}

int	get_data_list_len(t_data *lst)
{
	int	len;

	len = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

void	init_container(t_container *con, t_list *line, char **envp)
{
	con->head = make_data_list(line);
	con->envp = ms_2d_arr_dup(envp);
	con->cnt = get_data_list_len(con->head);
}
