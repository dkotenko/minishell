/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/24 14:50:31 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# include "minishell.h"

# define SYMBOL_SQUOTE 39
# define SYMBOL_DQUOTE 34
# define ENV_HOME "HOME"
# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_PATH "PATH"
# define SHELL_NAME "minishell"
# define BUILTIN_LIST "exit env setenv unsetenv echo cd pwd type"
# define CHAR_BUFF_SIZE 1
# define PROMPT "$>"
# define TERMNAME_XTERM "xterm-256color"
# define MAINTERM TERMNAME_XTERM

enum	e_token_type
{
	TOKEN_TYPE_CMD = 0,
	TOKEN_TYPE_ARG = 1
}				e_token_type;

enum	e_input_status
{
	INPUT_STATUS_START = 0,	
	INPUT_STATUS_NORMAL = 1,
	INPUT_STATUS_STRONG_QUOTE = 2,
	INPUT_STATUS_WEAK_QUOTE = 3,
	INPUT_STATUS_BACKSLASH = 4,
	INPUT_STATUS_SEMICOLON = 5,
	INPUT_STATUS_VARIABLE = 6,
	INPUT_STATUS_SPACE_TAB = 7,
	INPUT_STATUS_NEXT_LINE = 8
}				e_input_status;

enum	e_lex_type
{
	LEX_TYPE_NORMAL = 0,
	LEX_TYPE_QUOTED = 1
}				e_lex_type;

enum	e_hist_status
{
	HIST_TAIL = 0,
	HIST_MIDDLE = 1,
	HIST_HEAD = 2
}				e_hist_status;

#endif
