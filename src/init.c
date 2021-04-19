/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/20 19:58:13 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_trim(char **s)
{
	char	*temp;

	temp = *s;
	*s = ft_strtrim(*s);
	free(temp);
}

void	parse_system_environ(t_shell *shell)
{
	int			i;
	char		**splitted;
	char		*key;
	char		*value;
	extern char	**environ;

	i = 0;
	key = NULL;
	value = NULL;
	while (environ[i])
	{
		splitted = get_key_val(environ[i]);
		if (!splitted[0])
			handle_error("no equal sign in environ");
		key = splitted[T_HTABLE_KEY];
		value = splitted[T_HTABLE_VALUE];
		t_htable_add(&shell->env, key, value);
		free(splitted);
		i++;
	}
}

t_shell	*t_shell_new(void)
{
	t_shell		*new;

	new = (t_shell *)ft_memalloc(sizeof(t_shell));
	new->executables = t_htable_init(\
		T_HTABLE_INIT_PRIME_NUMBER, &cmp_func, &hash_func_fnv_1a_32);
	new->env = t_htable_init(\
		T_HTABLE_INIT_PRIME_NUMBER, &cmp_func, &hash_func_fnv_1a_32);
	new->buf = t_buffer_create(0);
	parse_system_environ(new);
	g_shell = new;
	return (new);
}
