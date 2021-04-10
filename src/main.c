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

int			handle_every_command(t_shell *shell, char **splitted)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (splitted[++i])
	{	
		temp = ft_strdup(splitted[i]);
		handle_input(shell, shell->allocated, &temp);
		if (temp && temp[0])
		{
			separate_cmd_args(shell, temp);
			exec_command(shell);
		}
		temp ? free(temp) : 0;
		temp = NULL;
	}
	return (1);
}

int			main()
{
	t_shell	*shell;
	char	**splitted;
	char	*s;

	shell = t_shell_new();
	signal (SIGINT, &interrupt); //в функции interrupt надо убить форк запущенного процесса
	s = shell->s;
	while (ft_printf("$> ") && get_next_line(STDIN_FILENO, &s))
	{
		if (!ft_strlen(s) && ft_free_int(s))
			continue ;
		splitted = ft_strsplit(s, ';');
		free(s);
		handle_every_command(shell, splitted);
		free_2dchararr_terminated(splitted);
	}
	exit(0);
	return (0);
}

/*
doesnt work:
/bin/ls

$> echo "it works"
"it works"

$> echo it works
it works



