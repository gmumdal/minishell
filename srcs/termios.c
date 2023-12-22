/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:37:31 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/20 16:06:04 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_input_mode(struct termios *old_term)
{
	tcgetattr(STDIN_FILENO, old_term);
}

void	set_input_mode(struct termios *new_term)
{
	tcgetattr(STDIN_FILENO, new_term);
	new_term->c_lflag &= ~(ECHOCTL);
	new_term->c_cc[VMIN] = 1;
	new_term->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, new_term);
}

void	reset_input_mode(struct termios *old_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, old_term);
}
