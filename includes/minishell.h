/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/24 19:47:12 by clala            ###   ########.fr       */
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
# include <curses.h>
# include <term.h>

# include "libft.h"
# include "const.h"
# include "msg.h"

typedef struct s_curr_cmd
{
	char		*cmd;
	char		*args;
}				t_curr_cmd;

typedef struct s_shell
{
	t_curr_cmd		cmd;
	t_htable		*executables;
	t_htable		*env;
	t_buffer		*buf;
	char			*path_var;
	char			*s;
	t_dlist			*history;
	t_dlist_node	*history_pointer;
}				t_shell;

t_shell			*g_shell;

void			handle_signal_chlid(int signo);
/*
** main.c
*/
char			*join_3_strings(char *s1, char *s2, char *s3);
void			print_promt(void);
/*
** exec_bin.c
*/
void			exec_bin(void);
int				exec_prog(const char *program, const char *arg);
int				do_exit(void);
int				do_echo(t_curr_cmd *cmd);
void			do_pwd(t_shell *shell, t_curr_cmd cmd);
int				exec_command(t_shell *shell);
void			run(t_shell *shell);
void			do_type(t_shell *shell, t_curr_cmd cmd);

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
void			do_setenv(t_shell *shell);
char			**get_environ(t_shell *shell);
void			parse_system_environ(t_shell *shell);
void			do_env(t_shell *shell);
int				do_environ(t_shell *shell);
int				set_env(t_shell *shell, char *key, char *value);
char			*get_env(t_shell *shell, char *key);
char			**get_key_val(char *s);

/*
** input.c
*/
//void			handle_input(t_shell *shell);
void			interrupt(int a);
void			handle_input(t_shell *shell, char **s);
void			replace_env_variables(t_shell *shell, char **s);

/*
**handle_status_aux.c
*/
int				is_quote_bs_status(int status);
void			handle_tabs_and_spaces(char **s);
int				is_empty_string(char *s);
int				is_space_tab(int c);
int				here(void);

/*
** t_shell.c
*/
t_shell			*t_shell_new(void);
void			update_exec_table(t_shell *shell);

/*
** cmd.c
*/
char			**get_argv(t_shell *shell, t_curr_cmd *cmd);
void			clear_cmd_args(t_curr_cmd *cmd);
char			*get_first_arg(t_curr_cmd *cmd);

/*
** path.c
*/
void			print_keys(t_htable *table);
char			*get_program_path(t_shell *shell, char *program_name);
void			signal_handler(int signo);
void			proc_signal_handler(int signo);
void			do_trim(char **s);
/*
** do_cd_aux.c
*/
char			**get_path_tokens(char *path);
int				check_dir(char *dir_name, char **error, char *origin_path);
char			*join_2darr(char **arr, char *sep);
int				is_tokens_valid(char **path_tokens, char *origin_path);

/*
** aux.c
*/
char			*get_first_separator(char *s);
int				is_separated(char *s);
char			*get_pwd(t_shell *shell);
void			handle_input_buf(t_shell *shell);
void			choose_input_action(t_shell *shell, char *buf);
int				ft_putchar_int(int c);
void			handle_args(t_shell *shell);

#endif