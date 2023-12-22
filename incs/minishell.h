/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:53:34 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/22 13:21:50 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
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
# include <errno.h>

# define MAXSIZE 1024
# define PATH "PATH="
# define BASIC_PATH "/usr/local/bin:/usr/bin:/bin:\
	/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin"
# define CMD_NOT_FOUND_ERR ": command not found\n"
# define ERROR 1

int	g_signal;

typedef struct s_container
{
	struct s_data	*head;
	char			**envp;
	char			*pwd;
	int				cnt;
	int				exit_code;
	struct termios	old_term;
	struct termios	new_term;
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
	int		cnt;
	char	**envp;
	t_data	*data;
}	t_info;

typedef struct s_token
{
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
	int				type;
}	t_token;

/* parsing.c */
t_token	*parsing(char *line, t_container *con);
void	free_2d_array(char **arr);

/* termios.c */
void	save_input_mode(struct termios *old_term);
void	set_input_mode(struct termios *new_term);
void	reset_input_mode(struct termios *old_term);

/* signal.c */
void	ms_sigset(void (*sigint_func)(int), void (*sigquit_func)(int));
void	sig_newline(int signum);

/* ms_split.c */
int		ms_init(char c, char *s);
int		ms_split_input(char *toss, char **cmd, char *oper);
int		ms_split_first(char *toss, char **cmd, char *oper);
int		ms_split_plus(char *toss, int *i, char **cmd);
char	**ms_split(char *cmd);

/* ms_token.c */
t_token	*ms_tokennew(char *data, t_container *con);
void	ms_tokenclear(t_token **token, void (*del)(void *));
int		ms_tokenadd_back(t_token **token, t_token *new);

/* side_utils.c */
int		ft_init(char *s, char *data);
char	*exit_expend(char *expend, t_container *con);
int		check_token(t_token	*head, t_container *con);

/* ms_expend_edit.c */
char	*expend_list(char *data, t_container *con);

/* debug */
void	print_arr(char *s);
void	print_2d_arr(char **s);
void	print_3d_arr(char ***s);
void	print_node(t_token *list);
void	print_data(t_data *data);
void	print_data_node(t_data *data);
void	print_container(t_container *con);
void	print_pwd_oldpwd(t_container *con);

/* init_data */
char	**make_cmd(t_token *list);
int		get_cmd_arr_len(t_token *lst);
t_token	*check_type_and_move_list(t_data *data, t_token *list);
char	***make_cmd_arr(t_data *data, t_token *list);
void	init_data(t_data *data, t_token *list, char **envp);

/* ms_utils1 */
char	**ms_2d_arr_dup(char **s);

/* pipe_parse */
char	*get_path(char **envp);
char	*make_cmd_path(char const *path, char const *cmd);
char	*get_valid_path(char **cmds, char *env_path);
int		execute_cmd(t_info *info, t_container *con);

/* pipe_utils */
void	open_pipe(t_info *info);
void	close_pipe(t_info *info);
void	open_file(t_info *info, t_container *con);
void	close_all_pipe(t_info *info);
void	redirect(t_info *info);
void	check_valid_file(t_token *line, t_data *toss, int *flag);

/* pipe */
int		wait_children(t_info *info, t_container *con);
int		check_exitcode(int wstatus);
void	init_info(t_info *info, t_container *con);
void	child(t_info *info, t_container *con);
int		pipex(t_container *con);

/* heredoc */
int		heredoc(t_data *info, t_container *con, int type);
char	*get_heredoc_tmpfile_name(void);
void	delete_all_heredoc_tmpfile(t_data *head);
void	read_heredoc(t_data *info, t_container *con, int tmpfile_fd, int type);
int		wait_heredoc(t_data *info, int status, t_container *con);

/* heredoc_expend.c */
char	*heredoc_expend(char *data, char **envp);

/* data_list */
t_data	*data_lstnew(t_token *line, t_container *con);
t_data	*data_lstlast(t_data *lst);
int		data_lstadd_back(t_data **lst, t_data *new);
void	data_lstclear(t_data **lst, void (*del)(void *));

/* data_init */
t_data	*make_data_list(t_token *line, t_container *con);
int		init_container(t_container *con, t_token *line);
char	**make_cmd(t_token *list);
void	check_valid_file(t_token *line, t_data *toss, int *flag);
int		check_type_and_dup_data(t_token *line, t_data *toss, t_container *con);

/* data_utils */
void	init_data_node(t_data *node);
int		get_cmd_arr_len(t_token *lst);
int		get_data_list_len(t_data *lst);

/* error_exit */
void	error_print(int flag);
void	print_command_error(char *cmd, t_container *con);
void	print_file_error(char *file, t_container *con);
void	print_execve_error(char *cmd, t_container *con);

/* error_return */
int		print_execute_error(char *cmd, char *path, char *error_msg);
int		print_syntax_error(char *error_char, t_token **head, t_container *con);

/* builtin_execute */
int		check_builtin(char *s);
int		execute_builtin(char **cmds, t_container *con, int flag);
void	redirect_and_open_file(t_container *con, int *in_fd, int *out_fd);
int		execute_builtin_one_case(t_container *con);

/* builtin_cd */
char	*get_env_value(char *env, char **envp);
int		builtin_cd(char **cmds, t_container *con);

/* builtin_unset */
int		builtin_unset(char	**cmds, t_container *con);
int		check_identifier(char *cmd);
char	**sub_env(t_container *con, char *cmd);

/* bulitin_exit */
int		builtin_exit(char **cmds, int flag);
int		builtin_echo(char **cmds);

/* bulitin_export */
int		builtin_export(char **cmds, t_container *con);

/* builtin_env */
int		builtin_env(char **s);

/* main */
void	ms_readline(t_container *con, char *line);
void	pre_init_container(t_container *con, char **envp);
int		init_container(t_container *con, t_token *line);
void	line_clear(t_token **token, t_container *con);

/* common_utils */
int		get_2d_arr_len(char	**s);
int		check_empty(char *s);

#endif
