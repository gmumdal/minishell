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

int	get_cmd_arr_len(t_token *lst)
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

char	**make_cmd(t_token *list)
{
	t_token	*tmp;
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
	cmd = (char **)ft_calloc((len + 1), sizeof(char *));
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

void	check_valid_file(t_token *line, t_data *toss, int *flag)
{
	int	fd;

	fd = 0;
	if (*flag == 0 && (line->type == 1 || line->type == 2))
	{
		fd = open(line->data, O_CREAT | O_WRONLY, 0644);
		free(toss->outfile);
		toss->outfile = ft_strdup(line->data);
		if (fd == -1)
			*flag = 1;
		if (line->type == 2)
			toss->is_append = 1;
	}
	else if (line->type == 3 && *flag == 0)
	{
		fd = open(line->data, O_RDONLY);
		free(toss->infile);
		toss->infile = ft_strdup(line->data);
		if (fd == -1)
			*flag = 1;
	}
	close(fd);
}

int	check_type_and_dup_data(t_token *line, t_data *toss, t_container *con)
{
	int	flag;

	flag = 0;
	while (line != NULL && line->type != -5)
	{
		if (line->type == 1 || line->type == 2 || line->type == 3)
			check_valid_file(line, toss, &flag);
		else if (line->type == 4 || line->type == 5)
		{
			toss->delimeter = ft_strdup(line->data);
			toss->infile = get_heredoc_tmpfile_name();
			if (heredoc(toss, con, line->type) == 0)
				return (0);
		}
		line = line->next;
	}
	return (1);
}

t_data	*data_lstnew(t_token *line, t_container *con)
{
	t_data	*toss;

	if (line == NULL)
		return (NULL);
	toss = (t_data *)ft_calloc(1, sizeof(t_data));
	init_data_node(toss);
	toss->cmd_arr = make_cmd(line);
	if (check_type_and_dup_data(line, toss, con) == 0)
	{
		free_2d_array(toss->cmd_arr);
		free(toss->infile);
		free(toss->outfile);
		free(toss->delimeter);
		free(toss);
		return (0);
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

int	data_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*cur;

	if (lst == NULL || new == NULL)
		return (0);
	if (*lst != NULL)
	{
		cur = data_lstlast(*lst);
		cur->next = new;
	}
	else
		*lst = new;
	return (1);
}

void	data_lstclear(t_data **lst, void (*del)(void *))
{
	t_data	*cur;

	if (lst == 0 || del == 0)
		return ;
	while (*lst != NULL)
	{
		cur = *lst;
		*lst = (*lst)->next;
		free_2d_array(cur->cmd_arr);
		free(cur->delimeter);
		free(cur->infile);
		free(cur->outfile);
		free(cur);
	}
	*lst = 0;
}

t_data	*make_data_list(t_token *line, t_container *con)
{
	t_data	*head;

	head = data_lstnew(line, con);
	if (head == 0)
		return (0);
	while (line != NULL && line->type != -5)
		line = line->next;
	if (line != NULL)
		line = line->next;
	while (line != NULL)
	{
		if (data_lstadd_back(&head, data_lstnew(line, con)) == 0)
		{
			data_lstclear(&head, free);
			return (0);
		}
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

int	init_container(t_container *con, t_token *line)
{
	con->head = make_data_list(line, con);
	if (con->head == 0)
	{
		ms_tokenclear(&line, free);
		return (0);
	}
	con->cnt = get_data_list_len(con->head);
	return (1);
}
