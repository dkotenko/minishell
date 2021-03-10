/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/07 19:24:38 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				ft_getchar()
{
	return (0);
}

void		init_cmd(t_dlist *cmd)
{
	t_dlist	*tokens;

	tokens = t_dlist_new();
	
	t_dlist_append(cmd, t_dlist_node_new(tokens, sizeof(t_dlist *)));
	t_dlist_append(tokens, t_dlist_node_new(t_buffer_create(0), sizeof(t_buf *)));
}

t_input		*t_input_new(void)
{
	t_input	*new;

	new = (t_input *)ft_memalloc(sizeof(t_input));
	new->cmd = t_dlist_new();
	new->buf = t_buffer_create(0);
	init_cmd(new->cmd);
	return (new);
}

void		do_trim(char **s)
{
	char	*temp;

	temp = *s;
	*s = ft_strtrim(*s);
	free(temp);
}

void		replace_env_variables(t_dlist *allocated, char **s)
{
	char	*dollar_pos;
	int		i;
	char	*var_name;
	char	*value;
	char	*temp;

	dollar_pos = *s;
	while (*s && (dollar_pos = ft_strchr(dollar_pos, '$')))
	{
		i = dollar_pos - *s;
		
		while ((*s)[i + 1] && !is_space_tab((*s)[i + 1]))
			i++;
		if (i == dollar_pos - *s)
			break ;
		var_name = ft_strndup(dollar_pos, i - (dollar_pos - *s) + 1);
		value = ft_getenv(var_name + 1);
		if (!value)
		{
			value = ft_strdup("");
			t_dlist_append(allocated, t_dlist_node_new(value, sizeof(char *)));
		}
		ft_printf("value:%s\n", value);
		temp = *s;
		*s = ft_strreplace(*s, var_name, value);
		free(temp);
		free(var_name);
		remove_if_allocated(allocated, value);
		dollar_pos++;
		//получить имя переменной
		//найти имя в env, вернуть значение, если нет - вернуть """
		//заменить доллар + имя на значение
	}
}

void		handle_input(t_dlist *allocated, char **s)
{
	do_trim(s);
	replace_env_variables(allocated, s);
}

/*
void				handle_input(t_shell *shell)
{
	char			c;   
	struct termios	oldt;
	struct termios	newt;

	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO | ECHOE);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	c = 0;
	while((c = t_buffer_getchar(shell->input->buf)))
	{
		//c = shell->input->buf->s[shell->input->buf->i - 1];
		ft_putchar(c);
		if (c == '\n')
			break ;
		
	}
	//ft_printf("%s\n", shell->input->buf->s);
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}
*/