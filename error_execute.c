#include "minishell.h"

int	print_execute_error(char *cmd, char *path, char *error_msg)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	return (1);
}

int	print_syntax_error(char *error_char, t_token **head)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error_char, 2);
	ft_putstr_fd("\'\n", 2);
	exit_code = 258;
	ms_tokenclear(head, free);
	return (1);
}

void	error_print(int flag)
{
	ft_putstr_fd("minishell: ", 2);
	if (flag == 2)
		ft_putstr_fd("input: ", 2);
	ft_putstr_fd(strerror(flag), 2);
	ft_putstr_fd("\n", 2);
	if (flag == 126)
		exit(126);
	exit(1);
}

void	print_command_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", 2);
	exit_code = 127;
	exit(127);
}	
