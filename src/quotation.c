#include "minishell.h"

int			is_quote(char c)
{
	if (c == SYMBOL_DOUBLE_QUOTE || c == SYMBOL_SINGLE_QUOTE)
		return (1);
	return (0);
}

int			print_entry_quote(t_quote_info *q_info)
{
	if (q_info->q_symbol == SYMBOL_SINGLE_QUOTE)
		ft_printf("quote> ");
	else if (q_info->q_symbol == SYMBOL_DOUBLE_QUOTE)
		ft_printf("dquote> ");
	else
		handle_error(ERR_INV_QUOTE_SYMBOL);
	return (1);
}

void				set_quote_info(t_quote_info *q_info, char c, int *next_symbol_flag)
{
	if (q_info->q_flag == false)
	{
		q_info->q_flag = true;
		q_info->q_symbol = c;
		*next_symbol_flag = false;
	}
	else if (q_info->q_flag == true)
	{
		if (q_info->q_symbol == c)
		{
			q_info->q_flag = true;
			q_info->q_symbol = c;
			*next_symbol_flag = false;
		}
	}
}


void				handle_quote_line(t_quote_info *q_info, char **s)
{
	
	int				i;
	int				j;
	int				next_symbol_flag;
	char			*new;
	char			*temp;
	

	i = -1;
	j = 0;
	new = ft_strnew(ft_strlen(*s));
	while (*s[++i])
	{
		next_symbol_flag = true;
		if (is_quote(*s[i]))
			set_quote_info(q_info, *s[i], &next_symbol_flag);
		new[j] = *s[i];
		if (next_symbol_flag)
			j++;
	}
	temp = q_info->s;
	q_info->s = ft_strjoin(q_info->s, new);
	free(temp);
	free(new);
}

void				handle_quotes(char **input_string)
{
	char			*s;
	t_quote_info	q_info;
	char			*temp;

	if (!ft_strchr(*input_string, SYMBOL_DOUBLE_QUOTE) && 
		!ft_strchr(*input_string, SYMBOL_SINGLE_QUOTE))
		return ;
	ft_memset(&q_info, 0, sizeof(t_quote_info));
	handle_quote_line(&q_info, input_string);
	while (q_info.q_flag && print_entry_quote(&q_info) &&
		get_next_line(STDIN_FILENO, &s))
	{
		handle_quote_line(&q_info, &s);
		free(s);
	}
	temp = *input_string;
	*input_string = q_info.s; 
	free(temp);
	free(q_info.s);
}