/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/24 19:43:44 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_input(t_shell *shell, char *buf)
{
	ft_putstr_fd(buf, STDERR_FILENO);
	t_buffer_write(shell->buf, buf);
}

static void	delete_char(t_shell *shell)
{
	if (shell->buf->i > 0)
	{
		tputs(cursor_left, 1, ft_putchar_int);
		tputs(tgetstr("dc", 0), 1, ft_putchar_int);
		t_buffer_pop(shell->buf);
	}
}

static void	history_prev(t_shell *shell)
{
	if (!shell->history->tail)
		return ;
	if (!shell->history_pointer)
		shell->history_pointer = shell->history->tail;
	else if (shell->history_pointer->prev)
		shell->history_pointer = shell->history_pointer->prev;
	tputs(restore_cursor, 1, ft_putchar_int);
	tputs(tigetstr("ed"), 1, ft_putchar_int);
	t_buffer_clean(shell->buf);
	write_input(shell, (char *)shell->history_pointer->data);
}

static void	history_next(t_shell *shell)
{
	if (!shell->history->tail)
		return ;
	if (!shell->history_pointer)
		shell->history_pointer = shell->history->tail;
	else if (shell->history_pointer->next)
		shell->history_pointer = shell->history_pointer->next;
	tputs(restore_cursor, 1, ft_putchar_int);
	tputs(tigetstr("ed"), 1, ft_putchar_int);
	t_buffer_clean(shell->buf);
	write_input(shell, shell->history_pointer->data);
}

void	choose_input_action(t_shell *shell, char *buf)
{
	if (ft_strequ(buf, "\e[A"))
		history_prev(shell);
	else if (ft_strequ(buf, "\e[B"))
		history_next(shell);
	else if (ft_strequ(buf, "\177"))
		delete_char(shell);
	else
		write_input(shell, buf);
}
