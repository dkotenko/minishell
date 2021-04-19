/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/16 23:39:02 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal_chlid(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		signal(SIGINT, signal_handler);
		t_buffer_clean(g_shell->buf);
	}
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n%s ", PROMPT);
		t_buffer_clean(g_shell->buf);
	}
	else
		ft_printf("\n%s ", PROMPT);
}
