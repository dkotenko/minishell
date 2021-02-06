#ifndef MINISHELL_H
# define MINISHELL_H


# include "ft_printf.h"
# include "error.h"
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h> 

# define SYMBOL_SINGLE_QUOTE 39
# define SYMBOL_DOUBLE_QUOTE 34
# define ENV_HOME "HOME"
# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define SHELL_NAME "minishell"

enum			input_status
{
	INPUT_STATUS_SHELL,
	INPUT_STATUS_QUOTE,
	INPUT_STATUS_BACKSLASH
}				e_input_status;

enum			lex_type
{
	LEX_TYPE_NORMAL,
	LEX_TYPE_QUOTED
}				e_lex_type;



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
	int			q_flag;
	int			input_status;
	t_dlist		*dlist;
	int			status;
	t_buffer	*buf;
}				t_input;

typedef struct	s_lex_token
{
	char		*s;
	int			type;
}				t_lex_token;


typedef struct	s_command
{
	char		*command;
	char		*argument;
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


#endif