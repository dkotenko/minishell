/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/12 23:24:01 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*t_shell_new(void)
{
	t_shell	*new;

	new = (t_shell *)ft_memalloc(sizeof(t_shell));
	new->env = t_htable_init(
		T_HTABLE_INIT_PRIME_NUMBER, &cmp_func, &hash_func_fnv_1a_32);
	new->input = t_input_new();
	new->allocated = t_dlist_new();
	return (new);
}

void		separate_cmd_args(t_shell *shell, char *s)
{
	t_curr_cmd	cmd;
	char	*space_pos;
	char	*temp;

	//ft_printf("%s\n");
	space_pos = ft_strchr(s, ' ');
	ft_bzero(&cmd, sizeof(t_curr_cmd));
	if (!space_pos)
		cmd.cmd = ft_strdup(s);
	else
	{
		temp = ft_strndup(s, space_pos - s);
		cmd.cmd = ft_strtrim(temp);
		free(temp);
		cmd.args = ft_strtrim(space_pos + 1);
	}
	shell->cmd = cmd;
}
/*
$> echo $ffff
value:

$> echo $d
sega
*/


//cd env - sega

void		clear_cmd_args(t_curr_cmd *cmd)
{
	cmd->args ? free(cmd->args) : 0;
	cmd->cmd ? free(cmd->cmd) : 0;
	ft_bzero(cmd, sizeof(t_curr_cmd));
}
int			main()
{
	char	*s;
	t_shell	*shell;
	char	**splitted;
	int		i;
	char	*temp;
	
	shell = t_shell_new();
	//s = shell->input->buf->s;
	signal (SIGINT, &interrupt); //в функции interrupt надо убить форк запущенного процесса
	//parse_system_environ(shell, env);
	while (ft_printf("$> ") && get_next_line(STDIN_FILENO, &s))
	{
		if (!ft_strlen(s) && ft_free_int(s))
			continue ;
		splitted = ft_strsplit(s, ';');
		free(s);
		i = -1;
		while (splitted[++i])
		{
			temp = ft_strdup(splitted[i]);
			handle_input(shell->allocated, &temp);
			separate_cmd_args(shell, temp);
			//ft_printf("%s ||| %s\n", shell->cmd.cmd, shell->cmd.args);
			exec_command(shell);
			temp ? free(temp) : 0;
		}
		free_2dchararr_terminated(splitted);
		
	}
	return (0);
}
