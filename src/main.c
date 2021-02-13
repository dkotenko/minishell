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

	new = (t_shell *)ft_memalloc(sizeof(t_shell));
	new->env = t_htable_init(
		T_HTABLE_INIT_PRIME_NUMBER, &cmp_func, &hash_func_fnv_1a_32);
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

void		print_token(t_buffer *token)
{
	if (token->s)
		ft_printf("token:%s\n", token->s);
	else
	{
		ft_printf("Uninitiated string:%s\n", token->s);
	}
	
}

void		print_command(t_dlist *cmd)
{
	t_dlist_node *temp;

	ft_printf("==== command start ====\n");
	temp = cmd->head;
	while (temp)
	{
		print_token((t_buffer *)temp->data);
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

void		free_token(t_dlist_node *token)
{
	t_buffer	*buffer;
	
	

	buffer = token->data;
	t_buffer_free(&buffer);
	ft_printf("%d\n", 10);
	//exit(0);
}

void		free_cmd(t_dlist *cmd)
{
	t_dlist_node	*temp;
	t_dlist_node	*temp_next;

	temp = cmd->head;
	while (temp)
	{
		temp_next = temp->next;
		t_dlist_free((t_dlist *)&temp->data, &free_token);
		t_dlist_pop(cmd, temp);
		temp = temp_next;
	}
	
}

void		clean_commands(t_shell *shell)
{
	t_dlist_node	*temp;
	t_dlist_node	*temp_next;
	t_dlist			*commands;

	commands = shell->input->cmd;
	temp = commands->head;
	while (temp)
	{
		temp_next = temp->next;
		free_cmd(temp->data);
		t_dlist_pop(commands, temp);
		temp = temp_next;
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
		ft_printf("%d %s len: %d\n", shell->input->buf->s[0], s, shell->input->buf->i);
		//ft_printf("%d\n", !is_empty_string(s));
		
		
		if (!is_empty_string(s))
		{
			if (is_quote_bs_status(shell->input->status))
				continue ;
			//ft_printf("%s\n", s);
			ft_strnequ(s, "exit", 4) ? do_exit() : 0;
			create_tokens(shell, s);
			ft_printf("%d\n", shell->input->cmd->size);
			//ft_printf("%d %s\n", shell->input->buf->i, s);	
			print_commands(shell);
			ft_printf("%d\n", shell->input->cmd->size);
			clean_commands(shell);
			
			init_cmd(shell->input->cmd);
			
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
