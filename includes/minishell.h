/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/11 14:01:50 by clala            ###   ########.fr       */
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

# include "libft.h"
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
	t_curr_cmd	cmd;
	t_dlist		*allocated;
	t_htable	*executables;
	t_htable	*env;
	char		*path_var;
	char		*s;
	
}				t_shell;


/*
** exec_bin.c
*/
void			exec_bin();
int 			exec_prog(const char* program, const char* arg);
int				do_exit();
int				do_echo(t_curr_cmd cmd);
int				exec_command(t_shell *shell);
void			run(t_shell *shell);

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
int				do_cd(t_shell *shell);
int				is_cd_command(char *s);



/*
** environ.c
*/

void		do_setenv(t_shell *shell);
char		**get_environ(t_shell *shell);
void		parse_system_environ(t_shell *shell);
void		do_env(t_shell *shell);
int			do_environ(t_shell *shell);
int			set_env(t_shell *shell, char *key, char *value);
char		*get_env(t_shell *shell, char *key);
char		**get_key_val(char *s);


/*
** input.c
*/
//void			handle_input(t_shell *shell);
void			interrupt(int a);
t_input			*t_input_new(void);
void		handle_input(t_shell *shell, t_dlist *allocated, char **s);
void		replace_env_variables(t_shell *shell, char **s);

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

/*
** t_shell.c
*/
t_shell		*t_shell_new(void);
void		update_exec_table(t_shell *shell);

/*
** cmd.c
*/
char		**get_argv(t_shell *shell, t_curr_cmd *cmd);
void		clear_cmd_args(t_curr_cmd *cmd);
char	*get_first_arg(t_curr_cmd *cmd);

/*
** path.c
*/
void	print_keys(t_htable *table);
char	*get_program_path(t_shell *shell, char *program_name);

void	signal_handler(int signo);
void	proc_signal_handler(int signo);

/*
** do_cd_aux.c
*/
char		**get_path_tokens(char *path);
int					check_dir(char *dir_name, char **error, char *origin_path);
char		*join_2darr(char **arr, char *sep);
int			is_tokens_valid(char **path_tokens, char *origin_path);
#endif