#ifndef MINISHELL_H
# define MINISHELL_H


# include "ft_printf.h"
# include "error.h"
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>

# define SYMBOL_SINGLE_QUOTE 39
# define SYMBOL_DOUBLE_QUOTE 34

typedef struct	s_quote_info
{
	char		q_symbol;
	int			q_flag;
	char		*s;
}				t_quote_info;


typedef struct	s_shell
{
	char		*curr_path;
	char		*command;
	char		**args;
	char		*prev_cd_dir;
}				t_shell;

/*
** exec_bin.c
*/

void			exec_bin();
int exec_prog(char **argv);

/*
** quotation.c
*/
void				handle_quotes(char **input_string);

/*
** handle_error.c
*/
int				handle_error(char *s);

/*
** do_cd.c
*/
void			do_cd(char *s);
int				is_cd_command(char *s);
#endif