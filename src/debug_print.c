/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_command(t_dlist *cmd)
{
	t_dlist_node *temp;

	ft_printf("==== command start ====\n");
	temp = cmd->head;
	while (temp)
	{
		print_token((t_buffer *)temp->data);
		temp = temp->next;
	}
	ft_printf("===== command end =====\n");
}

void		print_commands(t_shell *shell)
{
	t_dlist_node *temp;

	temp = shell->input->cmd->head;
	while (temp)
	{
		print_command(temp->data);
		temp = temp->next;
	}
}

void		print_token(t_buffer *token)
{
	if (token->s)
		ft_printf("token:%s\n", token->s);
	else
	{
		ft_printf("Uninitiated string:%s\n", token->s);
	}
	
}
