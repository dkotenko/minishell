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

int			is_valid_spaces(char *args)
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
			ft_printf("%s: %s: \n", SHELL_NAME,
			MSG_NOT_AN_IDENT, key_val[T_HTABLE_KEY]);
		free_2dchararr_terminated(key_val);
		return (0);
	}
	free_2dchararr_terminated(key_val);
	return (1);
}

int			is_valid_args(char *args)
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

void		do_setenv(t_shell *shell)
{
	char	*key;
	char	*value;
	char	*eq;
	
	if (!is_valid_args(shell->cmd.args))
		return ;
	eq = ft_strchr(shell->cmd.args, '=');
	key = ft_strndup(shell->cmd.args, eq - shell->cmd.args - 1);
	value = ft_strdup(eq + 1);
	t_htable_set(&shell->env, key, value);
}

int			set_env(t_shell *shell, char *key, char *value)
{
	return (t_htable_set(&shell->env, key, value));
}

char		*get_env(t_shell *shell, char *key)
{
	return (t_htable_get(shell->env, key));
}
