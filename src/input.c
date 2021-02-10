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

t_input		*t_input_new(void)
{
	t_input	*new;
	t_dlist	*tokens;

	new = (t_input *)ft_memalloc(sizeof(t_input));
	new->cmd = t_dlist_new();
	new->buf = t_buffer_create(0);
	tokens = t_dlist_new();
	t_dlist_append(new->cmd, t_dlist_node_new(tokens, sizeof(t_dlist *)));
	t_dlist_append(tokens, t_dlist_node_new(t_buf_create(0), sizeof(t_buf *)));
	return (new);
}


void				handle_input(t_shell *shell)
{
	char			c;   
	struct termios	oldt;
	struct termios	newt;

	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO | ECHOE);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	c = 0;
	while((c = t_buffer_getchar(shell->input->buf)))
	{
		//c = shell->input->buf->s[shell->input->buf->i - 1];
		ft_putchar(c);
		if (c == '\n')
			break ;
		
	}
	//ft_printf("%s\n", shell->input->buf->s);
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}
