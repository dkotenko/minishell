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

char		**get_path_tokens(char *path)
{
	int		i;
	int		j;
	char	**path_tokens;
	char	**splitted;

	splitted = ft_strsplit(path, '/');
	i = len_2dchararr_terminated(splitted);
	path_tokens = (char **)ft_memalloc(sizeof(char *) * (i + 2));
	j = 0;
	path_tokens[j++] = ft_strdup("/");
	i = -1;
	while (splitted[++i])
	{
		if (ft_strequ("..", splitted[i]))
		{
			path_tokens[j] ? ft_free_null((void **)&path_tokens[j]) : 0;
			j = j == 1 ? 1 : j - 1;
			path_tokens[j] ? ft_free_null((void **)&path_tokens[j]) : 0;
			j = j == 1 ? 1 : j - 1;
			continue ;
		}
		else if (ft_strequ(".", splitted[i]))
			continue ;
		path_tokens[j] ? ft_free_null((void **)&path_tokens[j]) : 0;
		path_tokens[j++] = ft_strdup(splitted[i]);
	}
	free_2dchararr_terminated(splitted);
	return (path_tokens);
}

int					check_dir(char *dir_name, char **error, char *origin_path)
{
	struct stat		s_stat;
	DIR				*dir;
	struct dirent	*s_d;
	int				exists;

	exists = 0;
	if (stat(dir_name, &s_stat) == -1)
		ft_asprintf(error, "cd: no such file or directory: %s", origin_path);
	else if (!S_ISDIR(s_stat.st_mode))
		ft_asprintf(error, "cd: not a directory: %s", origin_path);
	else if (access(dir_name, R_OK) == -1)
		ft_asprintf(error, "cd: permission denied: %s", origin_path);
	else
	{
		dir = opendir(dir_name);
		while ((s_d = readdir(dir)) != NULL)
			if (ft_strequ(s_d->d_name, dir_name))
			{
				exists = 1;
				break ;
			}
		closedir(dir);	
	}
	return (exists);
}

int			free_all(char *error, char *curr_dir)
{
	if (error)
		free(error);
	free(curr_dir);
	return (1);
}



char		*join_2darr(char **arr, char *sep)
{
	t_buffer	*buf;
	char		*new;
	int			i;

	buf = t_buffer_create(T_BUFFER_BUFF_SIZE);
	i = 0;
	while (arr[i])
	{
		t_buffer_write(buf, arr[i]);
		i++;
		if (arr[i])
			t_buffer_write(buf, sep);
	}
	new = ft_strdup(buf->s);
	t_buffer_free(&buf);
	return (new);
}

int			is_tokens_valid(char **path_tokens, char *origin_path)
{
	char	*error;
	char	*curr_dir;
	char	*temp;
	int		i;

	error = NULL;
	curr_dir = ft_strdup("/");
	i = 0;
	while (path_tokens[++i])
	{
		temp = curr_dir;
		curr_dir = ft_strjoin(curr_dir, path_tokens[i]);
		free(temp);
		check_dir(curr_dir, &error, origin_path);
		temp = curr_dir;
		curr_dir = ft_strjoin(curr_dir, "/");
		free(temp);
		if (error && ft_printf("%s\n", error) && free_all(error, curr_dir))
			return (0);
	}
	free_all(error, curr_dir);
	return (1);
}

char		*get_valid_path(char *path, char *origin_path)
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

char		*create_relative_path(t_shell *shell, char *path)
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

char		*create_path(t_shell *shell, char *s)
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

int			do_cd(t_shell *shell, char *s)
{
	char	*pwd;
	char	*temp;

	if (!shell->cmd.args)
		shell->cmd.args = ft_strdup(get_env(shell, ENV_PWD));
	if (ft_strchr(shell->cmd.args, ' '))
	{
		ft_printf("cd: string not in pwd: %s\n", s);
		return (1);
	}
	pwd = create_path(shell, shell->cmd.args);
	temp = pwd;
	pwd = get_valid_path(pwd, s);
	free(temp);
	if (pwd)
	{
		set_env(shell, ft_strdup(ENV_OLDPWD),
			ft_strdup(get_env(shell, ENV_PWD)));
		set_env(shell, ft_strdup(ENV_PWD), pwd);
	}
	return (1);
}
