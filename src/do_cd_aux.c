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

static void	handle_prev_dir(char **path_tokens, int *n)
{
	int	j;

	j = *n;
	ft_free_null((void **)&path_tokens[j]);
	if (j > 1)
		j--;
	ft_free_null((void **)&path_tokens[j]);
	if (j > 1)
		j--;
	*n = j;
}

char	**get_path_tokens(char *path)
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
			handle_prev_dir(path_tokens, &j);
			continue ;
		}
		else if (ft_strequ(".", splitted[i]))
			continue ;
		ft_free_null((void **)&path_tokens[j]);
		path_tokens[j++] = ft_strdup(splitted[i]);
	}
	free_2dchararr_terminated(splitted);
	return (path_tokens);
}

char	*join_2darr(char **arr, char *sep)
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

static int	free_all(char *error, char *curr_dir)
{
	if (error)
		free(error);
	free(curr_dir);
	return (1);
}

int	is_tokens_valid(char **path_tokens, char *origin_path)
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
