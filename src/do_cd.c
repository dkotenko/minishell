/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/23 22:53:02 by clala            ###   ########.fr       */
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
	if (s[0] != '/')
		return (create_relative_path(shell, s));
	return (ft_strdup(s));
}

void	replace_var_in_arg(t_shell *shell, char *to_find, char *env_var)
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
		shell->cmd.args = ft_strdup(get_env(shell, ENV_HOME));
}

char	*get_first_separator(char *s)
{
	char	*tab_pos;
	char	*space_pos;

	tab_pos = ft_strchr(s, '\t');
	space_pos = ft_strchr(s, ' ');
	if (tab_pos && space_pos && (space_pos - s) > (tab_pos - s))
		space_pos = tab_pos;
	else if (tab_pos && !space_pos)
		space_pos = tab_pos;
	return (space_pos);
}

int		is_separated(char *s)
{
	return (ft_strchr(s, ' ') || ft_strchr(s, '\t'));
}

void	set_env_pwd(t_shell *shell, char *pwd)
{
	char	*curr_pwd;

	if (pwd)
	{
		curr_pwd = get_env(shell, ENV_PWD);
		if (!curr_pwd)
		
		set_env(shell, ft_strdup(ENV_OLDPWD),
			ft_strdup(curr_pwd));
		set_env(shell, ft_strdup(ENV_PWD), pwd);
	}
}

int	do_cd(t_shell *shell)
{
	char	*pwd;
	char	*temp;
	char	*first_arg;

	handle_args(shell);
	if (is_separated(shell->cmd.args))
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
	set_env_pwd(shell, pwd);
	return (1);
}
