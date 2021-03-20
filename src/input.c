/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/20 19:55:36 by clala            ###   ########.fr       */
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

char		*get_var_extend(char *pos)
{
	int		i;

	i = 0;
	while (pos[1 + i] && !is_space_tab(pos[1 + i]) && pos[1 + i] != '$')
		i++;
	if (!i)
		return (NULL);
	return (ft_strndup(pos, i + 1));
}

void		replace_env_variables(char **environ, char **s)
{
	char	*dollar_pos;
	char	*var_extend;
	char	*value;
	char	*temp;
	int		new_len;

	dollar_pos = *s;
	while (*s && (dollar_pos = ft_strchr(dollar_pos, '$')))
	{
		var_extend = get_var_extend(dollar_pos);
		//ft_printf("%s\n", var_extend);
		if (!var_extend && dollar_pos++)
			continue ;
		value = ft_getenv(environ, var_extend + 1);
		temp = *s;
		if (!value)
		{
			new_len = ft_strlen(temp) - ft_strlen(var_extend);
			*s = ft_strnew(new_len);
			//ft_printf("%s\n", *s);
			ft_strncpy(*s, temp, dollar_pos - temp);
			ft_strcat(*s, dollar_pos + 1 + ft_strlen(var_extend));
			//ft_printf("aa %s\n", *s);
		}
		else
			*s = ft_strreplace(*s, var_extend, value);
		//ft_printf("%s\n", *s);
		free(temp);
		free(var_extend);
	}
}

void		clear_cmd_args(t_curr_cmd *cmd)
{
	cmd->args ? free(cmd->args) : 0;
	cmd->cmd ? free(cmd->cmd) : 0;
	ft_bzero(cmd, sizeof(t_curr_cmd));
}


void		handle_input(t_shell *shell,t_dlist *allocated, char **s)
{
	clear_cmd_args(&shell->cmd);
	replace_env_variables(shell->environ, s);
	do_trim(s);
	(void)allocated;
	
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