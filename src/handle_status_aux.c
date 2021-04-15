/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:51:54 by clala             #+#    #+#             */
/*   Updated: 2021/02/07 19:00:11 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote_bs_status(int status)
{
	if (status == INPUT_STATUS_STRONG_QUOTE ||
		status == INPUT_STATUS_WEAK_QUOTE ||
		status == INPUT_STATUS_BACKSLASH)
		return (1);
	return (0);
}

void	handle_tabs_and_spaces(char **s)
{
	char	*temp;

	temp = *s;
	*s = ft_strtrim(*s);
	free(temp);
}

int	is_space_tab(int c)
{
	if (c == '\t'|| c == ' ')
		return (1);
	return (0);
}

int	is_empty_string(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (0);
	}
	return (1);
}

int	here(void)
{
	ft_printf("here\n");
	return (1);
}
