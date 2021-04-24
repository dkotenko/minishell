/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd_check_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/24 19:47:02 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dir_exists(char *dir_name)
{
	DIR				*dir;
	struct dirent	*s_d;
	int				exists;

	exists = 0;
	dir = opendir(dir_name);
	s_d = readdir(dir);
	while (s_d)
	{
		if (ft_strequ(s_d->d_name, dir_name))
		{
			exists = 1;
			break ;
		}
		s_d = readdir(dir);
	}
	closedir(dir);
	return (exists);
}

int	check_dir(char *dir_name, char **error, char *origin_path)
{
	struct stat		s_stat;
	int				exists;

	exists = 0;
	if (stat(dir_name, &s_stat) == -1)
		ft_asprintf(error, "cd: no such file or directory: %s", origin_path);
	else if (!S_ISDIR(s_stat.st_mode))
		ft_asprintf(error, "cd: not a directory: %s", origin_path);
	else if (access(dir_name, R_OK) == -1)
		ft_asprintf(error, "cd: permission denied: %s", origin_path);
	else
		exists = is_dir_exists(dir_name);
	return (exists);
}

static void	replace_var_in_arg(t_shell *shell, char *to_find, char *env_var)
{
	char	*s;

	s = shell->cmd.args;
	if (ft_strequ(s, to_find))
	{
		if (get_env(shell, env_var))
		{
			shell->cmd.args = ft_strdup(get_env(shell, env_var));
			ft_free_int(s);
		}
		else
			ft_strdel(&shell->cmd.args);
	}
}

void	handle_args(t_shell *shell)
{
	char	*s;
	char	*home;

	replace_var_in_arg(shell, "-", ENV_OLDPWD);
	replace_var_in_arg(shell, "~", ENV_HOME);
	s = shell->cmd.args;
	if (ft_strnequ(s, "~", 1))
	{
		if (get_env(shell, ENV_HOME))
			shell->cmd.args = ft_strreplace(s, "~", get_env(shell, ENV_HOME));
		else
			shell->cmd.args = ft_strreplace(s, "~", "");
		ft_free_int(s);
	}
	if (!shell->cmd.args)
	{
		home = get_env(shell, ENV_HOME);
		if (home)
			shell->cmd.args = ft_strdup(home);
		else
			shell->cmd.args = get_pwd(shell);
	}
}
