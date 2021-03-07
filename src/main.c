/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/07 19:45:33 by clala            ###   ########.fr       */
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

void		separate_cmd_args(t_shell *shell, char *s)
{
	t_curr_cmd	cmd;
	char	*space_pos;

	space_pos = ft_strchr(s, ' ');
	ft_bzero(&cmd, sizeof(t_curr_cmd));
	if (!space_pos)
		cmd.cmd = s;
	else
	{
		cmd.cmd = ft_strndup(s, space_pos - s);
		cmd.args = ft_strdup(space_pos + 1);
	}
	shell->cmd = cmd;
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
	char	**splitted;
	int		i;
	
	(void)argv;
	argc > 1 ? exit(0) : 0;
	shell = t_shell_new();
	s = shell->input->buf->s;
	signal (SIGINT, &interrupt); //в функции interrupt надо убить форк запущенного процесса
	parse_system_environ(shell, env);
	while (ft_printf("$> ") && get_next_line(STDIN_FILENO, &s))
	{
		handle_input(&s);
		i = 0;
		splitted = ft_strsplit(s, ';');
		while (splitted[i])
		{
			separate_cmd_args(shell, splitted[i++]);
			//ft_printf("%s ||| %s\n", shell->curr_cmd.cmd, shell->curr_cmd.args);
			exec_implemented_commands(shell);
		}
		splitted ? free_2dchararr_terminated(splitted) : 0;
		free(s);
	}
	return (0);
}
