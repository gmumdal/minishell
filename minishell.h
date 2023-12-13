/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:53:34 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/13 21:56:51 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>

# define PATH "PATH="
# define BASIC_PATH "/usr/local/bin:/usr/bin:/bin:\
	/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin"
# define CMD_NOT_FOUND_ERR ": command not found\n"
# define HEREDOC "here_doc"

struct sigaction	sig;

typedef struct s_container
{
	struct s_data	*head;
	char			**envp;
	int				cnt;
}	t_container;

typedef struct s_data
{
	char			*infile;
	char			*outfile;
	char			*delimeter;
	char			**cmd_arr;
	int				is_append;
	struct s_data	*next;
}	t_data;

typedef struct s_info
{
	int		pipe_fds[2][2];
	pid_t	last_pid;
	int		infile_fd;
	int		outfile_fd;
	int		idx;
	int		cur;
	int		is_heredoc;
	t_data	*data;
}	t_info;

t_list	*pasing(char *line);
void	split_free(char **command);

int		ms_init(char c, char *s);
int		ms_split_input(char *toss, char **cmd, char *oper);
int		ms_split_first(char *toss, char **cmd, char *oper);
int		ms_split_plus(char *toss, int *i, char **cmd);
char	**ms_split(char *cmd);

/* debug */
void	print_2d_arr(char **s);
void	print_3d_arr(char ***s);
void	print_node(t_list *list);
void	print_data(t_data *data);
void	print_data_node(t_data *data);
void	print_container(t_container *con);

/* init_data */
char	**make_cmd(t_list *list);
int		get_cmd_arr_len(t_list *lst);
t_list	*check_type_and_move_list(t_data *data, t_list *list);
char	***make_cmd_arr(t_data *data, t_list *list);
void	init_data(t_data *data, t_list *list, char **envp);

/* ms_utils1 */
char	**ms_2d_arr_dup(char **s);

/* pipe_parse */
char	*get_path(char **envp);
char	*make_cmd_path(char const *path, char const *cmd);
char	*get_valid_path(char **cmds, char *env_path);
int		execute_cmd(t_info *info);

/* pipe_exit */
void	free_2d_array(char **arr);
void	perror_exit(char *str, int exit_code);

/* pipe_utils */
void	open_pipe(t_info *info);
void	close_pipe(t_info *info);
void	open_file(t_info *info);
void	close_all_pipe(t_info *info);
void	dup2_sub(int first, int second);
void	redirect(t_info *info);

/* pipe */
int		wait_children(t_info *info);
void	init_info(t_info *info, t_data *data);
void	child(t_info *info);
void	here_doc(t_info *info);
int		pipex(t_data *data);

/* data_list */
void	init_data_node(t_data *node);
int		get_cmd_arr_len(t_list *lst);
t_data	*data_lstnew(t_list *line);
t_data	*data_lstlast(t_data *lst);
void	data_lstadd_back(t_data **lst, t_data *new);
t_data	*make_data_list(t_list *line);
int	get_data_list_len(t_data *lst);
void	init_container(t_container *con, t_list *line, char **envp);


#endif