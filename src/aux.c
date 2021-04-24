/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/04/24 21:57:13 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = get_env(shell, ENV_PWD);
	if (pwd)
		pwd = ft_strdup(pwd);
	else
	{
		pwd = getcwd(pwd, sizeof(char *));
	}
	return (pwd);
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

int	is_separated(char *s)
{
	return (ft_strchr(s, ' ') || ft_strchr(s, '\t'));
}
