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

int			print_entry(t_shell *shell)
{
	int		status;
	
	status = shell->input->status;
	if (status == INPUT_STATUS_STRONG_QUOTE)
		ft_printf("quote> ");
	else if (status == INPUT_STATUS_WEAK_QUOTE)
		ft_printf("dquote> ");
	else if (status == INPUT_STATUS_BACKSLASH)
		ft_printf("> ");
	else
		ft_printf("$> ");
	//fflush(stdout);
	return (1);
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

/*
void				add_token(t_dlist *dlist, char *s, int lex_type)
{
	t_token		*token;
	t_dlist_node	*node;

	token = (t_token *)ft_memalloc(sizeof(t_token));
	!token ? handle_error(ERR_MALLOC) : 0;
	token->s = NULL;
	token->type = lex_type;
	node = t_dlist_node_new(token, sizeof(t_token));
	t_dlist_append(dlist, node);
}
*/

void		print_token(t_buf *token)
{
	ft_printf("token:%s", token->s);
}

void		print_command(t_dlist *cmd)
{
	t_dlist_node *temp;

	ft_printf("==== command start ====\n");
	temp = cmd->head;
	while (temp)
	{
		print_token((t_buf *)temp->data);
		temp = temp->next;
	}
	ft_printf("===== command end =====\n");
}

void		print_commands(t_shell *shell)
{
	t_dlist_node *temp;

	temp = shell->input->cmd->head;
	while (temp)
	{
		print_command(temp->data);
		temp = temp->next;
	}
}

int			main(int argc, char **argv, char **env)
{
	char	*s;
	t_shell	*shell;

	
	(void)argv;
	argc > 1 ? exit(0) : 0;
	shell = t_shell_new();

	s = shell->input->buf->s;
	signal (SIGINT, &interrupt);
	parse_system_environ(shell, env);
	while (print_entry(shell))
	{
		
		handle_input(shell);
		//ft_printf("%d\n", shell->input->buf->i);
		//ft_printf("%d\n", shell->input->buf->s[0]);
		//ft_printf("%d\n", shell->input->buf->s[1]);
		//ft_printf("%d\n", shell->input->buf->s[2]);
		//ft_printf("%d %s len: %d\n", shell->input->buf->s[0], s, shell->input->buf->i);
		//ft_printf("%d\n", !is_empty_string(s));
		
		
		if (!is_empty_string(s))
		{
			if (is_quote_bs_status(shell->input->status))
				continue ;
			//ft_printf("%s\n", s);
			ft_strnequ(s, "exit", 4) ? do_exit() : 0;
			create_tokens(shell, s);
			//ft_printf("%d %s\n", shell->input->buf->i, s);	
			print_commands(shell);
			
			//parser();
			//executor();
			/*
			if (!exec_implemented_commands(shell, s))
			{
				exec_prog(splitted = ft_strsplit(s, ' '), get_environ(shell));
				free_2dchararr_terminated(splitted);
			}
			*/
		}
		
		t_buffer_clean(shell->input->buf);
	}
	exit(0);
	return (0);
}
