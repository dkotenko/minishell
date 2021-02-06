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

char		**get_path_tokens(char *path)
{
	int		i;
	int		j;
	char	**path_tokens;
	char	**splitted;

	splitted = ft_strsplit(path, '/');
	i = -1;
	while (splitted[++i])
		;
	path_tokens = (char **)ft_memalloc(sizeof(char *) * (i + 2));
	j = 0;
	path_tokens[j++] = ft_strdup("/");
	i = -1;
	while (splitted[++i])
	{
		if (ft_strequ("..", splitted[i]))
		{	
			path_tokens[j] ? ft_free_null((void **)&path_tokens[j]) : 0;
			j--;
			j = j < 0 ? 0 : j;
			path_tokens[j] ? ft_free_null((void **)&path_tokens[j]) : 0;
			j--;
			j = j < 0 ? 0 : j;
			continue ;
		}
		else if (ft_strequ(".", splitted[i]))
			continue ;
		else if (ft_strequ("~", splitted[i]))
		{
			
		}
		
		path_tokens[j] ? ft_free_null((void **)&path_tokens[j]) : 0;
		path_tokens[j++] = ft_strdup(splitted[i]);
	}
	free_2dchararr_terminated(splitted);
	return (path_tokens);
}

/*
t_dlist				*get_tokens(char *path)
{
	char			**splitted;
	t_dlist			*path_tokens;
	t_dlist			*head;

	splitted = ft_strsplit(path, '/');
	path_tokens = t_dlist_new();
	head = path_tokens;
	t_dlist_append(path_tokens, t_dlist_node_new(ft_strdup("/"), sizeof(char *)));
	while (*splitted)
	{
		if (ft_strequ(".", *splitted))
			continue ;
		if (ft_strequ("..", *splitted))
		{
			if (head->head != head->tail)
				t_dlist_pop(path_tokens, path_tokens->tail);
			continue ;
		}
		t_dlist_append(path_tokens,
		t_dlist_node_new(ft_strdup(*splitted), sizeof(char *)));
		splitted++;
	}
	return (head);
}
*/

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

int			get_valid_path(char *path, char *origin_path)
{	
	char	**path_tokens;
	char	*error;
	char	*curr_dir;
	char	*temp;
	int		i;

	path_tokens = get_path_tokens(path);
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
		if (error && ft_printf("%s\n", error) && ft_free_int(error))
			return (0);
	}
	free(curr_dir);
	free_2dchararr_terminated(path_tokens);
	return (1);
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
	char	**splitted;
	char	*pwd;
	char	*old_pwd;
	char	*temp;

	splitted = ft_strsplit(s, ' ');
	pwd = NULL;
	if (len_2dchararr_terminated(splitted) > 2)
	{
		ft_printf("cd: string not in pwd: %s\n", s);
		free_2dchararr_terminated(splitted);
		return (1);
	}	
	pwd = create_path(shell, splitted[1]);
	temp = pwd;
	if (get_valid_path(pwd, splitted[1]))
	{
		old_pwd = ft_strdup(get_env(shell, ENV_PWD));
		set_env(shell, ENV_PWD, pwd);
		set_env(shell, ENV_OLDPWD, old_pwd);
	}
	free_2dchararr_terminated(splitted);
	return (1);
}
