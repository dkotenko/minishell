/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/03/20 19:56:12 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*join_3_strings(char *s1, char *s2, char *s3)
{
	char		*joined;
	int			len_1;
	int			len_2;
	int			len_3;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	len_3 = ft_strlen(s3);
	joined = ft_strnew(len_1 + len_2 + len_3);
	ft_strcpy(joined, s1);
	ft_strcat(joined + len_1, s2);
	ft_strcat(joined + len_2, s3);
	return (joined);
}

//unix ищет файл во всех папках с начала до конца, запускает первый
//ищет имя в таблица, далее пытается запустить (доступ/запуск). Нет прав ? пишет zsh: command not found: prog

void				add_dir_execs(t_htable *t, char *dir_path)
{
	char			*curr_exec;
	char			*fullpath;
	struct stat		s_stat;
	DIR				*dir;
	struct dirent	*s_d;
	
	if (stat(dir_path, &s_stat) == -1 ||
		!S_ISDIR(s_stat.st_mode) ||
		access(dir_path, R_OK) == -1)
		return ;
	dir = opendir(dir_path);
	while ((s_d = readdir(dir)) != NULL)
	{
		if (ft_strequ(s_d->d_name, "..") || ft_strequ(s_d->d_name, "."))
			continue ;
		curr_exec = ft_strdup(s_d->d_name);
		
		fullpath = join_3_strings(dir_path, "/", curr_exec);
		//ft_printf("%s %s %s\n", dir_path, curr_exec, fullpath);
		if (stat(fullpath, &s_stat) == 0 && s_stat.st_mode & S_IXUSR &&
		!access(fullpath, R_OK))
		{
			//(void)t;
			//ft_printf("%s %d %s\n", s_d->d_name, errno, strerror(errno));
			t_htable_set(&t, curr_exec, fullpath);
			//ft_printf("key:%s value:%s\n", fullpath, t_htable_get(t, curr_exec));
		}
		else
		{
			free(fullpath);
			free(curr_exec);
		}
	}
	closedir(dir);
}

void			handle_exec_table(t_shell *shell, t_htable *t)
{
	char		**splitted_path;
	char		*path;
	char		**temp;

	
	path = get_env(shell, "PATH");
	splitted_path = ft_strsplit(path, ':');
	temp = splitted_path;
	while (*temp)
	{
		add_dir_execs(t, *temp);
		temp++;
	}
	free_2dchararr_terminated(splitted_path);
}

void		update_path_var(t_shell *shell)
{
	char	*curr_path;

	curr_path = get_env(shell, ENV_PATH);
	if (ft_strequ(shell->path_var, curr_path))
		return ;
	shell->path_var ? free(shell->path_var) : 0;
	shell->path_var = ft_strdup(curr_path);
}

void		update_exec_table(t_shell *shell)
{
	update_path_var(shell);
	t_htable_clean_all(shell->executables);
	handle_exec_table(shell, shell->executables);
}
