/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/02/10 19:31:07 by clala            ###   ########.fr       */
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
	return (new);
}

void		separate_cmd_args(char *s)
{
	char	*space_pos;
	
	char	*cmd;
	char	*args;
	space_pos = ft_strchr(*s, ' ');
	if (!space_pos)
		cmd = *s;
	else
	{
		cmd = ft_strndup(s, space_pos - *s);
		args = ft_strdup(s + 1);
	}
}

int			exec_implemented_commands(t_shell *shell, char *s)
{
	ft_strequ("exit", s) ? do_exit() : 0;
	if (ft_strequ(s, "env") || ft_strequ(s, "setenv ") ||
	ft_strequ(s, "unsetenv "))
		return (do_environ(shell, s));
	if (ft_strequ(s, "echo") && ft_printf("%s\n", s))
		return (1);
	if (ft_strequ(s, "echo ") && do_echo(s))
		return (1);
	if ((ft_strequ(s, "cd") || ft_strnequ(s, "cd ", 3)) && do_cd(shell, s))
		return (1);
	return (0);
}

void		handle_input(char **s)
{
	char	*temp;

	temp = *s;
	*s = ft_strtrim(*s);
	free(temp);
}

int			main(int argc, char **argv, char **env)
{
	char	*s;
	t_shell	*shell;
	char	*splitted;
	int		i;
	
	(void)argv;
	argc > 1 ? exit(0) : 0;
	shell = t_shell_new();

	s = shell->input->buf->s;
	signal (SIGINT, &interrupt); //в функции interrupt надо убить форк запущенного процесса
	parse_system_environ(shell, env);
	while (ft_printf("$> ") && get_next_line(STDIN_FILENO, &s))
	{
		handle_input(s);
		i = 0;
		splitted = ft_strsplit(s, ';');
		while (splitted[i])
		{
			handle_command(splitted[i++]);
		}
		free_2dchararr_terminated(splitted);
		free(s);
	}
	return (0);
}
