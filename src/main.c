/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/24 19:42:56 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_3_strings(char *s1, char *s2, char *s3)
{
	char		*joined;
	int			len_1;
	int			len_2;
	int			len_3;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	len_3 = ft_strlen(s3);
	joined = ft_strnew(len_1 + len_2 + len_3);
	ft_strcpy(joined, s1);
	ft_strcat(joined + len_1, s2);
	ft_strcat(joined + len_2, s3);
	return (joined);
}

void	separate_cmd_args(t_shell *shell, char *s)
{
	t_curr_cmd	cmd;
	char		*space_pos;
	char		*temp;

	ft_bzero(&cmd, sizeof(t_curr_cmd));
	if (!is_separated(s))
		cmd.cmd = ft_strdup(s);
	else
	{
		space_pos = get_first_separator(s);
		temp = ft_strndup(s, space_pos - s);
		cmd.cmd = ft_strtrim(temp);
		free(temp);
		cmd.args = ft_strtrim(space_pos + 1);
	}
	shell->cmd = cmd;
}

int	handle_every_command(t_shell *shell, char **splitted)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (splitted[++i])
	{
		temp = ft_strdup(splitted[i]);
		handle_input(shell, &temp);
		if (temp && temp[0])
		{
			separate_cmd_args(shell, temp);
			exec_command(shell);
		}
		ft_free_int(temp);
		temp = NULL;
	}
	return (1);
}

int	main(void)
{
	t_shell	*shell;
	char	**splitted;
	char	*s;

	shell = t_shell_new();
	s = shell->s;
	while (1)
	{
		signal(SIGINT, signal_handler);
		print_promt();
		handle_input_buf(shell);
		s = ft_strdup(shell->buf->s);
		t_buffer_clean(shell->buf);
		if (!ft_strlen(s) && ft_free_int(s))
			continue ;
		splitted = ft_strsplit(s, ';');
		handle_every_command(shell, splitted);
		free(s);
		free_2dchararr_terminated(splitted);
	}
	exit(0);
	return (0);
}
