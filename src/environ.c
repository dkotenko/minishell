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

int				ft_putenv(char *s)
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
	//free(environ);
	environ = new_env;
	return 0;
}

char			*ft_getenv(const char *name)
{
	extern char	**environ;
	int			len;
	int			i;

	if (name == NULL || environ == NULL)
		return (NULL);
	len = ft_strlen(name);
	i = -1;
	while (++i)
	{
		if (!ft_strncmp(environ[i], name, len) && environ[i][len] == '=')
			return (environ[i]);
	}
	return (NULL);
}

int				ft_unsetenv(const char *name)
{
    extern char	**environ;
	int			i;
	int			j;
	int			len;

    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
	{
        ft_printf("unsetenv: %s\n", MSG_NOT_ENOUGH_ARGS);
        return -1;
    }
    len = ft_strlen(name);
	i = 0;
	j = 0;
    while (environ[i])
	{
        if (!ft_strncmp(environ[i], name, len) && environ[i][len] == '=')
		{
			j = i;
			ft_printf("%s\n", environ[i]);
			//free(environ[i]);
			while (environ[j])
			{
				environ[j] = environ[j + 1];
				j++;
			}
        }
		else
			i++;
    }
    return 0;
}

int ft_setenv(const char *name, const char *value, int overwrite)
{
    char *es;

    if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL ||
            value == NULL)
	{
        ft_printf("setenv: %s\n", MSG_NOT_ENOUGH_ARGS);
        return -1;
    }
    if (ft_getenv(name) != NULL && overwrite == 0)
        return 0;
    ft_unsetenv(name);
    es = ft_strnew(ft_strlen(name) + 1 + ft_strlen(value));
    ft_strcpy(es, name);
    ft_strcat(es, "=");
    ft_strcat(es, value);
    return (ft_putenv(es) != 0) ? -1 : 0;
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
	ft_setenv(key_val[T_HTABLE_KEY], key_val[T_HTABLE_VALUE], 1);
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
	if (ft_strequ(shell->cmd.cmd, "env"))
		do_env(shell);
	else if (ft_strequ(shell->cmd.cmd, "setenv"))
		do_setenv(shell);
	else if (ft_strequ(shell->cmd.cmd, "unsetenv"))
		ft_unsetenv(shell->cmd.args);
	return (1);
}
