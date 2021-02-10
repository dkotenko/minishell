/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/02/07 19:00:11 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_status(t_input *input, int status)
{
	input->status = status;
}

static void	set_another_input_status(t_input *input, char c)
{
	if (c == '$' && !is_quote_bs_status(input->status))
	{
		input->status = INPUT_STATUS_VARIABLE;
	}
	else if ((c == '\t'|| c == ' ') && !is_quote_bs_status(input->status))
		input->status = INPUT_STATUS_SPACE_TAB;
	else if (c == '\n')
		input->status = INPUT_STATUS_NEXT_LINE;
	
}

void		set_input_status(t_input *input, char c)
{
	if (c == ';' && !is_quote_bs_status(input->status))
		input->status = INPUT_STATUS_SEMICOLON;
	else if (c == '\\')
	{
		if (input->status == INPUT_STATUS_NORMAL)
			input->status = INPUT_STATUS_BACKSLASH;
		else if (input->status == INPUT_STATUS_BACKSLASH)
			input->status = INPUT_STATUS_NORMAL;
	}
	else if (c == SYMBOL_SINGLE_QUOTE)
	{
		input->status = input->status == INPUT_STATUS_STRONG_QUOTE ||
		input->status == INPUT_STATUS_BACKSLASH ? 
		INPUT_STATUS_NORMAL : INPUT_STATUS_STRONG_QUOTE;
	}
	else if (c == SYMBOL_DOUBLE_QUOTE)
	{
		input->status = input->status == INPUT_STATUS_WEAK_QUOTE ||
		input->status == INPUT_STATUS_BACKSLASH ?
		INPUT_STATUS_NORMAL : INPUT_STATUS_WEAK_QUOTE;
	}
	else
		set_another_input_status(input, c);
}


void		handle_status_space_tab(t_input *input, char *s, int i)
{
	if (is_quote_bs_status(input->status))
		t_buffer_add_char(input->buf, s[i]);
	else if (s + input->buf->i == input->start_token)
		return ;
		/*
	else
		add_token(input, s, i);
		*/
}

void		handle_status_variable(t_shell *shell, char *s, int *i)
{
	int		start;
	char	*variable_name;
	char	*variable_value;
	int		dollar_sign_pos;

	dollar_sign_pos = *i;
	start = *i + 1;
	
	while (s[*i + 1] && !is_space_tab(s[*i + 1]) &&
	!is_quote(s[*i + 1]) && s[*i + 1] != '\n')
		(*i)++;
	
	if (start == *i + 1)
	{
		t_buffer_add_char(shell->input->cmd->tail->data, s[(*i)++]);
	}
	else
	{
		variable_name = ft_strndup(s + start, *i - start);
		variable_value = get_env(shell, variable_name);
		free(variable_name);
		if (variable_value)
			t_buffer_write(shell->input->cmd->tail->data, variable_value);
		
	}
	shell->input->status = INPUT_STATUS_NORMAL;
	//ft_printf("%s\n", ((t_token *)shell->input->cmd->tail->data)->buf->s);
}

/*
void		handle_status_semicolon(t_input *input, char *s)
{
	char	*new;
	int		len;
	//t_cmd	*cmd;
	
	len = s + input->buf->i - input->start_cmd;
	new = ft_strnew(s + input->buf->i - input->start_cmd);
	ft_strncpy(new, input->start_cmd, len);
	cmd = t_cmd_new(new);
	t_dlist_append(input->cmd, t_dlist_node_new(cmd, sizeof(t_cmd)));
}
*/


void		add_token(t_input *input, char *s, int i)
{
	char	*to_token;
	t_dlist	*curr_tokens;
	t_buf	*token;

	to_token = ft_strndup(input->start_token, s + i - input->start_token);
	curr_tokens = (t_dlist *)(input->cmd->tail->data);
	
	((t_buffer *)(curr_tokens->tail->data))->s = to_token;
	
	
	token = t_buf_create(0);
	t_dlist_append(curr_tokens, t_dlist_node_new(token, sizeof(t_buf)));
	set_status(input, INPUT_STATUS_NORMAL);
}

void		handle_status_weak_quote(t_input *input, char *s)
{
	(void)input;
	(void)s;
}

void		handle_status_next_line(t_input *input, char *s, int *i)
{
	add_token(input, s, *i);
}

void		create_tokens(t_shell *shell, char *s)
{
	int		i;
	int		status;

	shell->input->start_token = s;
	shell->input->start_cmd = s;
	i = -1;
	while (s[++i])
	{
		//char *a = {';', '\\', '\'', '\"', '$'};
		set_input_status(shell->input, s[i]);
		status = shell->input->status;	
		//ft_printf("%d\n", i);
		if (status == INPUT_STATUS_NORMAL)
		{
			ft_printf("INPUT_STATUS_NORMAL %d\n", s[i]);
			t_buffer_add_char(shell->input->buf, s[i]);
		}
		else if (status == INPUT_STATUS_SPACE_TAB)
		{
			ft_printf("INPUT_STATUS_SPACE_TAB\n");
			handle_status_space_tab(shell->input, s, i);
		}
		else if (status == INPUT_STATUS_SEMICOLON)
		{
			ft_printf("INPUT_STATUS_SEMICOLON\n");
			;//handle_status_semicolon(shell->input, s);
		}
		else if (status == INPUT_STATUS_STRONG_QUOTE)
		{
			ft_printf("INPUT_STATUS_STRONG_QUOTE\n");
		}
			//handle_status_strong_quote(shell->input, s);
		else if (status == INPUT_STATUS_WEAK_QUOTE)
		{
			ft_printf("INPUT_STATUS_WEAK_QUOTE\n");
			handle_status_weak_quote(shell->input, s);
		}
		else if (status == INPUT_STATUS_VARIABLE)
		{
			ft_printf("INPUT_STATUS_VARIABLE\n");
			handle_status_variable(shell, s, &i);
		}
		else if (status == INPUT_STATUS_NEXT_LINE)
		{
			ft_printf("INPUT_STATUS_NEXT_LINE\n");
			handle_status_next_line(shell->input, s, &i);
		}
			
		shell->input->prev_status = shell->input->status;
	}
}