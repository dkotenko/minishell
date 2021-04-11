/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/11 13:36:57 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_dlist *cmd)
{
	t_dlist	*tokens;

	tokens = t_dlist_new();
	t_dlist_append(cmd, t_dlist_node_new(tokens, sizeof(t_dlist *)));
	t_dlist_append(tokens,
		t_dlist_node_new(t_buffer_create(0), sizeof(t_buf *)));
}

void	clear_cmd_args(t_curr_cmd *cmd)
{
	ft_free_int(cmd->args);
	ft_free_int(cmd->cmd);
	ft_bzero(cmd, sizeof(t_curr_cmd));
}

char	**get_argv(t_curr_cmd *cmd)
{
	char	**argv;

	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = ft_strdup(cmd->cmd);
	if (cmd->args)
		argv[1] = ft_strdup(cmd->args);
	return (argv);
}
