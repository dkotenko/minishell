/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_methods.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/20 21:27:04 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_spaces(char *args)
{
	char	*n1;
	char	*n2;
	char	**key_val;

	key_val = ft_strsplit(args, '=');
	n1 = ft_strchr(key_val[T_HTABLE_KEY], ' ');
	n2 = ft_strchr(key_val[T_HTABLE_VALUE], ' ');
	if (n1 || n2)
	{
		if (n1 && n2)
			ft_printf("%s: %s\n", SHELL_NAME, MSG_BAD_ASSIG);
		else if (n1)
			ft_printf("%s: %s not found\n", SHELL_NAME, key_val[T_HTABLE_KEY]);
		else if (n2)
			ft_printf("%s: %s: \n", SHELL_NAME, \
			MSG_NOT_AN_IDENT, key_val[T_HTABLE_KEY]);
		free_2dchararr_terminated(key_val);
		return (0);
	}
	free_2dchararr_terminated(key_val);
	return (1);
}

int	is_valid_args(char *args)
{
	char	*eq;

	eq = ft_strchr(args, '=');
	if (!eq || eq == args || ft_strchr(args, ' '))
	{
		ft_printf("%s: %s\n", SHELL_NAME, MSG_BAD_ASSIG);
		return (0);
	}
	return (1);
}

char	**get_key_val(char *s)
{
	char	**key_val;
	char	*key;
	char	*value;
	char	*eq;

	key_val = (char **)ft_memalloc(sizeof(char *) * 3);
	eq = ft_strchr(s, '=');
	if (!eq)
		return (key_val);
	key = ft_strndup(s, eq - s);
	value = ft_strdup(eq + 1);
	key_val[T_HTABLE_KEY] = key;
	key_val[T_HTABLE_VALUE] = value;
	return (key_val);
}

void	do_setenv(t_shell *shell)
{
	char	**key_val;

	if (!is_valid_args(shell->cmd.args))
		return ;
	key_val = get_key_val(shell->cmd.args);
	set_env(shell, key_val[T_HTABLE_KEY], key_val[T_HTABLE_VALUE]);
	free(key_val);
}

int	set_env(t_shell *shell, char *key, char *value)
{	
	return (t_htable_set(&shell->env, key, value));
}
