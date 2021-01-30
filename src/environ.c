#include "minishell.h"

void		parse_environ(t_shell *shell, char **env)
{
	int		i;
	char	**splitted;
	char	*key;
	char	*value;

	i = 0;
	int j = 0;
	while (env[i])
	{
		splitted = ft_strsplit(env[i], '=');
		key = ft_strdup(splitted[0]);
		value = ft_strdup(splitted[1]);
		j = t_htable_add(shell->env->hash(key, shell->env->size),
			value, &shell->env);
		free_2dchararr_terminated(splitted);
		i++;
	}
	
}

char		*get_environ(t_shell *shell, char *key)
{
	int		hash;

	hash = shell->env->hash(key, shell->env->size);
	if (t_htable_find(hash, key, shell->env))
	 if ((i = ))
		ft_printf("%s\n", shell->env->table[i]);
}
