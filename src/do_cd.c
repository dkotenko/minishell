/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/11 13:38:29 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_valid_path(char *path, char *origin_path)
{	
	char	*new_path;
	char	**path_tokens;
	char	*temp;

	new_path = NULL;
	path_tokens = get_path_tokens(path);
	if (is_tokens_valid(path_tokens, origin_path))
	{
		new_path = join_2darr(path_tokens, "/");
		if (!ft_strequ(new_path, "/"))
		{
			temp = new_path;
			new_path = ft_strdup(new_path + 1);
			free(temp);
		}
	}
	free_2dchararr_terminated(path_tokens);
	return (new_path);
}

char	*create_relative_path(t_shell *shell, char *path)
{
	char	*pwd;
	char	*temp;
	char	*relative;

	pwd = ft_strdup(get_env(shell, ENV_PWD));
	temp = ft_strjoin(pwd, "/");
	free(pwd);
	relative = ft_strjoin(temp, path);
	free(temp);
	return (relative);
}

char	*create_path(t_shell *shell, char *s)
{
	char	*path;
	char	*temp;

	path = NULL;
	temp = NULL;
	if (s && s[0] == '/')
		return (ft_strdup(s));
	if (ft_strequ(s, "-"))
		return (ft_strdup(get_env(shell, ENV_OLDPWD)));
	if (!s || ft_strequ(s, "~"))
		return (ft_strdup(get_env(shell, ENV_HOME)));
	if (ft_strnequ(s, "~", 1))
		return (ft_strreplace(s, "~", get_env(shell, ENV_HOME)));
	if (s[0] != '/')
		return (create_relative_path(shell, s));
	return (ft_strdup(s));
}

int	do_cd(t_shell *shell)
{
	char	*pwd;
	char	*temp;
	char	*first_arg;

	if (!shell->cmd.args)
		shell->cmd.args = ft_strdup(get_env(shell, ENV_PWD));
	if (ft_strchr(shell->cmd.args, ' '))
	{
		first_arg = get_first_arg(&shell->cmd);
		ft_printf("cd: string not in pwd: %s\n", first_arg);
		ft_free_int(first_arg);
		return (1);
	}
	pwd = create_path(shell, shell->cmd.args);
	temp = pwd;
	pwd = get_valid_path(pwd, shell->cmd.args);
	free(temp);
	if (pwd)
	{
		set_env(shell, ft_strdup(ENV_OLDPWD),
			ft_strdup(get_env(shell, ENV_PWD)));
		set_env(shell, ft_strdup(ENV_PWD), pwd);
	}
	return (1);
}
