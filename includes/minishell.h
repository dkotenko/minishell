#ifndef MINISHELL_H
# define MINISHELL_H


# include "ft_printf.h"
# include "error.h"
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>

typedef struct	s_quote_string
{
	char		curr_quote_symbol;
	int			curr_quote_flag;
	char		*s;
}				t_quote_string;


typedef struct	s_shell
{
	char		*curr_path;
	char		*command;
	char		**args;
}				t_shell;

/*
** exec_bin.c
*/

void			exec_bin(char *s);

/*
** exec_bin.c
*/
int					handle_quotation(char **source_string);
#endif