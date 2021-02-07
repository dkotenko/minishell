/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/02/06 23:57:53 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				ft_getchar()
{
	return (0);
}



void				handle_input(t_shell *shell)
{
	char			s[CHAR_BUFF_SIZE + 1];   
	struct termios	oldt;
	struct termios	newt;
	char			c;

	(void)shell;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO | ECHOE);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	s[CHAR_BUFF_SIZE] = '\0';
	while((s[0] = t_buffer_getchar(shell->input->buf)))
	{
		c = shell->input->buf->s[shell->input->buf->i - 1];
		ft_putchar(c);
		if (c == '\n')
			break ;
		
	}
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}
