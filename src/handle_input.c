/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/24 19:45:18 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_input(char *buf)
{
	int	c;

	ft_memset(buf, 0, BUFF_SIZE + 1);
	c = read(STDIN_FILENO, buf, BUFF_SIZE);
	if (c < 0)
		handle_error("Can't read STDIN");
	buf[c] = 0;
	return (c);
}

int	ft_putchar_int(int c)
{
	ft_putchar(c);
	return (c);
}

static void	set_terminal(struct termios *oldt, struct termios *newt)
{
	tcgetattr(STDIN_FILENO, oldt);
	*newt = *oldt;
	newt->c_lflag &= ~(ICANON | ECHO | ECHOE);
	tcsetattr(STDIN_FILENO, TCSANOW, newt);
	tgetent(0, MAINTERM);
	tputs(save_cursor, 1, ft_putchar_int);
}

void	handle_input_buf(t_shell *shell)
{
	char			c;
	struct termios	oldt;
	struct termios	newt;
	char			buf[BUFF_SIZE + 1];

	set_terminal(&oldt, &newt);
	c = read_input(buf);
	while (c)
	{
		choose_input_action(shell, buf);
		if (ft_strequ(buf, "\n"))
			break ;
		c = read_input(buf);
	}
	t_dlist_append(shell->history, \
		t_dlist_node_new(ft_strtrim(shell->buf->s), sizeof(char *)));
	shell->history_pointer = NULL;
	if (ft_strequ(buf, "\n"))
		t_buffer_pop(shell->buf);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
