/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/07 20:25:24 by clala            ###   ########.fr       */
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
# include "msg.h"

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
	t_dlist		*cmd;
	int			status;
	int			prev_status;
	t_buffer	*buf;
	char		*start_token;
	char		*start_cmd;
}				t_input;

/*
typedef struct	s_token
{
	t_buffer	*buf;
	int			type;
}				t_token;
*/

typedef struct	s_curr_cmd
{
	char		*cmd;
	char		*args;
}				t_curr_cmd;



typedef struct	s_shell
{
	t_input		*input;
	t_htable	*env;
	t_curr_cmd	cmd;
	t_dlist		*allocated;
}				t_shell;

/*
** exec_bin.c
*/
void			exec_bin();
int 			exec_prog(const char* program, const char* arg);
int				do_exit();
int				do_echo(t_curr_cmd cmd);
int				exec_command(t_shell *shell);
void run(const char* program, const char* arg);

/*
** quotation.c
*/
void			handle_quotes(char **input_string);
int				is_quote(char c);

/*
** handle_error.c
*/
int				handle_error(char *s);

/*
** do_cd.c
*/
int				do_cd(t_shell *shell, char *s);
int				is_cd_command(char *s);



/*
** environ.c
*/

int				do_environ(t_shell *shell);
void			do_env(t_shell *shell);
void			unset_env(t_shell *shell, char *key);
int				set_env(t_shell *shell, char *key, char *value);
char			*get_env(t_shell *shell, char *key);
void			remove_if_allocated(t_dlist *allocated, void *data);
//char			**get_environ(t_shell *shell);

int				ft_putenv(t_dlist *allocated, char *s);
char			*ft_getenv(const char *name);
int				ft_unsetenv(t_dlist *allocated, const char *name);
int ft_setenv(const char *name, const char *value, int overwrite, t_dlist *allocated);

void			quote_tokenizer(char *s, t_quote *q, t_dlist *list);


/*
** input.c
*/
//void			handle_input(t_shell *shell);
void			interrupt(int a);
t_input			*t_input_new(void);
void		handle_input(t_dlist *allocated, char **s);
void		replace_env_variables(t_dlist *allocated, char **s);

/*
**handle_status.c
*/
void			handle_status_space_tab(t_input *input, char *s, int i);
void			create_tokens(t_shell *shell, char *s);
void			handle_status_semicolon(t_input *input, char *s);

/*
**handle_status_aux.c
*/
int				is_quote_bs_status(int status);
void			handle_tabs_and_spaces(char **s);
int				is_empty_string(char *s);
int				is_space_tab(int c);
int			here(void);
void		add_token(t_input *input, char *s, int i);
#endif