/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:52:25 by jongmlee          #+#    #+#             */
/*   Updated: 2023/12/22 09:55:57 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
