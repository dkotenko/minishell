/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/02/07 19:13:44 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h> 
# include <term.h>
# include <curses.h>

# include "ft_printf.h"
# include "error.h"
# include "const.h"

typedef struct	s_quote
{
	char		q_symbol;
	int			q_flag;
	int			has_set;
	char		*start;
	char		*s;
}				t_quote;

typedef struct	s_input
{
	char		q_symbol;
	t_dlist		*commands;
	int			status;
	int			prev_status;
	t_buffer	*buf;
	char		*start;
}				t_input;

typedef struct	s_lex_token
{
	char		*s;
	int			type;
}				t_lex_token;


typedef struct	s_command
{
	char		*cmd_name;
	t_dlist		*args;
}				t_command;

typedef struct	s_shell
{
	char		*curr_path;
	char		*command;
	char		**args;
	char		*prev_cd_dir;
	t_input		*input;
	t_htable	*env;
}				t_shell;

/*
** exec_bin.c
*/
void			exec_bin();
int exec_prog(char **argv, char **env);

/*
** quotation.c
*/
void				handle_quotes(char **input_string);
int			is_quote(char c);

/*
** handle_error.c
*/
int				handle_error(char *s);

/*
** do_cd.c
*/
int			do_cd(t_shell *shell, char *s);
int				is_cd_command(char *s);



/*
** environ.c
*/
void		parse_system_environ(t_shell *shell, char **env);
int			do_environ(t_shell *shell, char *s);
void		do_env(t_shell *shell, char *s);
void		unset_env(t_shell *shell, char *key);
int			set_env(t_shell *shell, char *key, char *value);
char		*get_env(t_shell *shell, char *key);
char		**get_environ(t_shell *shell);


void		quote_tokenizer(char *s, t_quote *q, t_dlist *list);


/*
** input.c
*/
void		handle_input(t_shell *shell);
void		interrupt(int a);

#endif