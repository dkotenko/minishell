/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/02/06 21:19:46 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# define CHAR_BUFF_SIZE 1
char				ft_getchar()
{
	return (0);
}



void				handle_input(t_shell *shell)
{
	char			s[CHAR_BUFF_SIZE + 1];   
	struct termios	oldt;
	struct termios	newt;

	(void)shell;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO | ECHOE);
	//newt.c_lflag &= (~ICANON & ~ECHO & ~ECHOE);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	s[CHAR_BUFF_SIZE] = '\0';
	while((s[0] = t_buffer_getchar(shell->input->buf)))
	{
		ft_putchar(shell->input->buf->s[shell->input->buf->i - 1]);
		t_buffer_write(shell->input->buf, s);
		if (s[0] == '\n')
			break ;
	}
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}
