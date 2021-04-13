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

static char	**cmd_to_argv(t_curr_cmd *cmd)
{
	char	**argv;
	char	**args;
	int		len;
	int		i;

	if (!cmd->cmd)
		return (NULL);
	args = ft_strsplit(cmd->args, ' ');
	len = len_2dchararr_terminated(args);
	argv = (char **)ft_memalloc(sizeof(char *) * (len + 1 + 1));
	argv[0] = ft_strdup(cmd->cmd);
	i = 0;
	while (cmd->args && args[i])
	{
		argv[1 + i] = ft_strdup(args[i]);
		i++;
	}
	free_2dchararr_terminated(args);
	return (argv);
}


char	**get_argv(t_shell *shell, t_curr_cmd *cmd)
{
	char	**argv;

	argv = cmd_to_argv(cmd);
	if (cmd->cmd[0] != '/')
	{
		free(argv[0]);
		argv[0] = get_program_path(shell, cmd->cmd);
	}
	return (argv);
}
