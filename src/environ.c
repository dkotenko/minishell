/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/13 16:26:08 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist_node		*was_allocated(t_dlist *allocated, void *address)
{
	t_dlist_node	*temp;

	temp = allocated->head;
	while (temp)
	{
		if (address == temp->data)
			break;
		temp = temp->next;
	}
	return (temp);
}

void			remove_if_allocated(t_dlist *allocated, void *data)
{
	t_dlist_node	*node;

	if ((node = was_allocated(allocated, data)))
	{
		free(node->data);
		t_dlist_remove_node(allocated, node);
	}
}

int				ft_putenv(t_dlist *allocated, char *s)
{
	extern char	**environ;
	char		*equal_sign;
	int			environ_len;
	char		**new_env;

	equal_sign = ft_strchr(s, '=');
  	if (equal_sign == NULL)
		return (-1);
	environ_len = len_2dchararr_terminated(environ);
	new_env = (char **)ft_memalloc(sizeof(char *) * (environ_len + 1 + 1));
	ft_memcpy(new_env, environ, environ_len * sizeof(char *));
	new_env[environ_len] = s;
	remove_if_allocated(allocated, environ);
	t_dlist_append(allocated, t_dlist_node_new(new_env, sizeof(char **)));
	environ = new_env;
	return 0;
}

char		**get_key_val(char *s)
{
	char	**key_val;
	char	*temp;

	key_val = ft_strsplit(s, '=');
	temp = key_val[T_HTABLE_KEY];
	key_val[T_HTABLE_KEY] = ft_strtrim(key_val[T_HTABLE_KEY]);
	free(temp);
	if (key_val[T_HTABLE_VALUE])
	{
		temp = key_val[T_HTABLE_VALUE];
		key_val[T_HTABLE_VALUE] = ft_strtrim(key_val[T_HTABLE_VALUE]);
		free(temp);
	}
	return (key_val);
}

int			is_valid_setenv_args(char *s)
{
	char	*equal_sign;

	equal_sign = ft_strchr(s, '=');
	if (!s || !equal_sign || s == equal_sign || ft_strlen(s) == 1)
	{
		ft_printf("setenv: %s\n", MSG_NOT_ENOUGH_ARGS);
		return (0);
	}
	return (1);
}

void		do_setenv(t_shell *shell)
{
	char	**key_val;
	char	*n1;
	char	*n2;

	if (!is_valid_setenv_args(shell->cmd.args))
		return ;
	key_val = get_key_val(shell->cmd.args);
	n1 = ft_strchr(key_val[T_HTABLE_KEY], ' ');
	n2 = ft_strchr(key_val[T_HTABLE_VALUE], ' ');
	if (n1 || n2)
	{
		if (n1 && n2)
			ft_printf("%s: %s\n", SHELL_NAME, MSG_BAD_ASSIG);
		else if (n1)
			ft_printf("%s: %s not found\n", SHELL_NAME, key_val[T_HTABLE_KEY]);
		else if (n2)
			ft_printf("%s: %s: %s\n", SHELL_NAME, MSG_NOT_AN_IDENT, key_val[T_HTABLE_KEY]);
		free_2dchararr_terminated(key_val);
		return ;
	}
	ft_setenv(key_val[T_HTABLE_KEY], key_val[T_HTABLE_VALUE], 1, shell->allocated);
	free_2dchararr_terminated(key_val);
}

void			do_env(t_shell *shell)
{
	int			i;
	extern char	**environ;

	if (shell->cmd.args)
	{
		ft_printf("env: %s: %s\n", MSG_NO_SUCH_FILE, shell->cmd.args);
		return ;
	}
	i = -1;
	while (environ[++i])
		ft_printf("%s\n", environ[i]);
}

int			do_environ(t_shell *shell)
{
	int		env_changed;

	env_changed = 0;
	if (ft_strequ(shell->cmd.cmd, "env"))
		do_env(shell);
	else if (ft_strequ(shell->cmd.cmd, "setenv"))
	{
		do_setenv(shell);
		env_changed = 1;
	}
	else if (ft_strequ(shell->cmd.cmd, "unsetenv"))
	{
		ft_unsetenv(shell->allocated, shell->cmd.args);
		env_changed = 1;
	}
	env_changed ? update_exec_table(shell) : 0;
	return (1);
}
