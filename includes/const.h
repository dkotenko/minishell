/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/02/07 18:43:30 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define SYMBOL_SINGLE_QUOTE 39
# define SYMBOL_DOUBLE_QUOTE 34
# define ENV_HOME "HOME"
# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define SHELL_NAME "minishell"
# define CHAR_BUFF_SIZE 1

enum			token_type
{
	TOKEN_TYPE_CMD,
	TOKEN_TYPE_ARG
}				t_token_type;

enum			input_status
{
	INPUT_STATUS_START,	
	INPUT_STATUS_NORMAL,
	INPUT_STATUS_STRONG_QUOTE,
	INPUT_STATUS_WEAK_QUOTE,
	INPUT_STATUS_BACKSLASH,
	INPUT_STATUS_SEMICOLON,
	INPUT_STATUS_VARIABLE,
	INPUT_STATUS_SPACE_TAB,
	INPUT_STATUS_NEXT_LINE
}				e_input_status;

enum			lex_type
{
	LEX_TYPE_NORMAL,
	LEX_TYPE_QUOTED
}				e_lex_type;