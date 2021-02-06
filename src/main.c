/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
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

t_shell		*t_shell_new(void)
{
	t_shell	*new;

	if (!(new = (t_shell *)malloc(sizeof(t_shell))))
		handle_error(ERR_MALLOC);
	new->env = t_htable_init(42, &cmp_func, &hash_func_fnv_1a_32);
	!new->env ? handle_error(ERR_MALLOC) : 0;
	new->input = (t_input *)ft_memalloc(sizeof(t_input));
	!new->input ? handle_error(ERR_MALLOC) : 0;
	new->input->dlist = t_dlist_new();
	new->input->buf = t_buffer_create(T_BUFFER_BUFF_SIZE);
	!new->input->buf ? handle_error(ERR_MALLOC) : 0;
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
void		interrupt()
{
	ft_printf("hello\n");
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


void		quote_tokenizer(char *s, t_quote *q, t_dlist *list)
{
	int		i;
	int		prev;

	i = 0;
	while (s[i])
	{	
		is_quote(s[i]) ? set_quote(q, s[i]) : 0;
		if (!q->q_flag)
		{
			while (s[i] && !is_quote(s[i++]))
				prev = i;
			add_token(list, ft_strnew(s + prev - q->start), LEX_TYPE_NORMAL);
			ft_printf("%d\n", s + prev - q->start);
			ft_strncpy(((t_lex_token *)list->tail->data)->s,
				q->start, s + prev - q->start);
			q->start = s + i;
		}
		else if (q->q_flag)
		{
			while (s[++i] && s[i] != q->q_symbol)
				;
			add_token(list, ft_strnew(s + i - q->start), LEX_TYPE_QUOTED);
			ft_strncpy(((t_lex_token *)list->tail->data)->s,
				q->start, s + i - q->start);
			q->start = s + i + 1;
		}
		if (!s[i])
			break ;
		prev = i;
		i++;
		if (i > 100)
		{
			ft_printf("here\n");
			exit(0);
		}
	}

}

int			split_by_quotes(char *s)
{
	int		i;
	t_quote	q;
	int		prev;
	t_dlist	*list;

	i = 0;
	ft_memset(&q, 0, sizeof(t_quote));
	prev = 0;
	q.start = s;
	q.s = s;
	list = t_dlist_new();
	
	quote_tokenizer(s, &q, list);
	t_dlist_node *temp = list->head;
	while (temp != NULL)
	{
		//ft_printf("%s\n", ((t_lex_token *)temp->data)->s);
		temp = temp->next;
	}
	return (1);
}

int			split_by_semicolon(char *s)
{
	t_dlist	*list;
	char	*start;
	t_quote	quote;

	if (ft_strstr(s, ";;"))
	{	
		ft_printf("%s: parse error near ';;'\n", SHELL_NAME);
		return (0);
	}
	ft_memset(&quote, 0, sizeof(t_quote));
	list = t_dlist_new();
	start = s;
	while (*s)
	{
		if (is_quote(*s))
			set_quote(&quote, *s);
		if (*s == ';' && !quote.q_flag)
			;
	}
	return (1);
}





int			main(int argc, char **argv, char **env)
{
	char	*s;
	char	**splitted;
	t_shell	*shell;
	t_list	*input;

	
	exit(0);

	char *sa = "\"\"";
	while (*sa)
	{
		ft_printf("%d\n", *sa);
		sa++;
	}
	
	split_by_quotes(sa);
	
	(void)argv;
	argc > 1 ? exit(0) : 0;
	shell = t_shell_new();
	parse_system_environ(shell, env);
	//signal (SIGINT,interrupt);
	input = NULL;
	
	while (print_entry(shell) && get_next_line(STDIN_FILENO, &s))
	{	
		if (!is_empty(s))
		{
			//lexer(shell, s);
			if (shell->input->status != INPUT_STATUS_SHELL)
				continue ;
			//parser();
			//executor();
			
			if (!exec_implemented_commands(shell, s))
			{
				exec_prog(splitted = ft_strsplit(s, ' '), get_environ(shell));
				free_2dchararr_terminated(splitted);
			}
		}
		free(s);
	}
	return (0);
}
