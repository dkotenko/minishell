/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_methods.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/13 14:40:36 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_unsetenv(t_dlist *allocated, const char *name)
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
			remove_if_allocated(allocated, environ[i]);
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

int ft_setenv(const char *name, const char *value, int overwrite, t_dlist *allocated)
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
    ft_unsetenv(allocated, name);
    es = ft_strnew(ft_strlen(name) + 1 + ft_strlen(value));
    ft_strcpy(es, name);
    ft_strcat(es, "=");
    ft_strcat(es, value);
    return (ft_putenv(allocated, es) != 0) ? -1 : 0;
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
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], name, len) && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

