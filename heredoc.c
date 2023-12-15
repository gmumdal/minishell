#include "minishell.h"

void	heredoc(t_data *info)
{
	char	*line;
	int		tmpfile_fd;

	info->infile = get_heredoc_tmpfile_name();
	tmpfile_fd = open(info->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmpfile_fd < 0)
		perror_exit("open()", 1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(info->delimeter, line, ft_strlen(info->delimeter))
			&& ft_strlen(info->delimeter) == (ft_strlen(line)))
			break ;
		write(tmpfile_fd, line, ft_strlen(line));
		write(tmpfile_fd, "\n", 1);
		free(line);
	}
	free(line);
	close(tmpfile_fd);
}

char	*get_heredoc_tmpfile_name(void)
{
	int 	tmp_num;
	char	*tmp;

	tmp_num = INT32_MIN;
	while (tmp_num <= INT32_MAX)
	{
		tmp = ft_itoa(tmp_num);
		if (access(tmp, F_OK) == -1)
			return (tmp);
		free(tmp);
		tmp_num++;
	}
	return (NULL);
}

void	delete_all_heredoc_tmpfile(t_data *head)
{
	while (head != NULL)
	{
		if (head->delimeter != NULL)
			unlink(head->infile);
		head = head->next;
	}
}
