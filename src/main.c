/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/13 12:30:59 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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


int			main()
{
	t_shell	*shell;
	char	**splitted;
	int		i;
	char	*temp;
	char	*s;

	shell = t_shell_new();
	//s = shell->input->buf->s;
	signal (SIGINT, &interrupt); //в функции interrupt надо убить форк запущенного процесса
	//parse_system_environ(shell, env);
	s = shell->s;
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
			handle_input(shell, shell->allocated, &temp);
			separate_cmd_args(shell, temp);
			//ft_printf("%s ||| %s\n", shell->cmd.cmd, shell->cmd.args);
			exec_command(shell);
			temp ? free(temp) : 0;
		}
		free_2dchararr_terminated(splitted);
		
	}
	return (0);
}
