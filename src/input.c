/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/11 12:31:24 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_single_dollar_sign(char *s)
{
	if (!s || !s[0])
		return (0);
	if (s[1] && !is_space_tab(*(s + 1)))
		return (0);
	return (1);
}

char	*get_var_extend(char *s)
{
	int		i;

	if (!s || !s[0])
		return (NULL);
	i = 1;
	while (s[i] && !is_space_tab(s[i]) && s[i] != '$')
		i++;
	return (ft_strndup(s, i));
}

void	replace_variable(t_shell *shell, t_buffer *buf,
char **curr, char *dollar_pos)
{
	char	*var_extend;
	char	*value;

	var_extend = get_var_extend(dollar_pos);
	if (var_extend)
	{
		value = get_env(shell, var_extend + 1);
		t_buffer_write(buf, value);
		*curr = dollar_pos + ft_strlen(var_extend);
		free(var_extend);
	}
}

void	replace_env_variables(t_shell *shell, char **s)
{
	t_buffer	*buf;
	char		*dollar_pos;
	char		*curr;

	buf = t_buffer_create(1);
	dollar_pos = ft_strchr(*s, '$');
	curr = *s;
	while (dollar_pos)
	{
		t_buffer_writen(buf, curr, dollar_pos - curr);
		if (is_single_dollar_sign(dollar_pos))
		{
			t_buffer_add_char(buf, '$');
			curr = dollar_pos + 1;
		}
		else
			replace_variable(shell, buf, &curr, dollar_pos);
		dollar_pos = ft_strchr(curr, '$');
	}
	t_buffer_write(buf, curr);
	free(*s);
	*s = ft_strdup(buf->s);
	t_buffer_free(&buf);
}

void	handle_input(t_shell *shell, char **s)
{
	clear_cmd_args(&shell->cmd);
	replace_env_variables(shell, s);
	if (*s && (*s)[0])
		do_trim(s);
}
