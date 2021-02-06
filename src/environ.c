/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		unset_env(t_shell *shell, char *key)
{
	t_htable_remove(shell->env, key);
}

int			set_env(t_shell *shell, char *key, char *value)
{
	return (t_htable_set(shell->env, key, value));
}

char		*get_env(t_shell *shell, char *key)
{
	return (t_htable_get(shell->env, key));
}

char		**get_environ(t_shell *shell)
{
	char	**env;
	char	***env_arr;
	int		i;

	env_arr = (char ***)t_htable_get_keys_values(shell->env);
	if (!(env = (char **)ft_memalloc(sizeof(char *) * 
	(shell->env->counter + 1))))
		handle_error(ERR_MALLOC);
	i = -1;
	
	while (++i < shell->env->counter)
	{
		ft_asprintf(&env[i], "%s=%s",
			env_arr[i][T_HTABLE_KEY],
			env_arr[i][T_HTABLE_VALUE]);
		free(env_arr[i]);
	}
	free(env_arr);
	return (env);
}

void		parse_system_environ(t_shell *shell, char **env)
{
	int		i;
	char	**splitted;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	while (env[i])
	{
		splitted = ft_strsplit(env[i], '=');
		key = ft_strdup(splitted[0]);
		value = ft_strdup(splitted[1]);
		t_htable_add(&shell->env, key, value);
		free_2dchararr_terminated(splitted);
		i++;
	}
}


void		do_env(t_shell *shell, char *s)
{
	int		i;
	char	**environ;

	(void)s;
	environ = get_environ(shell);
	i = -1;
	while (++i < shell->env->counter)
	{
		ft_printf("%s\n", environ[i]);
	}
	free_2dchararr_terminated(environ);
}

int			do_environ(t_shell *shell, char *s)
{	
	char	**splitted;
	char	**key_val;

	if (ft_strequ(s, "env"))
		do_env(shell, s);
	else if (ft_strequ(s, "setenv "))
	{
		splitted = ft_strsplit(s, ' ');
		key_val = ft_strsplit(splitted[1], '=');
		t_htable_set(shell->env,
		key_val[T_HTABLE_KEY], key_val[T_HTABLE_VALUE]);
		free_2dchararr_terminated(key_val);
		free_2dchararr_terminated(splitted);
	}
	else if (ft_strequ(s, "unsetenv "))
	{
		splitted = ft_strsplit(s, ' ');
		t_htable_remove(shell->env, splitted[1]);
		free_2dchararr_terminated(splitted);
	}
	return (1);
}
