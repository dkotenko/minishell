/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/07 20:41:15 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			set_env(t_shell *shell, char *key, char *value)
{
	return (t_htable_set(shell->env, key, value));
}

void		do_setenv(t_shell *shell)
{
	char	**key_val;

	if (!shell->cmd.args)
	{
		ft_printf("setenv: %s\n", NOT_ENOUGH_ARGS);
		return;
	}
	key_val = ft_strsplit(shell->cmd.args, '=');
	t_htable_set(shell->env,
	key_val[T_HTABLE_KEY], key_val[T_HTABLE_VALUE]);
	free_2dchararr_terminated(key_val);
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


void		do_env(t_shell *shell)
{
	int		i;
	char	**environ;

	if (shell->cmd.args)
	{
		ft_printf("env: %s: %s\n", NO_SUCH_FILE, shell->cmd.args);
		return ;
	}
	environ = get_environ(shell);
	i = -1;
	while (++i < shell->env->counter)
	{
		ft_printf("%s\n", environ[i]);
	}
	free_2dchararr_terminated(environ);
}

int			do_environ(t_shell *shell)
{
	if (ft_strequ(shell->cmd.cmd, "env"))
		do_env(shell);
	else if (ft_strequ(shell->cmd.cmd, "setenv"))
		do_setenv(shell);
	else if (ft_strequ(shell->cmd.cmd, "unsetenv"))
	{
		if (!shell->cmd.args)
		{
			ft_printf("unsetenv: %s\n", NOT_ENOUGH_ARGS);
			return (1);
		}
		t_htable_remove(shell->env, shell->cmd.args);
	}
	return (1);
}
