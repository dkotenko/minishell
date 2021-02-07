/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/02/06 23:58:42 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			print_entry(t_shell *shell)
{
	if (shell->input->status == INPUT_STATUS_SHELL)
		ft_printf("$> ");
	else if (shell->input->status == INPUT_STATUS_QUOTE)
	{
		if (shell->input->q_symbol == SYMBOL_SINGLE_QUOTE)
			ft_printf("quote> ");
		else if (shell->input->q_symbol == SYMBOL_DOUBLE_QUOTE)
			ft_printf("dquote> ");
	}
	else if (shell->input->status == INPUT_STATUS_BACKSLASH)
		ft_printf("> ");
	return (1);
}

int			do_exit()
{	
	//kill(getppid(), SIGKILL); // close terminal
	exit(0);
    
}

int			do_echo(char *s)
{
	char	**splitted;

	splitted = ft_strsplit(s, ' ');
	ft_printf("%s\n", splitted[1]);
	free_2dchararr_terminated(splitted);
	return (1);
}

t_input		*t_input_new(void)
{
	t_input	*new;

	new = (t_input *)ft_memalloc(sizeof(t_input));
	!new ? handle_error(ERR_MALLOC) : 0;
	new->dlist = t_dlist_new();
	new->buf = t_buffer_create(T_BUFFER_BUFF_SIZE);
	!new->buf ? handle_error(ERR_MALLOC) : 0;
}

t_shell		*t_shell_new(void)
{
	t_shell	*new;

	if (!(new = (t_shell *)malloc(sizeof(t_shell))))
		handle_error(ERR_MALLOC);
	new->env = t_htable_init(42, &cmp_func, &hash_func_fnv_1a_32);
	!new->env ? handle_error(ERR_MALLOC) : 0;
	new->input = t_input_new();
	
	return (new);
}


void		handle_tabs_and_spaces(char **s)
{
	char	*temp;

	temp = *s;
	*s = ft_strtrim(*s);
	free(temp);
}

int			is_empty(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (!(s[i] == ' ' || s[i] == '\t'))
			return (0);
	}
	return (1);
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


/*
void		lexer(t_shell *shell, char *s)
{
	//ft_lstadd() shell->input->input
	//handle_tabs_and_spaces(&s);
	handle_quotes(&s);
}
*/



void	set_quote(t_quote *q, char c)
{
	if (q->q_flag == false)
	{
		q->q_flag = true;
		q->q_symbol = c;
		q->has_set = 1;
	}
	else if (q->q_flag == true)
	{
		if (q->q_symbol == c)
		{
			q->q_flag = false;
			q->q_symbol = 0;
			q->has_set = 1;
		}
	}
}

void				add_token(t_dlist *dlist, char *s, int lex_type)
{
	t_lex_token		*token;
	t_dlist_node	*node;

	token = (t_lex_token *)ft_memalloc(sizeof(t_lex_token));
	!token ? handle_error(ERR_MALLOC) : 0;
	token->s = s;
	token->type = lex_type;
	node = t_dlist_node_new(token, sizeof(t_lex_token));
	t_dlist_append(dlist, node);
}


void		set_input_status(t_input *input, char c)
{
	if (is_quote(c))
	{
		;
	}
	if (q->q_flag == false)
	{
		q->q_flag = true;
		q->q_symbol = c;
		q->has_set = 1;
	}
	else if (q->q_flag == true)
	{
		if (q->q_symbol == c)
		{
			q->q_flag = false;
			q->q_symbol = 0;
			q->has_set = 1;
		}
	}
}



void		get_tokens(t_shell *shell, char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		(';', '\\', '\'', '\"', '$');
		set_input_status(shell, s[i]);
	}
}

int			is_status_to_continue(int status)
{
	if (status == INPUT_STATUS_BACKSLASH ||
		status == INPUT_STATUS_STRONG_QUOTE ||
		status == INPUT_STATUS_WEAK_QUOTE)
		return (1);
	return (0);
}




int			main(int argc, char **argv, char **env)
{
	char	*s;
	
	t_shell	*shell;
	t_list	*input;

	
	(void)argv;
	argc > 1 ? exit(0) : 0;
	shell = t_shell_new();
	s = shell->input->buf->s;
	signal (SIGINT, &interrupt);
	while (print_entry(shell))
	{
		handle_input(shell);
		if (!is_empty(s))
		{
			if (is_status_to_continue(shell->input->status))
				continue ;
			if (ft_strequ(s, "exit\n"))
				do_exit();
			get_tokens(shell, s);
			//parser();
			//executor();
			/*
			if (!exec_implemented_commands(shell, s))
			{
				exec_prog(splitted = ft_strsplit(s, ' '), get_environ(shell));
				free_2dchararr_terminated(splitted);
			}
			*/
			t_buffer_clean(shell->input->buf);
		}
	}

	exit(0);

	parse_system_environ(shell, env);
	//
	input = NULL;
	
	while ( get_next_line(STDIN_FILENO, &s))
	{	
		
		free(s);
	}
	return (0);
}
