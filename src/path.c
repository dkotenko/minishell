/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/16 23:53:05 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
unix ищет файл во всех папках с начала до конца, запускает первый
ищет имя в таблица, далее пытается запустить (доступ/запуск). 
Нет прав ? пишет zsh: command not found: prog
*/

static void	handle_struct_direct(t_shell *shell, struct dirent	*s_d,
struct stat *s_stat, char *dir_path)
{
	char			*curr_exec;
	char			*fullpath;

	curr_exec = ft_strdup(s_d->d_name);
	fullpath = join_3_strings(dir_path, "/", curr_exec);
	if (stat(fullpath, s_stat) == 0 && s_stat->st_mode & S_IXUSR && \
	!access(fullpath, R_OK))
		t_htable_set(&shell->executables, curr_exec, fullpath);
	else
	{
		free(fullpath);
		free(curr_exec);
	}
}

void	add_dir_execs(t_shell *shell, char *dir_path)
{	
	struct stat		s_stat;
	DIR				*dir;
	struct dirent	*s_d;

	if (stat(dir_path, &s_stat) == -1 || !S_ISDIR(s_stat.st_mode) || \
		access(dir_path, R_OK) == -1)
		return ;
	dir = opendir(dir_path);
	s_d = readdir(dir);
	while (s_d)
	{
		if (ft_strequ(s_d->d_name, "..") || ft_strequ(s_d->d_name, "."))
			continue ;
		handle_struct_direct(shell, s_d, &s_stat, dir_path);
		s_d = readdir(dir);
	}
	closedir(dir);
}

void	handle_exec_table(t_shell *shell)
{
	char		**splitted_path;
	char		*path;
	char		**temp;

	path = get_env(shell, "PATH");
	splitted_path = ft_strsplit(path, ':');
	temp = splitted_path;
	while (*temp)
	{
		add_dir_execs(shell, *temp);
		temp++;
	}
	free_2dchararr_terminated(splitted_path);
}

void	update_exec_table(t_shell *shell)
{
	char	*curr_path;

	curr_path = get_env(shell, ENV_PATH);
	if (ft_strequ(shell->path_var, curr_path))
		return ;
	ft_free_int(shell->path_var);
	shell->path_var = ft_strdup(curr_path);
	t_htable_clean_all(shell->executables);
	handle_exec_table(shell);
}

char	*get_program_path(t_shell *shell, char *program_name)
{
	char	*program_path;

	update_exec_table(shell);
	program_path = t_htable_get(shell->executables, program_name);
	if (!program_path)
		return (NULL);
	else
		return (ft_strdup(program_path));
}
